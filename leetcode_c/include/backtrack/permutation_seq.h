/**
 * @file permutation_seq.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/permutation-sequence/
 * @version 0.1
 * @date 2023-02-23
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef LEETCODE_PERMUTATION_SEQ_H
#define LEETCODE_PERMUTATION_SEQ_H

#include "../const.h"

typedef struct {
    char* ans;
    int ansNum;
} AnsItem_T;

typedef struct {
    AnsItem_T* ansArray;
    int cnt;
} AnsWrapper_T;

typedef struct {
    bool* usedArray;
    char* curAns;
    int curSize;
} BackTrackState_T;

static int ConvertChar2Num(int n, char* inputStr) {
    int totalSum = 0;

    int weight = 1;
    for (int i = n - 1; i >= 0; i--) {
        int curNum = (int)(inputStr[i] - '0');
        totalSum += weight * curNum;
        weight *= 10;
    }

    return totalSum;
}

static void BackTrack(AnsWrapper_T* ansWrapper, BackTrackState_T* btState,
    int n, int pruneNum) {
    if (btState->curSize == n) {
        // find an ans
        for (int i = 0; i < n; i++) {
            printf("%c", btState->curAns[i]);
        }
        printf("\n");
        memcpy(ansWrapper->ansArray[ansWrapper->cnt].ans,
            btState->curAns, btState->curSize);
        ansWrapper->ansArray[ansWrapper->cnt].ansNum =
            ConvertChar2Num(n, ansWrapper->ansArray[ansWrapper->cnt].ans);
        ansWrapper->cnt++;
    }

    for (int i = 1; i <= n; i++) {
        if (btState->curSize == 0 && i != pruneNum) {
            // pruning
            continue;
        } else {
            if (btState->usedArray[i] == false) {
                // do op
                btState->curAns[btState->curSize] = i + '0';
                btState->usedArray[i] = true;
                btState->curSize++;

                BackTrack(ansWrapper, btState, n, pruneNum);

                // revert op
                btState->usedArray[i] = false;
                btState->curSize--;
            }
        }
    }

    return ;
}

int CmpFunc(const void* a, const void* b) {
    int aVal = ((AnsItem_T*)a)->ansNum;
    int bVal = ((AnsItem_T*)b)->ansNum;
    return aVal - bVal; // descend
}

char* getPermutation(int n, int k){
    int totalAnsSliceCnt = YZRGetFactorial(n - 1);
    AnsWrapper_T ansWrapper;

    ansWrapper.ansArray = (AnsItem_T*)calloc(totalAnsSliceCnt, sizeof(AnsItem_T));
    ansWrapper.cnt = 0;
    for (int i = 0; i < totalAnsSliceCnt; i++) {
        ansWrapper.ansArray[i].ans = (char*)calloc(n, sizeof(char));
    }

    BackTrackState_T btState;
    btState.usedArray = (bool*)calloc(n + 1, sizeof(bool));
    btState.curAns = (char*)calloc(n, sizeof(char));
    btState.curSize = 0;

    // count prune
    int new_k = k % totalAnsSliceCnt;
    int pruneNum = 0;
    if (new_k == 0) {
        pruneNum = k / totalAnsSliceCnt;
        new_k = totalAnsSliceCnt - 1;
    } else {
        pruneNum = k / totalAnsSliceCnt + 1;
        new_k -= 1;
    }

    BackTrack(&ansWrapper, &btState, n, pruneNum);

    qsort(&ansWrapper.ansArray[0], ansWrapper.cnt, sizeof(AnsItem_T), CmpFunc);

    char* retAns = (char*)calloc(n + 1, sizeof(char));
    memcpy(retAns, ansWrapper.ansArray[new_k].ans, n);
    retAns[n] = '\0';

    for (int i = 0; i < totalAnsSliceCnt; i++) {
        free(ansWrapper.ansArray[i].ans);
    }
    free(ansWrapper.ansArray);
    free(btState.curAns);
    free(btState.usedArray);

    return retAns;
}

#endif