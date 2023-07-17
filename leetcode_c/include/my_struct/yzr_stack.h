/**
 * @file yzr_stack.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief
 * @version 0.1
 * @date 2023-03-30
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef LEETCODE_YZR_STACK_H
#define LEETCODE_YZR_STACK_H

#include "../const.h"

#define EMPTY_POS -1

typedef struct {
    int* data;
    int stackTopIdx;
    int curSize;
    int capacity;
} YzrStack;

YzrStack* YzrStackCreate(int capacity) {
    YzrStack* stackPtr = (YzrStack*)calloc(1, sizeof(YzrStack));
    stackPtr->data = (int*)calloc(capacity, sizeof(*(stackPtr->data)));
    stackPtr->stackTopIdx = EMPTY_POS;
    stackPtr->capacity = capacity;
    stackPtr->curSize = 0;

    return stackPtr;
}

bool YzrStackIsFull(YzrStack* stackPtr) {
    if (stackPtr->stackTopIdx == (stackPtr->capacity - 1)) {
        return true;
    }
    return false;
}

bool YzrStackIsEmpty(YzrStack* stackPtr) {
    if (stackPtr->stackTopIdx == EMPTY_POS) {
        return true;
    }
    return false;
}

void YzrStackPush(YzrStack* stackPtr, int* inVal) {
    if (YzrStackIsFull(stackPtr)) {
        printf("stack is full.\n");
        return;
    }
    stackPtr->stackTopIdx++;
    memcpy(&stackPtr->data[stackPtr->stackTopIdx], inVal, sizeof(*(stackPtr->data)));
    stackPtr->curSize++;
    return;
}

void YzrStackPop(YzrStack* stackPtr, int* outVal) {
    if (YzrStackIsEmpty(stackPtr)) {
        printf("stack is empty.\n");
        return;
    }

    memcpy(outVal, &stackPtr->data[stackPtr->stackTopIdx], sizeof(*(stackPtr->data)));
    stackPtr->stackTopIdx--;
    stackPtr->curSize--;
    return;
}

int YzrStackTop(YzrStack* stackPtr) {
    if (YzrStackIsEmpty(stackPtr)) {
        printf("stack is empty.\n");
        return -1;
    }
    return (stackPtr->data[stackPtr->stackTopIdx]);
}

void YzrStackFree(YzrStack* stackPtr) {
    free(stackPtr->data);
    free(stackPtr);
    return;
}

#endif