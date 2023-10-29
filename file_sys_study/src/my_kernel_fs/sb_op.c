/**
 * @file sb_op.c
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief super block func operation
 * @version 0.1
 * @date 2023-09-30
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../../include/my_simplefs/sb_op.h"

static struct kmem_cache *simplefs_inode_cache;

static int simplefs_sb_op_statfs(struct dentry *dentry, struct kstatfs *stat)
{
    struct super_block *sb = dentry->d_sb;
    simplefs_sb_info *sb_info = sb->s_fs_info;

    ZUORU_ENTRY;
    stat->f_type = SIMPLEFS_MAGIC;
    stat->f_bsize = SIMPLEFS_BLOCK_SIZE;
    stat->f_blocks = sb_info->total_block_num;
    stat->f_bfree = sb_info->free_block_num;
    stat->f_bavail = sb_info->free_block_num;
    stat->f_files = sb_info->total_inode_num - sb_info->free_inode_num;
    stat->f_ffree = sb_info->free_inode_num;
    stat->f_namelen = SIMPLEFS_MAX_FILENAME_LEN;

    ZUORU_EXIT;
    return 0;
}

static void simplefs_put_super(struct super_block *sb)
{
    simplefs_sb_info *sb_info = sb->s_fs_info;

    ZUORU_ENTRY;
    if (sb_info) {
        kfree(sb_info->inode_free_bitmap);
        kfree(sb_info->block_free_bitmap);
        kfree(sb_info);
    }

    ZUORU_EXIT;
    return;
}

static struct super_operations simplefs_super_ops = {
    .put_super = simplefs_put_super,
    .statfs = simplefs_sb_op_statfs
};


int simplefs_sb_op_fill(struct super_block *sb, void *data, int silent)
{
    struct buffer_head *bh = NULL;
    simplefs_sb_info *on_disk_sb_info = NULL;
    simplefs_sb_info *in_mem_sb_info = NULL;
    struct inode *root_inode = NULL;
    int ret = 0;

    ZUORU_ENTRY;
    // init sb
    sb->s_magic = SIMPLEFS_MAGIC;
    sb_set_blocksize(sb, SIMPLEFS_BLOCK_SIZE);
    sb->s_maxbytes = SIMPLEFS_MAX_FILE_SIZE;
    sb->s_op = &simplefs_super_ops;

    // read sb from disk
    bh = sb_bread(sb, SIMPLEFS_SUPER_BLOCK_POS);
    if (!bh) {
        ZUORU_KO_LOG_ERR("read super block failed\n");
        return -EIO;
    }
    on_disk_sb_info = (simplefs_sb_info*)bh->b_data;

    // check magic
    if (on_disk_sb_info->magic != sb->s_magic) {
        ZUORU_KO_LOG_ERR("wrong magic number\n");
        ret = -EINVAL;
        goto out_free_bh;
    }

    // alloc superblock info
    in_mem_sb_info = kzalloc(sizeof(simplefs_sb_info), GFP_KERNEL);
    if (!in_mem_sb_info) {
        ZUORU_KO_LOG_ERR("alloc in_mem_sb_info failed\n");
        ret = -ENOMEM;
        goto out_free_bh;
    }
    in_mem_sb_info->total_block_num = on_disk_sb_info->total_block_num;
    in_mem_sb_info->total_inode_num = on_disk_sb_info->total_inode_num;
    in_mem_sb_info->inode_store_block_num = on_disk_sb_info->inode_store_block_num;
    in_mem_sb_info->inode_free_bitmap_block_num = on_disk_sb_info->inode_free_bitmap_block_num;
    in_mem_sb_info->block_free_bitmap_block_num = on_disk_sb_info->block_free_bitmap_block_num;
    in_mem_sb_info->free_inode_num = on_disk_sb_info->free_inode_num;
    in_mem_sb_info->free_block_num = on_disk_sb_info->free_block_num;

    sb->s_fs_info = in_mem_sb_info;
    brelse(bh);

    // alloc and copy free inode bitmap
    in_mem_sb_info->inode_free_bitmap = kzalloc(
        in_mem_sb_info->inode_free_bitmap_block_num * SIMPLEFS_BLOCK_SIZE,
        GFP_KERNEL);
    if (!in_mem_sb_info->inode_free_bitmap) {
        ZUORU_KO_LOG_ERR("alloc in_mem_sb_info inode_free_bitmap failed\n");
        ret = -ENOMEM;
        goto out_free_in_mem_sb_info;
    }

    for (int idx = 0; idx < in_mem_sb_info->inode_free_bitmap_block_num; idx++) {
        bh = sb_bread(sb, 1 + in_mem_sb_info->inode_store_block_num + idx);
        if (!bh) {
            ret = -EIO;
            ZUORU_KO_LOG_ERR("sb_bread inode_free_bitmap failed, idx: %d\n", idx);
            goto out_free_inode_free_bitmap;
        }

        memcpy(in_mem_sb_info->inode_free_bitmap + idx * SIMPLEFS_BLOCK_SIZE, bh->b_data,
            SIMPLEFS_BLOCK_SIZE);
        brelse(bh);
    }

    // alloc the copy free block bitmap
    in_mem_sb_info->block_free_bitmap = kzalloc(
        in_mem_sb_info->block_free_bitmap_block_num * SIMPLEFS_BLOCK_SIZE,
        GFP_KERNEL);
    if (!in_mem_sb_info->block_free_bitmap) {
        ret = -ENOMEM;
        goto out_free_inode_free_bitmap;
    }

    for (int idx = 0; idx < in_mem_sb_info->block_free_bitmap_block_num; idx++) {
        bh = sb_bread(sb, 1 + in_mem_sb_info->inode_store_block_num +
            in_mem_sb_info->inode_free_bitmap_block_num + idx);
        if (!bh) {
            ret = -EIO;
            ZUORU_KO_LOG_ERR("sb_bread block_free_bitmap failed, idx: %d\n", idx);
            goto out_free_block_free_bitmap;
        }

        memcpy(in_mem_sb_info->block_free_bitmap + idx * SIMPLEFS_BLOCK_SIZE, bh->b_data,
            SIMPLEFS_BLOCK_SIZE);
        brelse(bh);
    }

    // create root inode
    root_inode = simplefs_iget(sb, 1); // ignore inode 0, start from inode 1
    if (IS_ERR(root_inode)) {
        ret = PTR_ERR(root_inode);
        goto out_free_block_free_bitmap;
    }

#if MNT_IDMAP_REQUIRED()
    inode_init_owner(&nop_mnt_idmap, root_inode, NULL, root_inode->i_mode);
#elif USER_NS_REQUIRED()
    inode_init_owner(&init_user_ns, root_inode, NULL, root_inode->i_mode);
#else
    inode_init_owner(root_inode, NULL, root_inode->i_mode);
#endif

    sb->s_root = d_make_root(root_inode);
    if (!sb->s_root) {
        ret = -ENOMEM;
        ZUORU_KO_LOG_ERR("convert root inode to root dentry failed\n");
        goto out_put_root_inode;
    }

    ZUORU_EXIT;
    return 0;

out_put_root_inode:
    iput(root_inode);
out_free_block_free_bitmap:
    kfree(in_mem_sb_info->block_free_bitmap);
out_free_inode_free_bitmap:
    kfree(in_mem_sb_info->inode_free_bitmap);
out_free_in_mem_sb_info:
    kfree(in_mem_sb_info);
out_free_bh:
    brelse(bh);

    return ret;
}

int simplefs_init_inode_cache(void)
{
    ZUORU_ENTRY;
    simplefs_inode_cache = kmem_cache_create(
        "simplefs_inode_cache", sizeof(simplefs_inode_info), 0, 0, NULL);
    if (!simplefs_inode_cache) {
        ZUORU_KO_LOG_ERR("create simplefs_inode_cache failed\n");
        return -ENOMEM;
    }

    ZUORU_EXIT;
    return 0;
}

void simplefs_destroy_inode_cache(void)
{
    ZUORU_ENTRY;
    kmem_cache_destroy(simplefs_inode_cache);
    ZUORU_EXIT;
    return;
}
