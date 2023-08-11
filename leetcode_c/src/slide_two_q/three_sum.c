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
    int baseAnsCnt = numsSize;
    int **retAns = (int**)calloc(sizeof(int*), numsSize);
    *returnColumnSizes = (int*)calloc(sizeof(int), numsSize);

    qsort(nums, numsSize, sizeof(int), CmpFunc);
    int curAnsCnt = 0;

    for (int idx = 0; idx < numsSize - 2; idx++) {
        if (nums[idx] > 0) {
            break;
        }

        if (idx > 0 && (nums[idx] == nums[idx - 1])) {
            continue;
        }

        int leftIdx = idx + 1;
        int rightIdx = numsSize - 1;
        while (leftIdx < rightIdx) {
            int curSum = nums[idx] + nums[leftIdx] + nums[rightIdx];

            if (curSum < 0) {
                leftIdx++;
            } else if (curSum > 0) {
                rightIdx--;
            } else {
                retAns[curAnsCnt] = calloc(sizeof(int), 3);
                retAns[curAnsCnt][0] = nums[idx];
                retAns[curAnsCnt][1] = nums[leftIdx];
                retAns[curAnsCnt][2] = nums[rightIdx];
                (*returnColumnSizes)[curAnsCnt] = 3;
                curAnsCnt++;

                if (curAnsCnt == baseAnsCnt) {
                    baseAnsCnt *= 2;
                    retAns = (int**)realloc(retAns, sizeof(int*) * baseAnsCnt);
                    *returnColumnSizes = (int*)realloc(*returnColumnSizes, sizeof(int) * baseAnsCnt);
                }

                while (rightIdx > leftIdx && (nums[rightIdx] == nums[rightIdx - 1])) {
                    rightIdx--;
                }
                rightIdx--;

                while (rightIdx > leftIdx && (nums[leftIdx] == nums[leftIdx + 1])) {
                    leftIdx++;
                }
                leftIdx++;
            }
        }
    }

    *returnSize = curAnsCnt;
    return retAns;
}
