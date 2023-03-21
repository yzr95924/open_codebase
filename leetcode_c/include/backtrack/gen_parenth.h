/**
 * @file gen_parenth.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/generate-parentheses/
 * @version 0.1
 * @date 2023-02-20
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef LEETCODE_GEN_PARENTH_H
#define LEETCODE_GEN_PARENTH_H

#include "../const.h"

typedef struct {
    char** retAns;
    int cnt;
} AnsWrapper_T;

typedef struct {
    char* curAns;
    int curSize;
} BackTrackState_T;

static bool CheckValid(char* inputStr, int targetSize) {
    int map[2] = {0};

    for (int i = 0; i < targetSize; i++) {
        if (inputStr[i] == '(') {
            map[0]++;
        } else {
            // ')'
            if (map[0] > 0) {
                map[0]--;
            } else {
                return false;
            }
        }
    }

    if (map[0] != 0) {
        return false;
    }

    return true;
}

static void BackTrack(AnsWrapper_T* ansWrapper, BackTrackState_T* btState,
    int targetSize) {
    char choice[2] = {'(', ')'};

    if (btState->curSize == targetSize) {
        if (CheckValid(btState->curAns, targetSize)) {
            ansWrapper->retAns[ansWrapper->cnt] = (char*)calloc(targetSize + 1, sizeof(char));
            memcpy(ansWrapper->retAns[ansWrapper->cnt],
                btState->curAns,
                btState->curSize);
            ansWrapper->retAns[ansWrapper->cnt][btState->curSize] = '\0';
            ansWrapper->cnt++;
        }
        return ;
    }

    for (int i = 0; i < 2; i++) {
        btState->curAns[btState->curSize] = choice[i];
        btState->curSize++;

        BackTrack(ansWrapper, btState, targetSize);

        btState->curSize--;
    }

    return ;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char ** generateParenthesis(int n, int* returnSize){
    uint64_t maxAnsCnt = (uint64_t)pow((double)2, (double)(2 * n));

    AnsWrapper_T ansWrapper;
    ansWrapper.retAns = (char**)calloc(maxAnsCnt, sizeof(char*));
    ansWrapper.cnt = 0;

    BackTrackState_T btState;
    btState.curAns = (char*)calloc(2 * n, sizeof(char));
    btState.curSize = 0;

    BackTrack(&ansWrapper, &btState, 2 * n);

    free(btState.curAns);

    // ret the result
    *returnSize = ansWrapper.cnt;
    return ansWrapper.retAns;
}

#endif