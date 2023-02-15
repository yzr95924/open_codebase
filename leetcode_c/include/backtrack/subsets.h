/**
 * @file subsets.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/subsets/
 * @version 0.1
 * @date 2023-02-16
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef LEETCODE_SUBSETS_H
#define LEETCODE_SUBSETS_H

#include "../const.h"

typedef struct {
    int** retAns;
    int* returnColumnSizes;
    int cnt;
} AnsWrapper_T;

typedef struct {
    int* curAns;
    int curIdx;
    int curSize;
} BackTrackState_T;

void BackTrack(AnsWrapper_T* ansWrapper, BackTrackState_T* btState,
    int* nums, int numsSize) {
        
    if (btState->curIdx == numsSize) {
        memcpy(ansWrapper->retAns[ansWrapper->cnt],
            btState->curAns, sizeof(int) * btState->curSize);
        ansWrapper->returnColumnSizes[ansWrapper->cnt] = btState->curSize;
        ansWrapper->cnt++;
        return ;
    }

    // do op
    btState->curAns[btState->curSize] = nums[btState->curIdx];
    btState->curSize++;
    btState->curIdx++;

    BackTrack(ansWrapper, btState, nums, numsSize);

    // revert op
    btState->curSize--;
    BackTrack(ansWrapper,btState,nums, numsSize);

    return ;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** subsets(int* nums, int numsSize, int* returnSize, int** returnColumnSizes){
    int totalAns = (int)pow(2.0, (double)numsSize);
    *returnSize = totalAns;

    *returnColumnSizes = (int*)calloc(totalAns, sizeof(int));
    int** retAns = (int**)calloc(totalAns, sizeof(int*)); 
    for (int i = 0; i < totalAns; i++) {
        retAns[i] = (int*)calloc(numsSize, 0);
    }

    int curAns[3] = {0};
    BackTrackState_T btState;
    btState.curAns = curAns;
    btState.curIdx = 0;
    btState.curSize = 0;

    AnsWrapper_T ansWrapper;
    ansWrapper.returnColumnSizes = *returnColumnSizes;
    ansWrapper.retAns = retAns;
    ansWrapper.cnt = 0;

    BackTrack(&ansWrapper, &btState, nums, numsSize);

    return retAns;
}

#endif