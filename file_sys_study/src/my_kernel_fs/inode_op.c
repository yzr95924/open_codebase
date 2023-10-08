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

struct inode *simplefs_iget(struct super_block *sb, unsigned long inode_idx)
{
    // TODO: impl getting inode from disk
    return NULL;
}
