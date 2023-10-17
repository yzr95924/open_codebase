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

#define pr_fmt(fmt) "%s:%d:%s: " fmt, __FILE__, __LINE__, __func__

#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>

#include "../../include/my_fs/my_simple_fs.h"
#include "../../include/my_fs/my_simple_fs_sb_op.h"

struct dentry *simplefs_mount(struct file_system_type *fs_type, int flags,
    const char *dev_name, void *data) {
    struct dentry *root_dentry = NULL;
    root_dentry = mount_bdev(fs_type, flags, dev_name, data, simplefs_sb_op_fill);
    if (IS_ERR(root_dentry)) {
        pr_err("simplefs mount failed\n");
    } else {
        pr_info("simplefs mount successful\n");
    }
    return root_dentry;
}

static struct file_system_type simplefs_file_sys_type = {
    .owner = THIS_MODULE,
    .name = "simplefs",
    .mount = simplefs_mount,
};

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
