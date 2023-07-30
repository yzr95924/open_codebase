/**
 * @file largest_rect_hist.c
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/largest-rectangle-in-histogram
 * @version 0.1
 * @date 2023-07-30
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../../include/stack_q.h"

#define MAX(a,b) (((a) >= (b)) ? (a) : (b))
typedef struct {
    int curIdx;
    int curHeight;
} HeightRecord;

#define MY_DATA_STRUCT_EMPTY_POS (-1)
typedef HeightRecord ZUORU_DataItem;

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

int largestRectangleArea(int* heights, int heightsSize)
{
    ZUORU_Stack *stackPtr = ZUORU_InitStack(heightsSize);
    int *leftLowIdx = (int*)calloc(heightsSize, sizeof(int));
    int *rightLowIdx = (int*)calloc(heightsSize, sizeof(int));
    int ret = 0;

    ZUORU_DataItem curInItem;
    ZUORU_DataItem curOutItem;
    for (int idx = 0; idx < heightsSize; idx++) {
        curInItem.curIdx = idx;
        curInItem.curHeight = heights[idx];
        while (!ZUORU_IsEmptyStack(stackPtr)) {
            ZUORU_TopStack(stackPtr, &curOutItem);
            if (curOutItem.curHeight >= curInItem.curHeight) {
                ZUORU_PopStack(stackPtr, &curOutItem);
            } else {
                break;
            }
        }
        if (ZUORU_IsEmptyStack(stackPtr)) {
            leftLowIdx[curInItem.curIdx] = -1;
        } else {
            ZUORU_TopStack(stackPtr, &curOutItem);
            leftLowIdx[curInItem.curIdx] = curOutItem.curIdx;
        }
        ZUORU_PushStack(stackPtr, &curInItem);
    }

    // reset stack
    stackPtr->curSize = 0;
    stackPtr->stackTopIdx = MY_DATA_STRUCT_EMPTY_POS;

    for (int idx = heightsSize - 1; idx >= 0; idx--) {
        curInItem.curIdx = idx;
        curInItem.curHeight = heights[idx];
        while (!ZUORU_IsEmptyStack(stackPtr)) {
            ZUORU_TopStack(stackPtr, &curOutItem);
            if (curOutItem.curHeight >= curInItem.curHeight) {
                ZUORU_PopStack(stackPtr, &curOutItem);
            } else {
                break;
            }
        }
        if (ZUORU_IsEmptyStack(stackPtr)) {
            rightLowIdx[curInItem.curIdx] = heightsSize;
        } else {
            ZUORU_TopStack(stackPtr, &curOutItem);
            rightLowIdx[curInItem.curIdx] = curOutItem.curIdx;
        }
        ZUORU_PushStack(stackPtr, &curInItem);
    }

    for (int idx = 0; idx < heightsSize; idx++) {
        ret = MAX(ret, (rightLowIdx[idx] - leftLowIdx[idx] - 1) * heights[idx]);
    }

    free(leftLowIdx);
    free(rightLowIdx);
    ZUORU_FreeStack(stackPtr);

    return ret;
}
