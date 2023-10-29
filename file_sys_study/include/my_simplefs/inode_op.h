/**
 * @file inode_op.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief
 * @version 0.1
 * @date 2023-10-08
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef FILE_SYS_STUDY_SIMPLEFS_INODE_OP_H
#define FILE_SYS_STUDY_SIMPLEFS_INODE_OP_H

#include <linux/buffer_head.h>
#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/module.h>

#include "simplefs.h"

/**
 * @brief get inode from disk
 *
 * @param sb superblock
 * @param inode_idx inode index
 * @return struct inode* inode ptr
 */
struct inode *simplefs_iget(struct super_block *sb, unsigned long inode_idx);

#endif
