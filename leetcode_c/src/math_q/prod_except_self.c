/**
 * @file prod_except_self.c
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/product-of-array-except-self/
 * @version 0.1
 * @date 2023-09-07
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../../include/math_q.h"

int* productExceptSelf(int* nums, int numsSize, int* returnSize)
{
    int *retArr = (int*)calloc(numsSize, sizeof(int));
    int *lTbl = (int*)calloc(numsSize, sizeof(int));
    int *rTbl = (int*)calloc(numsSize, sizeof(int));

    lTbl[0] = 1;
    rTbl[numsSize - 1] = 1;

    for (int idx = 1; idx < numsSize; idx++) {
        lTbl[idx] = lTbl[idx - 1] * nums[idx - 1];
    }
    for (int idx = numsSize - 2; idx >= 0; idx--) {
        rTbl[idx] = rTbl[idx + 1] * nums[idx + 1];
    }

    for (int idx = 0; idx < numsSize; idx++) {
        retArr[idx] = lTbl[idx] * rTbl[idx];
    }
    *returnSize = numsSize;

    free(lTbl);
    free(rTbl);

    return retArr;
}
