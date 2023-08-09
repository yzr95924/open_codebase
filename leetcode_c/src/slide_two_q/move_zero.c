/**
 * @file move_zero.c
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/move-zeroes
 * @version 0.1
 * @date 2023-08-10
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../../include/slide_two_q.h"

void moveZeroes(int* nums, int numsSize)
{
    int leftIdx = 0;
    int rightIdx = 0;
    while (rightIdx < numsSize) {
        if (nums[rightIdx] != 0) {
            nums[leftIdx] = nums[rightIdx];
            leftIdx++;
        }
        rightIdx++;
    }

    for (int idx = leftIdx; idx < numsSize; idx++) {
        nums[idx] = 0;
    }
    return ;
}
