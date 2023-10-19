/**
 * @file dir_op.c
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief my simplefs dir operation
 * @version 0.1
 * @date 2023-10-19
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../../include/my_simplefs/simplefs_dir_op.h"

const struct file_operations simplefs_dir_ops = {
    .owner = THIS_MODULE,
};