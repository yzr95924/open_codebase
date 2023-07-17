/**
 * @file combine.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/combinations/
 * @version 0.1
 * @date 2023-02-17
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef LEETCODE_COMBINE_H
#define LEETCODE_COMBINE_H

#include "../const.h"

typedef struct {
    int** retAns;
    int cnt;
} AnsWrapper_T;

typedef struct {
    int* curAns;
    int curSize;
} BackTrackState_T;

static void BackTrack(AnsWrapper_T* ansWrapper, BackTrackState_T* btState,
    int n, int k, int startIdx) {
    if (btState->curSize == k) {
        memcpy(ansWrapper->retAns[ansWrapper->cnt],
            btState->curAns, sizeof(int) * k);
        ansWrapper->cnt++;
        return;
    }

    for (int i = startIdx; i <= n; i++) {
        // do op
        btState->curAns[btState->curSize] = i;
        btState->curSize++;

        BackTrack(ansWrapper, btState, n, k, i + 1);

        // revert op
        btState->curSize--;
    }

    return;
}

int** combine(int n, int k, int* returnSize, int** returnColumnSizes){
    *returnSize = YZRGetFactorial(n) / (YZRGetFactorial(k) * YZRGetFactorial(n - k));

    AnsWrapper_T ansWrapper;
    ansWrapper.retAns = (int**)calloc(*returnSize, sizeof(int*));
    ansWrapper.cnt = 0;
    for (int i = 0; i < *returnSize; i++) {
        ansWrapper.retAns[i] = (int*)calloc(k, sizeof(int));
    }

    *returnColumnSizes = (int*)calloc(*returnSize, sizeof(int));
    for (int i = 0; i < *returnSize; i++) {
        (*returnColumnSizes)[i] = k;
    }

    BackTrackState_T btState;
    btState.curSize = 0;
    btState.curAns = (int*)calloc(k, sizeof(int));

    BackTrack(&ansWrapper, &btState, n, k, 1);

    return ansWrapper.retAns;
}

#endif