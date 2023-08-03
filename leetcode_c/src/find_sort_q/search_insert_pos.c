/**
 * @file search_insert_pos.c
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/search-insert-position/
 * @version 0.1
 * @date 2023-08-03
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../../include/find_sort_q.h"

int searchInsert(int* nums, int numsSize, int target)
{
    int leftIdx = 0;
    int rightIdx = numsSize - 1;
    int ans = numsSize;
    while (leftIdx <= rightIdx) {
        int middleIdx = leftIdx + ((rightIdx - leftIdx) / 2);
        if (target <= nums[middleIdx] ) {
            ans = middleIdx;
            rightIdx = middleIdx - 1;
        } else {
            leftIdx = middleIdx + 1;
        }
    }

    return ans;
}
