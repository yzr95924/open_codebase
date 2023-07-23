/**
 * @file partition_lab.c
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/partition-labels/
 * @version 0.1
 * @date 2023-07-23
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../../include/greedy_dp_q.h"

#define MAX(a,b) (((a) >= (b)) ? (a) : (b))

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* partitionLabels(char * s, int* returnSize)
{
    int lastIdxMap[26] = { 0 };
    int totalSize = strlen(s);
    int *retArr = (int*)calloc(totalSize, sizeof(int));

    for (int idx = 0; idx < totalSize; idx++) {
        lastIdxMap[s[idx] - 'a'] = idx;
    }

    int startIdx = 0;
    int endIdx = 0;
    int curSegmentNum = 0;
    for (int idx = 0; idx < totalSize; idx++) {
        endIdx = MAX(endIdx, lastIdxMap[s[idx] - 'a']);
        if (idx == endIdx) {
            retArr[curSegmentNum] = endIdx - startIdx + 1;
            startIdx = idx + 1;
            curSegmentNum++;
        }
    }
    *returnSize = curSegmentNum;

    return retArr;
}
