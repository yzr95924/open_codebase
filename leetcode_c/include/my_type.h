/**
 * @file my_type.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief my data type
 * @version 0.1
 * @date 2023-02-08
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef LEETCODE_MY_TYPE_H
#define LEETCODE_MY_TYPE_H

#include "const.h"

#define EMPTY_POS -1

/**
 *********************************************
 ***               for queue
 ********************************************* 
 */

typedef struct {
    int* data;
    int head;
    int rear;
    int capacity;
    int curSize;
} MyQueue_T;

MyQueue_T* InitQueue(int capacity) {
    MyQueue_T* queuePtr = (MyQueue_T*)calloc(1, sizeof(MyQueue_T));
    queuePtr->data = (int*)calloc(capacity, sizeof(int));
    queuePtr->head = EMPTY_POS;
    queuePtr->rear = EMPTY_POS;
    queuePtr->capacity = capacity;
    queuePtr->curSize = 0;

    return queuePtr;
}

void EnQueue(MyQueue_T* queuePtr, int inVal) {
    if (queuePtr->head == EMPTY_POS) {
        queuePtr->head = 0;
    }
    queuePtr->rear = (queuePtr->rear + 1) % queuePtr->capacity;
    queuePtr->data[queuePtr->rear] = inVal;

    queuePtr->curSize++;
    return ;
}

void DeQueue(MyQueue_T* queuePtr, int* outVal) {
    *outVal = queuePtr->data[queuePtr->head];
    if (queuePtr->head == queuePtr->rear) {
        queuePtr->rear = EMPTY_POS;
        queuePtr->head = EMPTY_POS;
    } 
    queuePtr->head = (queuePtr->head + 1) % queuePtr->capacity;

    queuePtr->curSize--;
    return ;
}

bool IsFullQueue(MyQueue_T* queuePtr) {
    if (queuePtr->curSize == queuePtr->capacity) {
        return true;
    }
    return false;
}

bool IsEmptyQueue(MyQueue_T* queuePtr) {
    if (queuePtr->curSize == 0) {
        return true;
    }
    return false;
}

void FreeQueue(MyQueue_T* queuePtr) {
    free(queuePtr->data);
    free(queuePtr);
    return ;
}

/**
 *********************************************
 ***               for stack
 ********************************************* 
 */

typedef struct {
    int* data;
    int stackTopIdx;
    int curSize;
    int capacity;
} MyStack_T;

MyStack_T* InitStack(int capacity) {
    MyStack_T* stackPtr = (MyStack_T*)calloc(1, sizeof(MyStack_T));
    stackPtr->data = (int*)calloc(capacity, sizeof(int));
    stackPtr->stackTopIdx = EMPTY_POS;
    stackPtr->capacity = capacity;
    stackPtr->curSize = 0;

    return stackPtr;
}

bool IsFullStack(MyStack_T* stackPtr) {
    if (stackPtr->stackTopIdx == (stackPtr->capacity - 1)) {
        return true;
    } 
    return false;
}

bool IsEmptyStack(MyStack_T* stackPtr) {
    if (stackPtr->stackTopIdx == EMPTY_POS) {
        return true;
    }
    return false;
}

void PushStack(MyStack_T* stackPtr, int inVal) {
    if (IsFullStack(stackPtr)) {
        printf("stack is full.\n");
        return ;
    }
    stackPtr->stackTopIdx++;
    stackPtr->data[stackPtr->stackTopIdx] = inVal;
    stackPtr->curSize++;
    return ;
}

void PopStack(MyStack_T* stackPtr, int* outVal) {
    if (IsEmptyStack(stackPtr)) {
        printf("stack is empty.\n");
        return ;
    }
    
    *outVal = stackPtr->data[stackPtr->stackTopIdx];
    stackPtr->stackTopIdx--;
    stackPtr->curSize--;
    return ;
}

void FreeStack(MyStack_T* stackPtr) {
    free(stackPtr->data);
    free(stackPtr);
    return ;
}

#endif