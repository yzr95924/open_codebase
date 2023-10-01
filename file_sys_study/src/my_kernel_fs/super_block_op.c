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
        pr_err(SIMPLE_FS_MODULE_NAME "read super block failed\n");
    }

    return ret;
}
