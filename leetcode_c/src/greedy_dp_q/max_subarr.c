/**
 * @file max_subarr.c
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/maximum-subarray/
 * @version 0.1
 * @date 2023-08-20
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../../include/str_arr_q.h"

#define MAX(a,b) (((a) >= (b)) ? (a) : (b))

int maxSubArray(int* nums, int numsSize)
{
    int ret = INT32_MIN;
    int curSum = 0;
    for (int idx = 0; idx < numsSize; idx++) {
        curSum += nums[idx];
        ret = MAX(curSum, ret);
        if (curSum < 0) {
            curSum = 0;
        }
    }

    return ret;
}
