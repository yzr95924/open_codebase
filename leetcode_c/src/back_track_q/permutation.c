/**
 * @file permutation.c
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/permutations
 * @version 0.1
 * @date 2023-09-22
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../../include/back_track_q.h"

#define MAX_ANS_CNT 720

typedef struct {
    int **retAns;
    int cnt;
} AnsWrapper_T;

typedef struct {
    bool *usedArr;
    int *curAns;
    int curIdx;
} BackTrackState_T;

static void BackTrack(AnsWrapper_T *ansWrapper, BackTrackState_T *btStat, int *nums,
    int numsSize)
{
    if (btStat->curIdx > numsSize - 1) {
        // find an ans
        memcpy(ansWrapper->retAns[ansWrapper->cnt], btStat->curAns,
            sizeof(int) * numsSize);
        ansWrapper->cnt++;
        return;
    }

    for (int idx = 0; idx < numsSize; idx++) {
        if (btStat->usedArr[idx] == false) {
            // do op
            btStat->curAns[btStat->curIdx] = nums[idx];
            btStat->usedArr[idx] = true;
            btStat->curIdx++;

            BackTrack(ansWrapper, btStat, nums, numsSize);

            // revert op
            btStat->usedArr[idx] = false;
            btStat->curIdx--;
        }
    }
    return;
}

int** permute_46(int* nums, int numsSize, int* returnSize, int** returnColumnSizes)
{
    AnsWrapper_T ansWrapper;
    ansWrapper.retAns = (int**)calloc(MAX_ANS_CNT, sizeof(int*));
    for (int idx = 0; idx < MAX_ANS_CNT; idx++) {
        ansWrapper.retAns[idx] = (int*)calloc(numsSize, sizeof(int));
    }
    ansWrapper.cnt = 0;

    BackTrackState_T btState;
    btState.usedArr = (bool*)calloc(numsSize, sizeof(bool));
    btState.curAns = (int*)calloc(numsSize, sizeof(int));
    btState.curIdx = 0;

    BackTrack(&ansWrapper, &btState, nums, numsSize);

    free(btState.usedArr);
    free(btState.curAns);
    *returnSize = ansWrapper.cnt;

    *returnColumnSizes = (int*)calloc(ansWrapper.cnt, sizeof(int));
    for (int idx = 0; idx < ansWrapper.cnt; idx++) {
        (*returnColumnSizes)[idx] = numsSize;
    }
    return ansWrapper.retAns;
}
