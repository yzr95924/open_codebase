/**
 * @file max_con_ones_3.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/max-consecutive-ones-iii/
 * @version 0.1
 * @date 2023-02-08
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef LEETCODE_MAX_CON_ONES_3_H
#define LEETCODE_MAX_CON_ONES_3_H

#include "../const.h"

int longestOnes(int* nums, int numsSize, int k){
    int frontIdx = 0;
    int rearIdx = 0;

    int ret = 0;
    while (frontIdx < numsSize) {
        if (nums[frontIdx] == 0) {
            k--;
        }

        if (k < 0) {
            if (nums[rearIdx] == 0) {
                k++;
            }
            rearIdx++;
        }

        ret = MAX(ret, frontIdx - rearIdx + 1);

        frontIdx++;
    }

    return ret;
}

#endif