/**
 * @file subset.c
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/subsets
 * @version 0.1
 * @date 2023-09-22
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../../include/back_track_q.h"

#define MAX_ANS_CNT 1024

typedef struct {
    int **retAns;
    int *retColSize;
    int cnt;
} AnsWrapper_T;

typedef struct {
    int *curAns;
    int curAnsSize;
    int curIdx;
} BackTrackState_T;

static void BackTrack(AnsWrapper_T *ansWrapper, BackTrackState_T *btState, int *nums,
    int numsSize)
{
    if (btState->curAnsSize >= 1) {
        memcpy(ansWrapper->retAns[ansWrapper->cnt], btState->curAns,
            sizeof(int) * btState->curAnsSize);
        ansWrapper->retColSize[ansWrapper->cnt] = btState->curAnsSize;
        ansWrapper->cnt++;
    }

    if (btState->curIdx > numsSize - 1) {
        return;
    }

    for (int idx = btState->curIdx; idx < numsSize; idx++) {
        // do op
        btState->curAns[btState->curAnsSize] = nums[idx];
        btState->curAnsSize++;
        btState->curIdx = idx + 1;
        BackTrack(ansWrapper, btState, nums, numsSize);

        // revert op
        btState->curAnsSize--;
    }
}

int** subsets_78(int* nums, int numsSize, int* returnSize, int** returnColumnSizes)
{
    AnsWrapper_T ansWrapper;
    ansWrapper.retAns = (int**)calloc(MAX_ANS_CNT, sizeof(int*));
    for (int idx = 0; idx < MAX_ANS_CNT; idx++) {
        ansWrapper.retAns[idx] = (int*)calloc(numsSize, sizeof(int));
    }
    ansWrapper.retColSize = (int*)calloc(MAX_ANS_CNT, sizeof(int));
    ansWrapper.cnt = 0;

    BackTrackState_T bkState = { 0 };
    bkState.curAns = (int*)calloc(numsSize, sizeof(int));

    ansWrapper.retColSize[0] = 0;
    ansWrapper.cnt++;

    BackTrack(&ansWrapper, &bkState, nums, numsSize);

    free(bkState.curAns);
    *returnSize = ansWrapper.cnt;
    *returnColumnSizes = ansWrapper.retColSize;

    return ansWrapper.retAns;
}
