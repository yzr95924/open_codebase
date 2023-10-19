/**
 * @file my_fs.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief
 * @version 0.1
 * @date 2023-09-24
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef FILE_SYS_STUDY_MY_SIMPLE_FS_H
#define FILE_SYS_STUDY_MY_SIMPLE_FS_H

#include <linux/types.h>
#include <linux/fs.h>
#include <linux/version.h>
#include <linux/module.h>
#include <linux/kernel.h>

#define SIMPLE_FS_MODULE_NAME "simple_fs"
#define USER_NS_REQUIRED() LINUX_VERSION_CODE >= KERNEL_VERSION(5,12,0)
#define MNT_IDMAP_REQUIRED() LINUX_VERSION_CODE >= KERNEL_VERSION(6,3,0)

#define _FILE strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__
#define KO_LOG_FMT(fmt) "%s:%d:%s: " fmt, _FILE, __LINE__, __func__

#define ZUORU_KO_LOG_INFO(message, args...) printk(KERN_INFO KO_LOG_FMT(message), ##args);
#define ZUORU_KO_LOG_ERR(message, args...) printk(KERN_ERR KO_LOG_FMT(message), ##args);

#define ZUORU_ENTRY ZUORU_KO_LOG_INFO("entry");
#define ZUORU_EXIT ZUORU_KO_LOG_INFO("exit");

/*
 * simplefs partition layout
 * +---------------+
 * |  superblock   |  1 block
 * +---------------+
 * |  inode store  |  sb->inode_store_block_num
 * +---------------+
 * | ifree bitmap  |  sb->inode_free_bitmap_block_num
 * +---------------+
 * | bfree bitmap  |  sb->block_free_bitmap_block_num
 * +---------------+
 * |    data       |
 * |      blocks   |  rest of the blocks
 * +---------------+
 */

#define SIMPLE_FS_SUPER_BLOCK_POS 0

#define SIMPLE_FS_BLOCK_SIZE (1 << 12) // 4KiB
#define SIMPLE_FS_MAGIC 0xDEADCELL // source: https://en.wikipedia.org/wiki/Hexspeak

#define SIMPLE_FS_MAX_EXTENTS \
    ((SIMPLE_FS_BLOCK_SIZE - sizeof(uint32_t)) / sizeof(simplefs_extent))
#define SIMPLE_FS_MAX_BLOCK_PER_EXTENT 8
#define SIMPLE_FS_MAX_FILE_SIZE \
    ((uint64_t) SIMPLE_FS_MAX_BLOCK_PER_EXTENT * SIMPLE_FS_BLOCK_SIZE * SIMPLE_FS_MAX_EXTENTS)

#define SIMPLE_FS_FILE_NAME_LEN 255

#define SIMPLE_FS_INODE_PER_BLOCK \
    (SIMPLE_FS_BLOCK_SIZE / sizeof(simplefs_inode))

typedef struct {
    uint32_t magic; // fs magic
    uint32_t total_block_num; // total number of blocks (include sb & inodes)
    uint32_t total_inode_num; // total number of inodes

    uint32_t inode_store_block_num; // blocks stored inode
    uint32_t inode_free_bitmap_block_num; // blocks stored inode free-bitmap
    uint32_t block_free_bitmap_block_num; // blocks stored block free-bitmap

    uint32_t free_inode_num;
    uint32_t free_block_num;

    uint8_t *inode_free_bitmap;
    uint8_t *block_free_bitmap;
} simplefs_sb_info;

typedef struct {
    uint32_t e_l_block; // first logical block covered by extent
    uint32_t e_p_block; // first physical block covered by extent
    uint32_t e_len; // number of blocks covered by extent
} simplefs_extent;

typedef struct {
    uint32_t i_mode; // file mode
    uint32_t i_uid; // owner id
    uint32_t i_gid; // group id
    uint32_t i_size; // size in byte
    uint32_t i_ctime; // inode change time
    uint32_t i_atime; // inode access time
    uint32_t i_mtime; // inode modify time
    uint32_t i_block; // block count
    uint32_t i_nlink; // hard link count
    uint32_t i_extent_block; // block with list of extents for this file
    uint8_t  i_sym_data[32]; // store symlink content
} __attribute__((packed)) simplefs_inode;

#ifdef __KERNEL__

typedef struct {
    uint32_t i_extent_block; // block with list of extents for this file
    char i_data[32];
    struct inode vfs_inode;
} simplefs_inode_info;

#endif // __KERNEL__

#endif
