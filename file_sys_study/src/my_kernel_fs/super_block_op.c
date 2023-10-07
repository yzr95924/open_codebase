/**
 * @file super_block_op.c
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief super block func operation
 * @version 0.1
 * @date 2023-09-30
 *
 * @copyright Copyright (c) 2023
 *
 */

#define pr_fmt(fmt) "simple_fs: " fmt

#include "../../include/my_fs/my_simple_fs_sb_op.h"

static int simplefs_sb_op_statfs(struct dentry *dentry, struct kstatfs *stat)
{
    struct super_block *sb = dentry->d_sb;
    simplefs_sb_info *sb_info = sb->s_fs_info;

    stat->f_type = SIMPLE_FS_MAGIC;
    stat->f_bsize = SIMPLE_FS_BLOCK_SIZE;
    stat->f_blocks = sb_info->total_block_num;
    stat->f_bfree = sb_info->free_block_num;
    stat->f_bavail = sb_info->free_block_num;
    stat->f_files = sb_info->total_inode_num - sb_info->free_inode_num;
    stat->f_ffree = sb_info->free_inode_num;
    stat->f_namelen = SIMPLE_FS_FILE_NAME_LEN;

    return 0;
}

static struct super_operations simplefs_super_ops = {
    .statfs = simplefs_sb_op_statfs
};


int simplefs_sb_op_fill(struct super_block *sb, void *data, int silent)
{
    struct buffer_head *bh = NULL;
    simplefs_sb_info *on_disk_sb = NULL;
    simplefs_sb_info *in_mem_sb = NULL;
    struct inode *root_inode = NULL;
    int ret = 0;

    // init sb
    sb->s_magic = SIMPLE_FS_MAGIC;
    sb_set_blocksize(sb, SIMPLE_FS_BLOCK_SIZE);
    sb->s_maxbytes = SIMPLE_FS_MAX_FILE_SIZE;
    sb->s_op = &simplefs_super_ops;

    // read sb from disk
    bh = sb_bread(sb, SIMPLE_FS_SUPER_BLOCK_POS);
    if (!bh) {
        pr_err("read super block failed\n");
        return -EIO;
    }
    on_disk_sb = (simplefs_sb_info*)bh->b_data;

    // check magic
    if (on_disk_sb->magic != sb->s_magic) {
        pr_err("wrong magic number\n");
        ret = -EINVAL;
        goto out_free_bh;
    }

    // alloc superblock info
    in_mem_sb = kzalloc(sizeof(simplefs_sb_info), GFP_KERNEL);
    if (!in_mem_sb) {
        pr_err("alloc in_mem_sb failed\n");
        ret = -ENOMEM;
        goto out_free_bh;
    }
    in_mem_sb->total_block_num = on_disk_sb->total_block_num;
    in_mem_sb->total_inode_num = on_disk_sb->total_inode_num;
    in_mem_sb->inode_store_block_num = on_disk_sb->inode_store_block_num;
    in_mem_sb->inode_free_bitmap_block_num = on_disk_sb->inode_free_bitmap_block_num;
    in_mem_sb->block_free_bitmap_block_num = on_disk_sb->block_free_bitmap_block_num;
    in_mem_sb->free_inode_num = on_disk_sb->free_inode_num;
    in_mem_sb->free_block_num = on_disk_sb->free_block_num;

    sb->s_fs_info = in_mem_sb;
    brelse(bh);

    // alloc and copy free inode bitmap
    in_mem_sb->inode_free_bitmap = kzalloc(
        in_mem_sb->inode_free_bitmap_block_num * SIMPLE_FS_BLOCK_SIZE,
        GFP_KERNEL);
    if (!in_mem_sb->inode_free_bitmap) {
        pr_err("alloc in_mem_sb inode_free_bitmap fail\n");
        ret = -ENOMEM;
        goto out_free_in_mem_sb_info;
    }

    for (int idx = 0; idx < in_mem_sb->inode_free_bitmap_block_num; idx++) {
        bh = sb_bread(sb, 1 + in_mem_sb->inode_store_block_num + idx);
        if (!bh) {
            ret = -EIO;
            pr_err("sb_bread inode_free_bitmap fail, idx: %d\n", idx);
            goto out_free_inode_free_bitmap;
        }

        memcpy(in_mem_sb->inode_free_bitmap + idx * SIMPLE_FS_BLOCK_SIZE, bh->b_data,
            SIMPLE_FS_BLOCK_SIZE);
        brelse(bh);
    }

    // TODO: alloc the copy free block bitmap

    return 0;

out_free_block_free_bitmap:
    kfree(in_mem_sb->block_free_bitmap);
out_free_inode_free_bitmap:
    kfree(in_mem_sb->inode_free_bitmap);
out_free_in_mem_sb_info:
    kfree(in_mem_sb);
out_free_bh:
    brelse(bh);

    return ret;
}
