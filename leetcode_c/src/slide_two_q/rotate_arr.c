/**
 * @file rotate_arr.c
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/rotate-array
 * @version 0.1
 * @date 2023-09-07
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../../include/slide_two_q.h"

void ReverseArr(int *nums, int startIdx, int endIdx)
{
    int tmpVal;
    while (startIdx < endIdx) {
        tmpVal = nums[startIdx];
        nums[startIdx] = nums[endIdx];
        nums[endIdx] = tmpVal;
        startIdx++;
        endIdx--;
    }
    return;
}

void rotateArr(int* nums, int numsSize, int k){
    k %= numsSize; // if k > numsSize
    int startIdx = 0;
    int endIdx = numsSize - 1;
    ReverseArr(nums, startIdx, endIdx);

    startIdx = 0;
    endIdx = k - 1;
    ReverseArr(nums, startIdx, endIdx);

    startIdx = k;
    endIdx = numsSize - 1;
    ReverseArr(nums, startIdx, endIdx);
    return;
}
