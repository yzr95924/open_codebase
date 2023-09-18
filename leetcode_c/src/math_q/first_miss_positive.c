/**
 * @file first_miss_positive.c
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/first-missing-positive/
 * @version 0.1
 * @date 2023-09-08
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../../include/math_q.h"

int firstMissingPositive(int* nums, int numsSize)
{
    int tmpVal = 0;
    for (int idx = 0; idx < numsSize; idx++) {
        while (nums[idx] > 0 &&
            nums[idx] <= numsSize &&
            nums[nums[idx] - 1] != nums[idx]) {
            tmpVal = nums[nums[idx] - 1];
            nums[nums[idx] - 1] = nums[idx];
            nums[idx] = tmpVal;
        }
    }

    for (int idx = 0; idx < numsSize; idx++) {
        if (nums[idx] != idx + 1) {
            return idx + 1;
        }
    }

    return numsSize + 1;
}
