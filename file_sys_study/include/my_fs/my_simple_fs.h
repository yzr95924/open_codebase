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

#define SIMPLE_FS_BLOCK_SIZE (1 << 12) // 4KiB
#define SIMPLE_FS_MAGIC 0xDEADCELL // source: https://en.wikipedia.org/wiki/Hexspeak

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

typedef struct {
    uint32_t magic; // fs magic
    uint32_t total_block_num;
    uint32_t total_inode_num;

    uint32_t inode_store_block_num; // blocks stored inode
    uint32_t inode_free_bitmap_block_num; // blocks stored inode free-bitmap
    uint32_t block_free_bitmap_block_num; // blocks stored block free-bitmap

    uint32_t free_inode_num;
    uint32_t free_block_num;

    uint8_t *free_inode_bitmap;
    uint8_t *free_block_bitmap;
} simplefs_sb_info;

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

#define SIMPLE_FS_INODE_PER_BLOCK \
    (SIMPLE_FS_BLOCK_SIZE / sizeof(simplefs_inode))

#endif
