/**
 * @file arith_slices.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/arithmetic-slices/
 * @version 0.1
 * @date 2023-02-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef LEETCODE_ARITH_SLICES_H
#define LEETCODE_ARITH_SLICES_H

#include "../const.h"

static int CountSlices(int* nums, int startIdx, int endIdx) {
    int diff = nums[startIdx] - nums[startIdx + 1];
    int ret = 0;

    for (int i = startIdx + 1; i <= endIdx - 1; i++) {
        if (nums[i] - nums[i + 1] != diff) {
            break;
        } else {
            ret++;
        }
    }

    return ret;
}

int numberOfArithmeticSlices(int* nums, int numsSize){
    if (numsSize < 3) {
        return 0;
    }

    int arithmeticNum = 0;
    for (int i = 0; i < numsSize - 2; i++) {
        // numsSize - 3, numsSize - 2, numsSize - 1
        arithmeticNum += CountSlices(nums, i, numsSize - 1);
    }
   
    return arithmeticNum;
}

#endif