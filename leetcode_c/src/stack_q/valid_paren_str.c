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
typedef int Zuoru_Data;

typedef struct {
    Zuoru_Data *data;
    int stackTopIdx;
    int curSize;
    int capacity;
} Zuoru_Stack;

Zuoru_Stack* ZuoruInitStack(int capacity)
{
    Zuoru_Stack *stackPtr = (Zuoru_Stack*)calloc(1, sizeof(Zuoru_Stack));
    stackPtr->data = (Zuoru_Data*)calloc(capacity, sizeof(Zuoru_Data));
    stackPtr->stackTopIdx = MY_DATA_STRUCT_EMPTY_POS;
    stackPtr->capacity = capacity;
    stackPtr->curSize = 0;

    return stackPtr;
}

void ZuoruFreeStack(Zuoru_Stack *stackPtr)
{
    free(stackPtr->data);
    free(stackPtr);
    return;
}

bool ZuoruIsFullStack(Zuoru_Stack *stackPtr)
{
    if (stackPtr->stackTopIdx == (stackPtr->capacity - 1)) {
        return true;
    }
    return false;
}

bool ZuoruIsEmptyStack(Zuoru_Stack *stackPtr)
{
    if (stackPtr->stackTopIdx == MY_DATA_STRUCT_EMPTY_POS) {
        return true;
    }
    return false;
}

bool ZuoruPushStack(Zuoru_Stack *stackPtr, Zuoru_Data *inVal)
{
    if (ZuoruIsFullStack(stackPtr)) {
        fprintf(stderr, "stack is full\n");
        return false;
    }
    stackPtr->stackTopIdx++;
    memcpy(&stackPtr->data[stackPtr->stackTopIdx], inVal,
        sizeof(Zuoru_Data));
    stackPtr->curSize++;
    return true;
}

bool ZuoruPopStack(Zuoru_Stack *stackPtr, Zuoru_Data *outVal)
{
    if (ZuoruIsEmptyStack(stackPtr)) {
        fprintf(stderr, "stack is empty\n");
        return false;
    }

    memcpy(outVal, &stackPtr->data[stackPtr->stackTopIdx],
        sizeof(Zuoru_Data));
    stackPtr->stackTopIdx--;
    stackPtr->curSize--;
    return true;
}

bool ZuoruTopStack(Zuoru_Stack *stackPtr, Zuoru_Data *outVal)
{
    if (ZuoruIsEmptyStack(stackPtr)) {
        fprintf(stderr, "stack is empty");
        return false;
    }
    memcpy(outVal, &stackPtr->data[stackPtr->stackTopIdx],
        sizeof(Zuoru_Data));

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

    Zuoru_Stack *leftParenStk = ZuoruInitStack(100);
    Zuoru_Stack *starStk = ZuoruInitStack(100);
    Zuoru_Data tmpData;
    bool retAns = true;

    for (int idx = 0; idx < inputStrSize; idx++) {
        if (s[idx] == '(') {
            ZuoruPushStack(leftParenStk, &idx);
        } else if (s[idx] == '*') {
            ZuoruPushStack(starStk, &idx);
        } else if (s[idx] == ')') {
            if (!ZuoruIsEmptyStack(leftParenStk)) {
                ZuoruPopStack(leftParenStk, &tmpData);
                continue;
            }
            if (!ZuoruIsEmptyStack(starStk)) {
                ZuoruPopStack(starStk, &tmpData);
                continue;
            }
            retAns = false;
            break;
        } else {
            printf("wrong input char: %u\n", idx);
        }
    }

    if (!ZuoruIsEmptyStack(leftParenStk)) {
        int curLeftParenStkSize = leftParenStk->curSize;
        int curStarStkSize = starStk->curSize;
        Zuoru_Data leftIdx;
        Zuoru_Data starIdx;

        if (curStarStkSize >= curLeftParenStkSize) {
            for (int idx = 0; idx < curLeftParenStkSize; idx++) {
                ZuoruTopStack(leftParenStk, &leftIdx);
                ZuoruTopStack(starStk, &starIdx);

                if (starIdx < leftIdx) {
                    retAns = false;
                    break;
                }

                ZuoruPopStack(leftParenStk, &leftIdx);
                ZuoruPopStack(starStk, &starIdx);
            }
        } else {
            retAns = false;
        }
    }

    ZuoruFreeStack(leftParenStk);
    ZuoruFreeStack(starStk);

    return retAns;
}
