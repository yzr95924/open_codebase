/**
 * @file simple_fs.c
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief the main module implementation
 * @version 0.1
 * @date 2023-09-25
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../../include/my_simplefs/simplefs.h"

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

#include "../../include/my_simplefs/sb_op.h"

struct dentry *simplefs_mount(struct file_system_type *fs_type, int flags,
    const char *dev_name, void *data) {
    struct dentry *root_dentry = NULL;

    ZUORU_ENTRY;
    root_dentry = mount_bdev(fs_type, flags, dev_name, data, simplefs_sb_op_fill);
    if (IS_ERR(root_dentry)) {
        ZUORU_KO_LOG_ERR("simplefs mount failed\n");
    } else {
        ZUORU_KO_LOG_INFO("simplefs mount successful\n");
    }

    ZUORU_EXIT;
    return root_dentry;
}

void simplefs_kill_sb(struct super_block *sb)
{
    ZUORU_ENTRY;
    kill_block_super(sb);
    ZUORU_KO_LOG_INFO("unmount simplefs\n");

    ZUORU_EXIT;
    return;
}

static struct file_system_type simplefs_file_sys_type = {
    .owner = THIS_MODULE,
    .name = "simplefs",
    .mount = simplefs_mount,
    .kill_sb = simplefs_kill_sb,
    .fs_flags = FS_REQUIRES_DEV,
    .next = NULL,
};

static int __init simple_fs_mod_init(void)
{
    int ret = 0;
    ret = simplefs_init_inode_cache();
    if (ret) {
        ZUORU_KO_LOG_ERR("init inode cache failed\n");
        goto out_end;
    }

    ret = register_filesystem(&simplefs_file_sys_type);
    if (ret) {
        ZUORU_KO_LOG_ERR("register simplefs failed\n");
        goto out_end;
    }

    ZUORU_KO_LOG_INFO("simplefs is loaded\n");
    return 0;

out_end:
    return ret;
}

static void __exit simple_fs_mod_exit(void)
{
    int ret = 0;
    ret = unregister_filesystem(&simplefs_file_sys_type);
    if (ret) {
        ZUORU_KO_LOG_ERR("unregister simplefs failed\n");
    }

    simplefs_destroy_inode_cache();
    ZUORU_KO_LOG_INFO("simplefs is unloaded\n");
    return;
}

module_init(simple_fs_mod_init);
module_exit(simple_fs_mod_exit);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Zuoru YANG");
MODULE_DESCRIPTION("my simple file system");
