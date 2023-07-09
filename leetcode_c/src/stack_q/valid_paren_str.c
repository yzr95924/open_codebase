/**
 * @file valid_paren_str.c
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/valid-parenthesis-string/
 * @version 0.1
 * @date 2023-07-10
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../../include/stack_q.h"

#define MY_DATA_STRUCT_EMPTY_POS -1
typedef int ZUORU_DATA_T;

typedef struct {
    ZUORU_DATA_T *data;
    int stackTopIdx;
    int curSize;
    int capacity;
} ZUORU_STACK_T;

ZUORU_STACK_T* Zuoru_InitStack(int capacity)
{
    ZUORU_STACK_T *stackPtr = (ZUORU_STACK_T*)calloc(1, sizeof(ZUORU_STACK_T));
    stackPtr->data = (ZUORU_DATA_T*)calloc(capacity, sizeof(ZUORU_DATA_T));
    stackPtr->stackTopIdx = MY_DATA_STRUCT_EMPTY_POS;
    stackPtr->capacity = capacity;
    stackPtr->curSize = 0;

    return stackPtr;
}

void Zuoru_FreeStack(ZUORU_STACK_T *stackPtr)
{
    free(stackPtr->data);
    free(stackPtr);
    return;
}

bool Zuoru_IsFullStack(ZUORU_STACK_T *stackPtr)
{
    if (stackPtr->stackTopIdx == (stackPtr->capacity - 1)) {
        return true;
    }
    return false;
}

bool Zuoru_IsEmptyStack(ZUORU_STACK_T *stackPtr)
{
    if (stackPtr->stackTopIdx == MY_DATA_STRUCT_EMPTY_POS) {
        return true;
    }
    return false;
}

bool Zuoru_PushStack(ZUORU_STACK_T *stackPtr, ZUORU_DATA_T *inVal)
{
    if (Zuoru_IsFullStack(stackPtr)) {
        fprintf(stderr, "stack is full\n");
        return false;
    }
    stackPtr->stackTopIdx++;
    memcpy(&stackPtr->data[stackPtr->stackTopIdx], inVal,
        sizeof(ZUORU_DATA_T));
    stackPtr->curSize++;
    return true;
}

bool Zuoru_PopStack(ZUORU_STACK_T *stackPtr, ZUORU_DATA_T *outVal)
{
    if (Zuoru_IsEmptyStack(stackPtr)) {
        fprintf(stderr, "stack is empty\n");
        return false;
    }

    memcpy(outVal, &stackPtr->data[stackPtr->stackTopIdx],
        sizeof(ZUORU_DATA_T));
    stackPtr->stackTopIdx--;
    stackPtr->curSize--;
    return true;
}

bool Zuoru_TopStack(ZUORU_STACK_T *stackPtr, ZUORU_DATA_T *outVal)
{
    if (Zuoru_IsEmptyStack(stackPtr)) {
        fprintf(stderr, "stack is empty");
        return false;
    }
    memcpy(outVal, &stackPtr->data[stackPtr->stackTopIdx],
        sizeof(ZUORU_DATA_T));

    return true;
}

/**
 * @brief 678. Valid Parenthesis String
 *
 * @param s input str
 * @return true
 * @return false
 */
bool checkValidString(char * s)
{
    int inputStrSize = strlen(s);

    ZUORU_STACK_T *leftParenStk = Zuoru_InitStack(100);
    ZUORU_STACK_T *starStk = Zuoru_InitStack(100);
    ZUORU_DATA_T tmpData;
    bool retAns = true;

    for (int idx = 0; idx < inputStrSize; idx++) {
        if (s[idx] == '(') {
            Zuoru_PushStack(leftParenStk, &idx);
        } else if (s[idx] == '*') {
            Zuoru_PushStack(starStk, &idx);
        } else if (s[idx] == ')') {
            if (!Zuoru_IsEmptyStack(leftParenStk)) {
                Zuoru_PopStack(leftParenStk, &tmpData);
                continue;
            }
            if (!Zuoru_IsEmptyStack(starStk)) {
                Zuoru_PopStack(starStk, &tmpData);
                continue;
            }
            retAns = false;
            break;
        } else {
            printf("wrong input char: %u\n", idx);
        }
    }

    if (!Zuoru_IsEmptyStack(leftParenStk)) {
        int curLeftParenStkSize = leftParenStk->curSize;
        int curStarStkSize = starStk->curSize;
        ZUORU_DATA_T leftIdx;
        ZUORU_DATA_T starIdx;

        if (curStarStkSize >= curLeftParenStkSize) {
            for (int idx = 0; idx < curLeftParenStkSize; idx++) {
                Zuoru_TopStack(leftParenStk, &leftIdx);
                Zuoru_TopStack(starStk, &starIdx);

                if (starIdx < leftIdx) {
                    retAns = false;
                    break;
                }

                Zuoru_PopStack(leftParenStk, &leftIdx);
                Zuoru_PopStack(starStk, &starIdx);
            }
        } else {
            retAns = false;
        }
    }

    Zuoru_FreeStack(leftParenStk);
    Zuoru_FreeStack(starStk);

    return retAns;
}
