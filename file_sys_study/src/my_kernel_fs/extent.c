/**
 * @file extent.c
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief implement the interface of extent
 * @version 0.1
 * @date 2023-10-28
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../../include/my_simplefs/extent.h"

int simplefs_ext_search_blk(simplefs_file_ei_block *index_blk, uint32_t iblock)
{
    for (int i = 0; i < SIMPLEFS_MAX_EXTENTS; i++) {
        uint32_t logical_blk = index_blk->extents[i].e_l_block;
        uint32_t len = index_blk->extents[i].e_len;
        if (index_blk->extents[i].e_p_block == 0 ||
            (iblock >= logical_blk && iblock < logical_blk + len)) {
            return i;
        }
    }
    return -1;
}
