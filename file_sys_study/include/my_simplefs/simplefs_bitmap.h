/**
 * @file simplefs_bitmap.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief simplefs bitmap interface
 * @version 0.1
 * @date 2023-10-21
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef FILE_SYS_STUDY_SIMPLEFS_BITMAP_H
#define FILE_SYS_STUDY_SIMPLEFS_BITMAP_H

#include <linux/bitmap.h>
#include  "simplefs.h"

/**
 * @brief Get the free inode object, return an unused inode number
 * and mark it used, return 0 if no free inode was found
 *
 * @param sb_info superblock info
 * @return uint32_t free inode index
 */
uint32_t get_free_inode(simplefs_sb_info *sb_info);

/**
 * @brief Get the free blocks, return $len unused block(s) number,
 * and mark it used, return 0 if no enough free block(s) were found
 *
 * @param sb_info superblock info
 * @param len free blocks
 * @return uint32_t free block index
 */
uint32_t get_free_blocks(simplefs_sb_info *sb_info, uint32_t len);

/**
 * @brief mark an inode as unused
 *
 * @param sb_info superblock info
 * @param inode_idx inode index
 */
void put_inode(simplefs_sb_info *sb_info, uint32_t inode_idx);

/**
 * @brief mark blocks with $len as unused
 *
 * @param sb_info superblock info
 * @param start_block_idx start block index
 * @param len required len
 */
void put_blocks(simplefs_sb_info *sb_info, uint32_t start_block_idx,
    uint32_t len);

#endif
