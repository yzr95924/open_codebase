/**
 * @file simple_fs_sb_op.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief define the interfaces of superblock op
 * @version 0.1
 * @date 2023-10-01
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef FILE_SYS_STUDY_SIMPLEFS_SB_OP_H
#define FILE_SYS_STUDY_SIMPLEFS_SB_OP_H

#include <linux/buffer_head.h>
#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/statfs.h>
#include <linux/slab.h>
#include <linux/module.h>

#include "simplefs.h"
#include "simplefs_inode_op.h"

/**
 * @brief fill vfs superblock from simplefs superblock
 *
 * @param sb vfs superblock
 * @param data data
 * @param silent silent
 * @return int ret val
 */
int simplefs_sb_op_fill(struct super_block *sb, void *data, int silent);


#endif
