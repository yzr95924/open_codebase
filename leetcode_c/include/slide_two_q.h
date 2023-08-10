/**
 * @file slide_two_q.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief the question set of sliding window and two pointer
 * @version 0.1
 * @date 2023-08-10
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef LEETCODE_C_SLIDE_TWO_Q_H
#define LEETCODE_C_SLIDE_TWO_Q_H

#include "../../common_include/c_include.h"

/**
 * @brief 11. 盛最多水的容器
 * @cite https://leetcode.cn/problems/container-with-most-water
 *
 */
int maxArea(int* height, int heightSize);

/**
 * @brief 15. 三数之和
 * @cite https://leetcode.cn/problems/3sum
 *
 */
int** threeSum(int* nums, int numsSize, int* returnSize, int** returnColumnSizes);

/**
 * @brief 283. 移动零
 * @cite https://leetcode.cn/problems/move-zeroes
 *
 */
void moveZeroes(int* nums, int numsSize);

#endif
