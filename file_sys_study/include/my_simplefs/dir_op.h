/**
 * @file dir_op.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief my simplefs dir operation header
 * @version 0.1
 * @date 2023-10-19
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef FILE_SYS_STUDY_SIMPLEFS_DIR_OP_H
#define FILE_SYS_STUDY_SIMPLEFS_DIR_OP_H

#include "simplefs.h"

/**
 * @brief get simplefs inode dir ops table
 *
 * @return struct file_operations*
 */
const struct file_operations* simplefs_get_inode_dir_op(void);

#endif
