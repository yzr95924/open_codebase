/**
 * @file file_op.c
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief inode file ops interface implementation
 * @version 0.1
 * @date 2023-10-23
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../../include/my_simplefs/simplefs_file_op.h"

const struct file_operations simplefs_file_ops = {
    .owner = THIS_MODULE,
};

const struct file_operations* simplefs_get_inode_file_op(void)
{
    return &simplefs_file_ops;
}
