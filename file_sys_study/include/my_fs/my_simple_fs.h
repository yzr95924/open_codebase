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

#define MY_SIMPLE_BLOCK_SIZE (1 << 12) // 4KiB

typedef struct {
    uint32_t magic;
    uint32_t total_block_num;
    uint32_t total_inode_num;

    uint32_t inode_store_block_num;
    uint32_t inode_free_bitmap_block_num;
    uint32_t block_free_bitmap_block_num;

    uint32_t free_inode_num;
    uint32_t free_block_num;

    uint8_t *free_inode_bitmap;
    uint8_t *free_block_bitmap;
} simplefs_sb_info;


#endif
