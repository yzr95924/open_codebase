/**
 * @file decode_str.c
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/decode-string/
 * @version 0.1
 * @date 2023-07-25
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../../include/stack_q.h"

#define MY_DATA_STRUCT_EMPTY_POS (-1)
typedef char ZUORU_DataItem;

typedef struct {
    ZUORU_DataItem *data;
    int stackTopIdx;
    int curSize;
    int capacity;
} ZUORU_Stack;

ZUORU_Stack* ZUORU_InitStack(int capacity)
{
    ZUORU_Stack *stackPtr = (ZUORU_Stack*)calloc(1, sizeof(ZUORU_Stack));
    stackPtr->data = (ZUORU_DataItem*)calloc(capacity, sizeof(ZUORU_DataItem));
    stackPtr->stackTopIdx = MY_DATA_STRUCT_EMPTY_POS;
    stackPtr->capacity = capacity;
    stackPtr->curSize = 0;

    return stackPtr;
}

void ZUORU_FreeStack(ZUORU_Stack *stackPtr)
{
    free(stackPtr->data);
    free(stackPtr);
    return;
}

bool ZUORU_IsFullStack(ZUORU_Stack *stackPtr)
{
    if (stackPtr->stackTopIdx == (stackPtr->capacity - 1)) {
        return true;
    }
    return false;
}

bool ZUORU_IsEmptyStack(ZUORU_Stack *stackPtr)
{
    if (stackPtr->stackTopIdx == MY_DATA_STRUCT_EMPTY_POS) {
        return true;
    }
    return false;
}

bool ZUORU_PushStack(ZUORU_Stack *stackPtr, ZUORU_DataItem *inVal)
{
    if (ZUORU_IsFullStack(stackPtr)) {
        fprintf(stderr, "stack is full\n");
        return false;
    }
    stackPtr->stackTopIdx++;
    memcpy(&stackPtr->data[stackPtr->stackTopIdx], inVal,
        sizeof(ZUORU_DataItem));
    stackPtr->curSize++;
    return true;
}

bool ZUORU_PopStack(ZUORU_Stack *stackPtr, ZUORU_DataItem *outVal)
{
    if (ZUORU_IsEmptyStack(stackPtr)) {
        fprintf(stderr, "stack is empty\n");
        return false;
    }

    memcpy(outVal, &stackPtr->data[stackPtr->stackTopIdx],
        sizeof(ZUORU_DataItem));
    stackPtr->stackTopIdx--;
    stackPtr->curSize--;
    return true;
}

bool ZUORU_TopStack(ZUORU_Stack *stackPtr, ZUORU_DataItem *outVal)
{
    if (ZUORU_IsEmptyStack(stackPtr)) {
        fprintf(stderr, "stack is empty");
        return false;
    }
    memcpy(outVal, &stackPtr->data[stackPtr->stackTopIdx],
        sizeof(ZUORU_DataItem));

    return true;
}

bool IsDigit(char inputChar)
{
    if (inputChar <= '9' && inputChar >= '0') {
        return true;
    }
    return false;
}

void ProcDigit(ZUORU_Stack *stackPtr, int totalCnt)
{
    char tmpBuf[9000] = { 0 };
    ZUORU_DataItem tmpChar = '0';
    int subStrLen = 0;
    while (tmpChar != ']') {
        ZUORU_PopStack(stackPtr, &tmpChar);
        if (tmpChar != '[' && tmpChar != ']') {
            tmpBuf[subStrLen] = tmpChar;
            subStrLen++;
        }
    }

    for (int cnt = 0; cnt < totalCnt; cnt++) {
        for (int idx = subStrLen - 1; idx >= 0; idx--) {
            ZUORU_PushStack(stackPtr, &tmpBuf[idx]);
        }
    }

    return;
}

char* decodeString(char *s)
{
    char *retArr = (char*)calloc(9000, sizeof(char));
    ZUORU_Stack *stackPtr = ZUORU_InitStack(9000);
    int totalSize = strlen(s);

    bool isLastNum = false;
    int totalCnt = 0;
    int weight = 1;
    for (int idx = totalSize - 1; idx >= 0; idx--) {
        if (IsDigit(s[idx])) {
            totalCnt += weight * (s[idx] - '0');
            weight *= 10;
            isLastNum = true;
        } else {
            if (isLastNum) {
                ProcDigit(stackPtr, totalCnt);
                totalCnt = 0;
                weight = 1;
                isLastNum = false;
            }
            ZUORU_PushStack(stackPtr, &s[idx]);
        }
    }
    if (totalCnt != 0) {
        ProcDigit(stackPtr, totalCnt);
    }

    ZUORU_DataItem tmpChar;
    int stackSize = stackPtr->curSize;
    for (int idx = 0; idx < stackSize; idx++) {
        ZUORU_PopStack(stackPtr, &tmpChar);
        retArr[idx] = tmpChar;
    }

    ZUORU_FreeStack(stackPtr);
    return retArr;
}
