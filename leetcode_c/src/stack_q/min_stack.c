/**
 * @file min_stack.c
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/min-stack/
 * @version 0.1
 * @date 2023-07-23
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

MinStack* minStackCreate() {
    MinStack *ret = calloc(1, sizeof(MinStack));
    ret->minStack = ZUORU_InitStack(30000);
    ret->realStack = ZUORU_InitStack(30000);
    return ret;
}

void minStackPush(MinStack* obj, int val) {
    ZUORU_Stack *minStack = (ZUORU_Stack*)obj->minStack;
    ZUORU_Stack *realStack = (ZUORU_Stack*)obj->realStack;
    ZUORU_DataItem tmpMin;

    ZUORU_PushStack(realStack, &val);
    if (!ZUORU_IsEmptyStack(minStack)) {
        ZUORU_TopStack(minStack, &tmpMin);
        if (val < tmpMin) {
            ZUORU_PushStack(minStack, &val);
        } else {
            ZUORU_PushStack(minStack, &tmpMin);
        }
    } else {
        ZUORU_PushStack(minStack, &val);
    }
    return;
}

void minStackPop(MinStack* obj) {
    ZUORU_Stack *minStack = (ZUORU_Stack*)obj->minStack;
    ZUORU_Stack *realStack = (ZUORU_Stack*)obj->realStack;
    ZUORU_DataItem tmpData;
    ZUORU_PopStack(minStack, &tmpData);
    ZUORU_PopStack(realStack, &tmpData);
    return;
}

int minStackTop(MinStack* obj) {
    ZUORU_Stack *realStack = (ZUORU_Stack*)obj->realStack;
    ZUORU_DataItem ret;
    ZUORU_TopStack(realStack, &ret);
    return ret;
}

int minStackGetMin(MinStack* obj) {
    ZUORU_Stack *minStack = (ZUORU_Stack*)obj->minStack;
    ZUORU_DataItem ret;
    ZUORU_TopStack(minStack, &ret);
    return ret;
}

void minStackFree(MinStack* obj) {
    ZUORU_FreeStack(obj->minStack);
    ZUORU_FreeStack(obj->realStack);
    free(obj);
}
