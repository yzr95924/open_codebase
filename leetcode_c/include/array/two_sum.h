/**
 * @file two_sum.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/two-sum/
 * @version 0.1
 * @date 2023-01-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef LEETCODE_TWO_SUM_H
#define LEETCODE_TWO_SUM_H

#include "../const.h"

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* nums, int numsSize, int target, int* returnSize){
    int* retArray = (int*)malloc(sizeof(int) * 2);

    for (int i = 0; i < numsSize; i++) {
        // printf("i = %d\n", i);
        for (int j = 0; j < i; j++) {
            // printf("j = %d\n", j); 
            if ((nums[i] + nums[j]) == target) {
                retArray[0] = j;
                retArray[1] = i;
                // printf("find a ans! [%d, %d]\n", i, j);
            }
        }
    }

    *returnSize = 2;
    return retArray;
}

#endif