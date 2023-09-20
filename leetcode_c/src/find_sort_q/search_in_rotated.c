/**
 * @file search_in_rotated.c
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/search-in-rotated-sorted-array
 * @version 0.1
 * @date 2023-09-20
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../../include/find_sort_q.h"

static bool BinarySearchWithIdx(int *nums, int len, int target, int *retIdx)
{
    int leftIdx = 0;
    int rightIdx = len - 1;

    while (leftIdx <= rightIdx) {
        int midIdx = leftIdx + ((rightIdx - leftIdx) / 2);
        if (nums[midIdx] < target) {
            leftIdx = midIdx + 1;
        } else if (nums[midIdx] > target) {
            rightIdx = midIdx - 1;
        } else {
            *retIdx = midIdx;
            return true;
        }
    }

    return false;
}

int search_33(int* nums, int numsSize, int target)
{
    if (numsSize == 1) {
        if (nums[0] == target) {
            return 0;
        } else {
            return -1;
        }
    }

    int leftSegmentLen = 1;
    for (int idx = 1; idx < numsSize; idx++) {
        if (nums[idx] < nums[idx - 1]) {
            break;
        }
        leftSegmentLen++;
    }
    int rightSegmentLen = numsSize - leftSegmentLen;

    int retIdx = -1;
    if (BinarySearchWithIdx(nums, leftSegmentLen, target, &retIdx)) {
        return retIdx;
    }

    if (BinarySearchWithIdx(nums + leftSegmentLen, rightSegmentLen, target,
        &retIdx)) {
        return retIdx + leftSegmentLen;
    }

    return retIdx;
}
