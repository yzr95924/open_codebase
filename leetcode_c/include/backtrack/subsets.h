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
    int curSize;
} BackTrackState_T;

void BackTrack(AnsWrapper_T* ansWrapper, BackTrackState_T* btState,
    int* nums, int numsSize, int startIdx) {

    // collect the ans here!
    memcpy(ansWrapper->retAns[ansWrapper->cnt],
        btState->curAns, sizeof(int) * btState->curSize);
    ansWrapper->returnColumnSizes[ansWrapper->cnt] = btState->curSize;
    ansWrapper->cnt++;

    if (startIdx >= numsSize) {
        return;
    }

    for (int i = startIdx; i < numsSize; i++) {
        // do op
        btState->curAns[btState->curSize] = nums[i];
        btState->curSize++;

        BackTrack(ansWrapper, btState, nums, numsSize, i + 1);

        // revert op
        btState->curSize--;
    }

    return;
}

int** subsets(int* nums, int numsSize, int* returnSize, int** returnColumnSizes){
    int totalAns = (int)pow(2.0, (double)numsSize);

    *returnColumnSizes = (int*)calloc(totalAns, sizeof(int));
    int** retAns = (int**)calloc(totalAns, sizeof(int*));
    for (int i = 0; i < totalAns; i++) {
        retAns[i] = (int*)calloc(numsSize, sizeof(int));
    }


    int* curAns = (int*)calloc(numsSize, sizeof(int));
    BackTrackState_T btState;
    btState.curAns = curAns;
    btState.curSize = 0;

    AnsWrapper_T ansWrapper;
    ansWrapper.returnColumnSizes = *returnColumnSizes;
    ansWrapper.retAns = retAns;
    ansWrapper.cnt = 0;

    BackTrack(&ansWrapper, &btState, nums, numsSize, 0);

    free(curAns);
    *returnSize = ansWrapper.cnt;

    return retAns;
}

#endif