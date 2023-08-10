/**
 * @file three_sum.c
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/3sum/
 * @version 0.1
 * @date 2023-08-11
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../../include/slide_two_q.h"

int CmpFunc(const void *leftItem, const void *rightItem)
{
    int *leftVal = (int*)leftItem;
    int *rightVal = (int*)rightItem;
    return (*leftVal > *rightVal);
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** threeSum(int* nums, int numsSize, int* returnSize, int** returnColumnSizes)
{
    qsort(nums, numsSize, sizeof(int), CmpFunc);
}
