/**
 * @file letter_combinations_of_phone_num.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/letter-combinations-of-a-phone-number
 * @version 0.1
 * @date 2023-03-22
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef LEETCODE_LETTER_COMBINE_OF_PHONE_NUM_H
#define LEETCODE_LETTER_COMBINE_OF_PHONE_NUM_H

#include "../const.h"

static const char letterTbl[][5] = {
    "", // 0
    "", // 1
    "abc", // 2
    "def", // 3
    "ghi", // 4
    "jkl", // 5
    "mno", // 6
    "pqrs", // 7
    "tuv", // 8
    "wxyz", // 9
};

typedef struct {
    char** retAns;
    int cnt;
} AnsWrapper_T;

typedef struct {
    char* curAns;
    int curSize;
    char* inputStr;
    int curCharIdx;
} BackTrackState_T;

static void BackTrack(AnsWrapper_T* ansWrapper, BackTrackState_T* btState, int targetSize) {
    if (btState->curSize == targetSize) {
        btState->curAns[btState->curSize] = '\0';
        ansWrapper->retAns[ansWrapper->cnt] =
            (char*)calloc(btState->curSize + 1, sizeof(char));
        char* targetPtr = ansWrapper->retAns[ansWrapper->cnt];
        memcpy(targetPtr, btState->curAns, btState->curSize + 1);
        ansWrapper->cnt++;
        return ;
    }

    int curDigit = btState->inputStr[btState->curCharIdx] - '0';
    int curChoiceSize = strlen(letterTbl[curDigit]);

    for (int i = 0; i < curChoiceSize; i++) {
        btState->curAns[btState->curSize] = letterTbl[curDigit][i];
        btState->curSize++;
        btState->curCharIdx++;
        BackTrack(ansWrapper, btState, targetSize);
        btState->curSize--;
        btState->curCharIdx--;
    }

    return ;
}


char** letterCombinations(char* digits, int* returnSize){
    int retSize = strlen(digits);

    if (0 == retSize) {
        *returnSize = 0;
        return NULL;
    }

    BackTrackState_T btState;
    btState.curAns = (char*)calloc(retSize + 1, sizeof(char));
    btState.curSize = 0;
    btState.inputStr = digits;
    btState.curCharIdx = 0;

    AnsWrapper_T ansWrapper;
    ansWrapper.cnt = 0;
    int totalAnsCnt = 1;
    for (int i = 0; i < retSize; i++) {
        int curDigit = digits[i] - '0';
        totalAnsCnt *= strlen(letterTbl[curDigit]);
    }
    ansWrapper.retAns = (char**)calloc(totalAnsCnt, sizeof(char*));

    BackTrack(&ansWrapper, &btState, retSize);

    free(btState.curAns);

    *returnSize = ansWrapper.cnt;
    return ansWrapper.retAns;
}

#endif