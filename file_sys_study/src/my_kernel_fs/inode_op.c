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

#include "../../include/my_fs/my_simple_fs_inode_op.h"

static const struct inode_operations simplefs_inode_ops;
static const struct inode_operations simplefs_symlink_inode_ops;

struct inode *simplefs_iget(struct super_block *sb, unsigned long inode_idx)
{
    // TODO: impl getting inode from disk
    struct inode *vfs_inode = NULL;
    struct simplefs_inode *simplefs_inode = NULL;
    struct simplefs_inode_fs *simplefs_inode_info = NULL;
    struct simplefs_sb_info *simplefs_sb_info = sb->s_fs_info;
    struct buffer_head *bh = NULL;

    // compute the inode block
    uint32_t inode_block_idx = (inode_idx / SIMPLE_FS_INODE_PER_BLOCK) + 1;
    uint32_t inode_block_offset = inode_idx % SIMPLE_FS_INODE_PER_BLOCK;

    return NULL;
}
