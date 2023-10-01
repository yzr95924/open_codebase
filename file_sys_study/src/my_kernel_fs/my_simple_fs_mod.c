/**
 * @file my_simple_fs.c
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief the main module implementation
 * @version 0.1
 * @date 2023-09-25
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>

#include "../../include/my_fs/my_simple_fs.h"

static int __init my_simple_fs_init(void)
{
    pr_info("my simplefs is loaded\n");
    return 0;
}

static void __exit my_simple_fs_exit(void)
{
    pr_info("my simplefs is unloaded\n");
}

module_init(my_simple_fs_init);
module_exit(my_simple_fs_exit);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Zuoru YANG");
MODULE_DESCRIPTION("my simple file system");
