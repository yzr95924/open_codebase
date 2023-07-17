/**
 * @file permutations.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/permutations/
 * @version 0.1
 * @date 2023-02-11
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef LEETCODE_PERMUTATIONS_H
#define LEETCODE_PERMUTATIONS_H

#include "../const.h"

typedef struct {
    int** retAns;
    int cnt;
} AnsWrapper_T;

typedef struct {
    bool* usedArray;
    int* curAns;
    int curIdx;
} BackTrackState_T;

static void BackTrack(AnsWrapper_T* ansWrapper, BackTrackState_T* btState,
    int* nums, int numsSize) {
    if (btState->curIdx > numsSize - 1) {
        // find an ans
        memcpy(ansWrapper->retAns[ansWrapper->cnt],
            btState->curAns, sizeof(int) * numsSize);
        ansWrapper->cnt++;
        return;
    }

    for (int i = 0; i < numsSize; i++) {
        if (btState->usedArray[i] == false) {
            // do op
            btState->curAns[btState->curIdx] = nums[i];
            btState->usedArray[i] = true;
            btState->curIdx++;

            BackTrack(ansWrapper, btState, nums, numsSize);

            // revert op
            btState->usedArray[i] = false;
            btState->curIdx--;
        }
    }

    return;
}

int** permute(int* nums, int numsSize, int* returnSize, int** returnColumnSizes){
    int totalAnsCnt = YZRGetFactorial(numsSize);
    AnsWrapper_T ansWrapper;

    ansWrapper.retAns = (int**)calloc(totalAnsCnt, sizeof(int*));
    for (int i = 0; i < totalAnsCnt; i++) {
        ansWrapper.retAns[i] = (int*)calloc(numsSize, sizeof(int));
    }
    ansWrapper.cnt = 0;

    *returnColumnSizes = (int*)calloc(totalAnsCnt, sizeof(int));
    for (int i = 0; i < totalAnsCnt; i++) {
        (*returnColumnSizes)[i] = numsSize;
    }

    BackTrackState_T btState;
    btState.usedArray = (bool*)calloc(numsSize, sizeof(bool));
    btState.curAns = (int*)calloc(numsSize, sizeof(int));
    btState.curIdx = 0;

    BackTrack(&ansWrapper, &btState, nums, numsSize);

    free(btState.usedArray);
    free(btState.curAns);
    *returnSize = totalAnsCnt;
    return ansWrapper.retAns;
}

#endif