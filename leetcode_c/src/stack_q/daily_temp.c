/**
 * @file daily_temp.c
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/daily-temperatures
 * @version 0.1
 * @date 2023-07-30
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../../include/stack_q.h"

typedef struct {
    int curIdx;
    int curTemp;
} TempRecord;

#define MY_DATA_STRUCT_EMPTY_POS (-1)
typedef TempRecord ZUORU_DataItem;

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

int* dailyTemperatures(int* temperatures, int temperaturesSize, int* returnSize)
{
    int *retArr = (int*)calloc(temperaturesSize, sizeof(int));
    *returnSize = temperaturesSize;
    ZUORU_Stack *stackPtr = ZUORU_InitStack(temperaturesSize);

    ZUORU_DataItem curInItem;
    ZUORU_DataItem curOutItem;
    for (int idx = 0; idx < temperaturesSize; idx++) {
        curInItem.curIdx = idx;
        curInItem.curTemp = temperatures[idx];
        if (ZUORU_IsEmptyStack(stackPtr)) {
            ZUORU_PushStack(stackPtr, &curInItem);
        } else {
            while (!ZUORU_IsEmptyStack(stackPtr)) {
                ZUORU_TopStack(stackPtr, &curOutItem);
                if (curOutItem.curTemp < curInItem.curTemp) {
                    ZUORU_PopStack(stackPtr, &curOutItem);
                    retArr[curOutItem.curIdx] = curInItem.curIdx - curOutItem.curIdx;
                } else {
                    break;
                }
            }
            ZUORU_PushStack(stackPtr, &curInItem);
        }
    }

    int totalSize = stackPtr->curSize;
    for (int idx = 0; idx < totalSize; idx++) {
        ZUORU_PopStack(stackPtr, &curOutItem);
        retArr[curOutItem.curIdx] = 0;
    }

    ZUORU_FreeStack(stackPtr);
    return retArr;
}
