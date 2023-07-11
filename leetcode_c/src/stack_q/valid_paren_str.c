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

#define MY_DATA_STRUCT_EMPTY_POS (-1)
typedef int ZUORU_DataItem;

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

    ZUORU_Stack *leftParenStk = ZUORU_InitStack(100);
    ZUORU_Stack *starStk = ZUORU_InitStack(100);
    ZUORU_DataItem tmpData;
    bool retAns = true;

    for (int idx = 0; idx < inputStrSize; idx++) {
        if (s[idx] == '(') {
            ZUORU_PushStack(leftParenStk, &idx);
        } else if (s[idx] == '*') {
            ZUORU_PushStack(starStk, &idx);
        } else if (s[idx] == ')') {
            if (!ZUORU_IsEmptyStack(leftParenStk)) {
                ZUORU_PopStack(leftParenStk, &tmpData);
                continue;
            }
            if (!ZUORU_IsEmptyStack(starStk)) {
                ZUORU_PopStack(starStk, &tmpData);
                continue;
            }
            retAns = false;
            break;
        } else {
            printf("wrong input char: %u\n", idx);
        }
    }

    if (!ZUORU_IsEmptyStack(leftParenStk)) {
        int curLeftParenStkSize = leftParenStk->curSize;
        int curStarStkSize = starStk->curSize;
        ZUORU_DataItem leftIdx;
        ZUORU_DataItem starIdx;

        if (curStarStkSize >= curLeftParenStkSize) {
            for (int idx = 0; idx < curLeftParenStkSize; idx++) {
                ZUORU_TopStack(leftParenStk, &leftIdx);
                ZUORU_TopStack(starStk, &starIdx);

                if (starIdx < leftIdx) {
                    retAns = false;
                    break;
                }

                ZUORU_PopStack(leftParenStk, &leftIdx);
                ZUORU_PopStack(starStk, &starIdx);
            }
        } else {
            retAns = false;
        }
    }

    ZUORU_FreeStack(leftParenStk);
    ZUORU_FreeStack(starStk);

    return retAns;
}
