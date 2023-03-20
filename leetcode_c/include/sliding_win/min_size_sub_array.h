/**
 * @file min_size_sub_array.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/minimum-size-subarray-sum/
 * @version 0.1
 * @date 2023-02-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef LEETCODE_MIN_SIZE_SUB_ARRAY_H
#define LEETCODE_MIN_SIZE_SUB_ARRAY_H

#include "../const.h"

int minSubArrayLen(int target, int* nums, int numsSize){
    int leftIdx = 0;
    int rightIdx = 0;

    int curVal = nums[rightIdx];
    int minSize = 0; 
    
    bool findAns = false;
    while (rightIdx < numsSize) {
        if (curVal >= target) {
            int curSize = rightIdx - leftIdx + 1;
            if (!findAns) {
                minSize = curSize;
                findAns = true;
            } else {
                minSize = MIN(minSize, curSize);
            }
            curVal -= nums[leftIdx];
            leftIdx++;
        } else {
            rightIdx++;
            if (rightIdx == numsSize) {
                break;
            } else {
                curVal += nums[rightIdx];
            }
        }
    }

    return minSize;
}

#endif