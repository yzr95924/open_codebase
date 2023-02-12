/**
 * @file max_width_ramp.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/maximum-width-ramp/
 * @version 0.1
 * @date 2023-02-12
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef LEETCODE_MAX_WIDTH_RAMP_H
#define LEETCODE_MAX_WIDTH_RAMP_H

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
    return (stackPtr->data[stackPtr->stackTopIdx]);
}

void FreeMyStack(MyStack_T* stackPtr) {
    free(stackPtr->data);
    free(stackPtr);
    return ;
}

int maxWidthRamp(int* nums, int numsSize){
    MyStack_T* myStackPtr = NULL;
    myStackPtr = InitMyStack(numsSize);
    int ret = 0;

    PushMyStack(myStackPtr, 0); // init the first elem '0'

    int target = nums[0]; 
    for (int i = 1; i < numsSize; i++) {
        if (nums[i] <= target) {
            PushMyStack(myStackPtr, i);
            target = nums[i];
        }
    }

    for (int i = numsSize - 1; i >= 0; i--) {
        int popVal;
        while (!(IsEmptyMyStack(myStackPtr)) &&
            (nums[TopMyStack(myStackPtr)] <= nums[i])) {
            PopMyStack(myStackPtr, &popVal);
            ret = MAX(ret, i - popVal);
        }
    }

    FreeMyStack(myStackPtr);
    return ret;
}

// CANNOT PASS THE TIME LIMITATION
// int maxWidthRamp(int* nums, int numsSize){
//     int curMaxWidth = 0;

//     for (int i = 0; i < numsSize; i++) {
//         for (int j = i + 1; j < numsSize; j++) {
//             if (nums[i] <= nums[j]) {
//                 curMaxWidth = MAX(curMaxWidth, (j - i));
//             }
//         }
//     }

//     return curMaxWidth;
// }

#endif