/**
 * @file valid_paren_str.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief
 * @version 0.1
 * @date 2023-02-24
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef LEETCODE_VALID_PAREN_STR_H
#define LEETCODE_VALID_PAREN_STR_H

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


bool checkValidString(char* s){
    int inputStrSize = strlen(s);

    MyStack_T* leftParenStackPtr = InitMyStack(inputStrSize);
    MyStack_T* starStackPtr = InitMyStack(inputStrSize);

    bool retAns = true;
    int retVal = 0;
    for (int i = 0; i < inputStrSize; i++) {
        if (s[i] == '(') {
            PushMyStack(leftParenStackPtr, i);
        } else if (s[i] == '*') {
            PushMyStack(starStackPtr,i);
        } else {
            if (!IsEmptyMyStack(leftParenStackPtr)) {
                PopMyStack(leftParenStackPtr, &retVal);
                continue;
            }

            if (!IsEmptyMyStack(starStackPtr)) {
                PopMyStack(starStackPtr, &retVal);
                continue;
            }

            retAns = false;
            break;
        }
    }

    if (!IsEmptyMyStack(leftParenStackPtr)) {
        int curLeftStackSize = leftParenStackPtr->curSize;
        int curStarStackSize = starStackPtr->curSize;

        if (curStarStackSize >= curLeftStackSize) {
            for (int i = 0; i < curLeftStackSize; i++) {
                int leftTop = TopMyStack(leftParenStackPtr);
                int starTop = TopMyStack(starStackPtr);

                if (starTop < leftTop) {
                    retAns = false;
                    break;
                }

                PopMyStack(leftParenStackPtr, &retVal);
                PopMyStack(starStackPtr, &retVal);
            }
        } else {
            retAns = false;
        }
    }

    FreeMyStack(leftParenStackPtr);
    FreeMyStack(starStackPtr);

    return retAns;
}

#endif