/**
 * @file daily_temperature.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/daily-temperatures/
 * @version 0.1
 * @date 2023-02-12
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef LEETCODE_DAILY_TEMPERATURE_H
#define LEETCODE_DAILY_TEMPERATURE_H

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
        return ;
    }
    stackPtr->stackTopIdx++;
    stackPtr->data[stackPtr->stackTopIdx] = inVal;
    stackPtr->curSize++;
    return ;
}

void PopMyStack(MyStack_T* stackPtr, int* outVal) {
    if (IsEmptyMyStack(stackPtr)) {
        printf("stack is empty.\n");
        return ;
    }
    
    *outVal = stackPtr->data[stackPtr->stackTopIdx];
    stackPtr->stackTopIdx--;
    stackPtr->curSize--;
    return ;
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
    return ;
}

int* dailyTemperatures(int* temperatures, int temperaturesSize, int* returnSize){
    *returnSize = temperaturesSize;
    int *ret = (int*)calloc(temperaturesSize, sizeof(int));

    MyStack_T* stackPtr = NULL;
    stackPtr = InitMyStack(temperaturesSize);

    int outVal = 0;

    if (temperaturesSize == 1) {
        ret[0] = 0;
        return ret;
    }

    PushMyStack(stackPtr, 0);
    for (int i = 1; i < temperaturesSize; i++) {
        while (!(IsEmptyMyStack(stackPtr)) &&
            (temperatures[TopMyStack(stackPtr)] < temperatures[i])) {
            ret[TopMyStack(stackPtr)] = i - TopMyStack(stackPtr);
            PopMyStack(stackPtr, &outVal);
        }
        PushMyStack(stackPtr, i);
    }

    while (!(IsEmptyMyStack(stackPtr))) {
        PopMyStack(stackPtr, &outVal);
        ret[outVal] = 0;
    }

    FreeMyStack(stackPtr);

    return ret;
}

#endif