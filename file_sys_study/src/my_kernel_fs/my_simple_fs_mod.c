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

#include "../../include/my_simplefs/simplefs.h"
#include "../../include/my_simplefs/simplefs_sb_op.h"

#include <linux/init.h>

struct dentry *simplefs_mount(struct file_system_type *fs_type, int flags,
    const char *dev_name, void *data) {
    struct dentry *root_dentry = NULL;
    root_dentry = mount_bdev(fs_type, flags, dev_name, data, simplefs_sb_op_fill);
    if (IS_ERR(root_dentry)) {
        ZUORU_KO_LOG_INFO("simplefs mount failed\n");
    } else {
        ZUORU_KO_LOG_ERR("simplefs mount successful\n");
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
    ZUORU_KO_LOG_INFO("my simplefs is loaded\n");
    return 0;
}

static void __exit my_simple_fs_exit(void)
{
    ZUORU_KO_LOG_INFO("my simplefs is unloaded\n");
}

module_init(my_simple_fs_init);
module_exit(my_simple_fs_exit);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Zuoru YANG");
MODULE_DESCRIPTION("my simple file system");
