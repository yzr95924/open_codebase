/**
 * @file inode_op.c
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief
 * @version 0.1
 * @date 2023-10-08
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../../include/my_simplefs/simplefs_inode_op.h"

extern const struct file_operations simplefs_dir_ops;
extern const struct file_operations simplefs_file_ops;

static const struct inode_operations simplefs_inode_ops;
static const struct inode_operations simplefs_symlink_inode_ops;

struct inode *simplefs_iget(struct super_block *sb, unsigned long inode_idx)
{
    struct inode *l_vfs_inode = NULL;
    simplefs_inode *l_simplefs_inode = NULL;
    simplefs_inode_info *l_simplefs_inode_info = NULL;
    simplefs_sb_info *l_simplefs_sb_info = sb->s_fs_info;
    struct buffer_head *bh = NULL;

    // compute the inode block
    uint32_t inode_block_idx = (inode_idx / SIMPLEFS_INODE_PER_BLOCK) + 1;
    uint32_t inode_block_offset = inode_idx % SIMPLEFS_INODE_PER_BLOCK;
    int ret;

    ZUORU_ENTRY;

    if (inode_idx >= l_simplefs_sb_info->total_inode_num) {
        ZUORU_KO_LOG_ERR("inode idx is out of range");
        return ERR_PTR(-EINVAL);
    }

    l_vfs_inode = iget_locked(sb, inode_idx);
    if ((l_vfs_inode->i_state & I_NEW) == 0) { // in the cache
        return l_vfs_inode;
    }

    l_simplefs_inode_info = container_of(l_vfs_inode, simplefs_inode_info, vfs_inode);
    bh = sb_bread(sb, inode_block_idx); // read inode from disk and initialize
    if (!bh) {
        ZUORU_KO_LOG_ERR("bread inode block failed");
        ret = -EIO;
        goto out_failed;
    }
    l_simplefs_inode = (simplefs_inode*)bh->b_data;
    l_simplefs_inode += inode_block_offset;

    l_vfs_inode->i_ino = inode_idx;
    l_vfs_inode->i_sb = sb;
    l_vfs_inode->i_op = &simplefs_inode_ops;

    l_vfs_inode->i_mode = le32_to_cpu(l_simplefs_inode->i_mode);
    i_uid_write(l_vfs_inode, le32_to_cpu(l_simplefs_inode->i_uid));
    i_gid_write(l_vfs_inode, le32_to_cpu(l_simplefs_inode->i_gid));
    l_vfs_inode->i_size = le32_to_cpu(l_simplefs_inode->i_size);

#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 5, 0)
    inode_set_ctime(l_vfs_inode, (time64_t) le32_to_cpu(l_simplefs_inode->i_ctime), 0);
#else
    l_vfs_inode->i_ctime.tv_sec = (time64_t)le32_to_cpu(l_simplefs_inode->i_ctime);
    l_vfs_inode->i_ctime.tv_nsec = 0;
#endif

    l_vfs_inode->i_atime.tv_sec = (time64_t)le32_to_cpu(l_simplefs_inode->i_atime);
    l_vfs_inode->i_atime.tv_nsec = 0;
    l_vfs_inode->i_mtime.tv_sec = (time64_t)le32_to_cpu(l_simplefs_inode->i_mtime);
    l_vfs_inode->i_mtime.tv_nsec = 0;
    l_vfs_inode->i_blocks = le32_to_cpu(l_simplefs_inode->i_block);
    set_nlink(l_vfs_inode, le32_to_cpu(l_simplefs_inode->i_nlink));

    if (S_ISDIR(l_vfs_inode->i_mode)) {
        l_simplefs_inode_info->i_extent_block =
            le32_to_cpu(l_simplefs_inode->i_extent_block);
        l_vfs_inode->i_fop = &simplefs_dir_ops;
    } else if (S_ISREG(l_vfs_inode->i_mode)) {
        // TODO: for regular file --> inode operation
    } else if (S_ISLNK(l_vfs_inode->i_mode)) {
        // TODO: for hardlink file --> inode operation
    } else {
        ZUORU_KO_LOG_ERR("wrong inode mode");
        ret = -EIO;
        goto out_failed;
    }

    brelse(bh);
    // unlock the inode to make it usable
    unlock_new_inode(l_vfs_inode);

    ZUORU_EXIT;
    return l_vfs_inode;

out_failed:
    brelse(bh);
    iget_failed(l_vfs_inode);
    return ERR_PTR(ret);
}
