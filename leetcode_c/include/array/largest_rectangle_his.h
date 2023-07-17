/**
 * @file largest_rectangle_his.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/largest-rectangle-in-histogram/
 * @version 0.1
 * @date 2023-02-12
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef LEETCODE_LARGEST_RECTANGLE_HIS_H
#define LEETCODE_LARGEST_RECTANGLE_HIS_H

#include "../const.h"

#define EMPTY_POS -1

typedef struct {
    int* data;
    int stackTopIdx;
    int curSize;
    int capacity;
} MyStack_T;

MyStack_T* InitMyStack(int capacity) {
    MyStack_T* stackPtr = (MyStack_T*)calloc(1, sizeof(MyStack_T));
    stackPtr->data = (int*)calloc(capacity, sizeof(int));
    stackPtr->stackTopIdx = EMPTY_POS;
    stackPtr->capacity = capacity;
    stackPtr->curSize = 0;

    return stackPtr;
}

bool IsFullMyStack(MyStack_T* stackPtr) {
    if (stackPtr->stackTopIdx == (stackPtr->capacity - 1)) {
        return true;
    }
    return false;
}

bool IsEmptyMyStack(MyStack_T* stackPtr) {
    if (stackPtr->stackTopIdx == EMPTY_POS) {
        return true;
    }
    return false;
}

void PushMyStack(MyStack_T* stackPtr, int inVal) {
    if (IsFullMyStack(stackPtr)) {
        printf("stack is full.\n");
        return;
    }
    stackPtr->stackTopIdx++;
    stackPtr->data[stackPtr->stackTopIdx] = inVal;
    stackPtr->curSize++;
    return;
}

void PopMyStack(MyStack_T* stackPtr, int* outVal) {
    if (IsEmptyMyStack(stackPtr)) {
        printf("stack is empty.\n");
        return;
    }

    *outVal = stackPtr->data[stackPtr->stackTopIdx];
    stackPtr->stackTopIdx--;
    stackPtr->curSize--;
    return;
}

int TopMyStack(MyStack_T* stackPtr) {
    if (IsEmptyMyStack(stackPtr)) {
        printf("stack is empty.\n");
        return -1;
    }
    return (stackPtr->data[stackPtr->stackTopIdx]);
}

void FreeMyStack(MyStack_T* stackPtr) {
    free(stackPtr->data);
    free(stackPtr);
    return;
}

int largestRectangleArea(int* heights, int heightsSize){
    MyStack_T* stackPtr = NULL;
    stackPtr = InitMyStack(heightsSize);

    int ret = 0;
    if (heightsSize == 1) {
        return heights[0];
    }

    int outVal = 0;
    int high = 0;
    int width = 0;
    for (int i = 0; i < heightsSize; i++) {
        while (!(IsEmptyMyStack(stackPtr)) &&
            (heights[TopMyStack(stackPtr)] > heights[i])) {
            high = heights[TopMyStack(stackPtr)];
            // find the left boundary
            PopMyStack(stackPtr, &outVal);

            if (!IsEmptyMyStack(stackPtr)) {
                width = i - TopMyStack(stackPtr) - 1;
            } else {
                width = i;
            }
            ret = MAX(ret, high * width);
        }
        PushMyStack(stackPtr, i);
    }

    while (!(IsEmptyMyStack(stackPtr))) {
        high = heights[TopMyStack(stackPtr)];
        PopMyStack(stackPtr, &outVal);

        if (!IsEmptyMyStack(stackPtr)) {
            width = heightsSize - TopMyStack(stackPtr) - 1;
        } else {
            width = heightsSize;
        }
        ret = MAX(ret, high * width);
    }

    FreeMyStack(stackPtr);

    return ret;
}

#endif