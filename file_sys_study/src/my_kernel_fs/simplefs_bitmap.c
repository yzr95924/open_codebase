/**
 * @file simplefs_bitmap.c
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief simplefs bitmap interface implementation
 * @version 0.1
 * @date 2023-10-21
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../../include/my_simplefs/simplefs_bitmap.h"

/**
 * @brief Get the first free bits, return the first bit and clear the following $len
 * consecutive free bits (set to 1) in a given in-memory bitmap spanning over
 * multiple blocks. Return 0 if no enough free bits were found (the first bit is never
 * free because of the superblock and the root inode)
 *
 * @param free_bitmap free bitmap
 * @param size total size
 * @param len required len
 * @return uint32_t ret index
 */
static uint32_t get_first_free_bits(unsigned long *free_bitmap,
    uint32_t size, uint32_t len)
{
    uint32_t bit, prev = 0, count = 0;
    for_each_set_bit(bit, free_bitmap, size) {
        if (prev != bit - 1) {
            count = 0;
        }
        prev = bit;
        if (++count == len) {
            bitmap_clear(free_bitmap, bit - len + 1, len);
            return bit - len + 1;
        }
    }
    return 0;
}

uint32_t get_free_inode(simplefs_sb_info *sb_info)
{
    uint32_t ret = 0;
    ZUORU_ENTRY;
    ret = get_first_free_bits((unsigned long*)sb_info->inode_free_bitmap,
        sb_info->total_inode_num, 1);
    if (ret) {
        sb_info->free_inode_num--;
    }

    ZUORU_EXIT;
    return ret;
}

uint32_t get_free_blocks(simplefs_sb_info *sb_info, uint32_t len)
{
    uint32_t ret = 0;
    ZUORU_ENTRY;
    ret = get_first_free_bits((unsigned long*)sb_info->block_free_bitmap,
        sb_info->total_block_num, len);
    if (ret) {
        sb_info->free_block_num -= len;
    }

    ZUORU_EXIT;
    return ret;
}

/**
 * @brief mark the $len bits from start-th bit in free_bitmap as free (1)
 *
 * @param free_bitmap free bitmap
 * @param size total size
 * @param start_idx start index
 * @param len required len
 * @return int ret value (0: success, -1: failed)
 */
static int put_free_bits(unsigned long *free_bitmap, uint32_t size, uint32_t start_idx,
    uint32_t len)
{
    if (start_idx + len - 1 > size) {
        return -1;
    }
    bitmap_set(free_bitmap, start_idx, len);
    return 0;
}

void put_inode(simplefs_sb_info *sb_info, uint32_t inode_idx)
{
    ZUORU_ENTRY;
    if (put_free_bits((unsigned long*)sb_info->inode_free_bitmap,
        sb_info->total_inode_num, inode_idx, 1)) {
        ZUORU_KO_LOG_ERR("set free inode bitmap failed\n");
        return;
    }
    sb_info->free_inode_num++;

    ZUORU_EXIT;
    return;
}

void put_blocks(simplefs_sb_info *sb_info, uint32_t start_block_idx,
    uint32_t len)
{
    ZUORU_ENTRY;
    if (put_free_bits((unsigned long*)sb_info->block_free_bitmap,
        sb_info->total_block_num, start_block_idx, len)) {
        ZUORU_KO_LOG_ERR("set free block bitmap failed\n");
        return;
    }
    sb_info->free_block_num += len;

    ZUORU_EXIT;
    return;
}
