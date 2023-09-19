/**
 * @file find_first_last_pos.c
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/find-first-and-last-position-of-element-in-sorted-array
 * @version 0.1
 * @date 2023-09-19
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../../include/find_sort_q.h"

static bool BinarySearch(int *nums, int len, int target, int *retIdx)
{
    int leftIdx = 0;
    int rightIdx = len - 1;

    while (leftIdx <= rightIdx) {
        int midIdx = leftIdx + ((rightIdx - leftIdx) / 2);
        if (nums[midIdx] > target) {
            rightIdx = midIdx - 1;
        } else if (nums[midIdx] < target) {
            leftIdx = midIdx + 1;
        } else {
            *retIdx = midIdx;
            return true;
        }
    }

    return false;
}

int* searchRange_34(int* nums, int numsSize, int target, int* returnSize)
{
    *returnSize = 2;
    int *retArr = (int*)calloc(*returnSize, sizeof(int));
    int retIdx = 0;

    if (!BinarySearch(nums, numsSize, target, &retIdx)) {
        retArr[0] = -1;
        retArr[1] = -1;
        return retArr;
    }

    int leftBound = retIdx;
    while (leftBound >= 0) {
        if (nums[leftBound] != target) {
            break;
        }
        leftBound--;
    }
    leftBound++;

    int rightBound = retIdx;
    while (rightBound < numsSize) {
        if (nums[rightBound] != target) {
            break;
        }
        rightBound++;
    }
    rightBound--;

    retArr[0] = leftBound;
    retArr[1] = rightBound;
    return retArr;
}
