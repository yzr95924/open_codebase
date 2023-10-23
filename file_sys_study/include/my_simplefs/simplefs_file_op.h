/**
 * @file simplefs_file_op.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief define the simplefs file op interface
 * @version 0.1
 * @date 2023-10-23
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef FILE_SYS_STUDY_SIMPLEFS_FILE_OP_H
#define FILE_SYS_STUDY_SIMPLEFS_FILE_OP_H

#include "simplefs.h"

/**
 * @brief get simplefs inode file ops table
 *
 * @return const struct file_operations* ptr to file op table
 */
const struct file_operations* simplefs_get_inode_file_op(void);

#endif
