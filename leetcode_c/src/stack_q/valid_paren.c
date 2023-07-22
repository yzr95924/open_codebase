/**
 * @file valid_paren.c
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/valid-parentheses
 * @version 0.1
 * @date 2023-07-23
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

bool isValid(char * s)
{
    bool ret = true;
    int totalSize = strlen(s);
    if (totalSize == 1) {
        return false;
    }

    bool stopScan = false;
    bool popRet = false;
    ZUORU_DataItem tmpChar;
    ZUORU_Stack *stackPtr = ZUORU_InitStack(10000);
    for (int idx = 0; idx < totalSize; idx++) {
        if (stopScan) {
            break;
        }
        switch (s[idx]) {
            case '(':
                ZUORU_PushStack(stackPtr, &s[idx]);
                break;
            case '{':
                ZUORU_PushStack(stackPtr, &s[idx]);
                break;
            case '[':
                ZUORU_PushStack(stackPtr, &s[idx]);
                break;
            case ')':
                popRet = ZUORU_PopStack(stackPtr, &tmpChar);
                if (tmpChar != '(' || !popRet) {
                    stopScan = true;
                    ret = false;
                }
                break;
            case '}':
                popRet = ZUORU_PopStack(stackPtr, &tmpChar);
                if (tmpChar != '{' || !popRet) {
                    stopScan = true;
                    ret = false;
                }
                break;
            case ']':
                popRet = ZUORU_PopStack(stackPtr, &tmpChar);
                if (tmpChar != '[' || !popRet) {
                    stopScan = true;
                    ret = false;
                }
                break;
        }
    }

    if (stackPtr->curSize != 0) {
        ret = false;
    }

    ZUORU_FreeStack(stackPtr);
    return ret;
}
