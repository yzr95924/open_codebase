/**
 * @file plus_one.c
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/plus-one/
 * @version 0.1
 * @date 2023-07-12
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../../include/math_q.h"
#include "../../../common_include/c_include.h"

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
 * @brief 66. Plus One
 *
 * @param digits input digits
 * @param digitsSize input digits size
 * @param returnSize return size
 * @return int* return array
 */
int* plusOne(int* digits, int digitsSize, int* returnSize)
{
    ZUORU_Stack *stackPtr = ZUORU_InitStack(100);
    int weight = 0;
    int curDigit = 0;

    curDigit = (digits[digitsSize - 1] + 1) % 10;
    if (digits[digitsSize - 1] + 1 > 9) {
        weight = 1;
    }
    ZUORU_PushStack(stackPtr, &curDigit);
    for (int idx = digitsSize - 2; idx >= 0; idx--) {
        curDigit = (digits[idx] + weight) % 10;
        if (digits[idx] + weight > 9) {
            weight = 1;
        } else {
            weight = 0;
        }
        ZUORU_PushStack(stackPtr, &curDigit);
    }
    if (weight == 1) {
        ZUORU_PushStack(stackPtr, &weight);
    }

    *returnSize = stackPtr->curSize;
    int *retArray = (int*)calloc(*returnSize, sizeof(int));

    for (int idx = 0; idx < *returnSize; idx++) {
        ZUORU_PopStack(stackPtr, &retArray[idx]);
    }

    ZUORU_FreeStack(stackPtr);

    return retArray;
}
