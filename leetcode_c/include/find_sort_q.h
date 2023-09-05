/**
 * @file find_sort_q.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief the question set of BFS
 * @version 0.1
 * @date 2023-08-03
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef LEETCODE_C_FIND_SORT_Q_H
#define LEETCODE_C_FIND_SORT_Q_H

#include "../../common_include/c_include.h"

/**
 * @brief 35. 搜索插入位置
 * @cite https://leetcode.cn/problems/search-insert-position
 *
 */
int searchInsert(int* nums, int numsSize, int target);

/**
 * @brief 56. 合并区间
 * @cite https://leetcode.cn/problems/merge-intervals
 *
 */
int** merge(int** intervals, int intervalsSize, int* intervalsColSize, int* returnSize,
    int** returnColumnSizes);

/**
 * @brief 74. 搜索二维矩阵
 * @cite https://leetcode.cn/problems/search-a-2d-matrix/
 *
 */
bool searchMatrix(int** matrix, int matrixSize, int* matrixColSize, int target);

#endif