/**
 * @file extent.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief define the interface of extent
 * @version 0.1
 * @date 2023-10-28
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef FILE_SYS_STUDY_SIMPLEFS_EXTENT_H
#define FILE_SYS_STUDY_SIMPLEFS_EXTENT_H

#include "simplefs.h"

/**
 * @brief search the extent which contain the target block
 *
 * @param index_blk the index block
 * @param iblock the target block
 * @return uint32_t the first unused file index if not found
 * -1 if it is out of range
 */
int simplefs_ext_search_blk(simplefs_file_ei_block *index_blk, uint32_t iblock);

#endif
