/**
 * @file my_data_struct.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief my data struct
 * @version 0.1
 * @date 2023-06-08
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef MY_DATA_STRUCT_H
#define MY_DATA_STRUCT_H

#include "define_const.h"
#include "c_include.h"

#define MY_DATA_STRUCT_EMPTY_POS -1

typedef int ZUORU_DATA_T;

int Zuoru_CompFunc(const void *rawInput1, const void *rawInput2)
{
    ZUORU_DATA_T *input1 = (ZUORU_DATA_T*)rawInput1;
    ZUORU_DATA_T *input2 = (ZUORU_DATA_T*)rawInput2;
    int ret = *input1 - *input2; // ascend

    return ret;
}

/**
 *********************************************
 ***               for queue
 *********************************************
 */

typedef struct {
    ZUORU_DATA_T *data;
    int head;
    int rear;
    int capacity;
    int curSize;
} ZUORU_QUEUE_T;

ZUORU_QUEUE_T* Zuoru_InitQueue(int capacity)
{
    ZUORU_QUEUE_T *queuePtr = (ZUORU_QUEUE_T*)calloc(1, sizeof(ZUORU_QUEUE_T));
    queuePtr->data = (ZUORU_DATA_T*)calloc(capacity, sizeof(ZUORU_DATA_T));
    queuePtr->head = MY_DATA_STRUCT_EMPTY_POS;
    queuePtr->rear = MY_DATA_STRUCT_EMPTY_POS;
    queuePtr->capacity = capacity;
    queuePtr->curSize = 0;

    return queuePtr;
}

bool Zuoru_EnQueue(ZUORU_QUEUE_T *queuePtr, ZUORU_DATA_T *inVal)
{
    if (unlikely(queuePtr->curSize + 1 > queuePtr->capacity)) {
        fprintf(stderr, "queue is full\n");
        return false;
    }

    if (queuePtr->head == MY_DATA_STRUCT_EMPTY_POS) {
        queuePtr->head = 0;
    }
    queuePtr->rear = (queuePtr->rear + 1) % queuePtr->capacity;
    memcpy(&queuePtr->data[queuePtr->rear], inVal, sizeof(ZUORU_DATA_T));

    queuePtr->curSize++;
    return true;
}

bool Zuoru_DeQueue(ZUORU_QUEUE_T *queuePtr, ZUORU_DATA_T *outVal)
{
    if (unlikely(queuePtr->curSize == 0)) {
        fprintf(stderr, "queue is empty\n");
        return false;
    }

    memcpy(outVal, &queuePtr->data[queuePtr->head], sizeof(ZUORU_DATA_T));
    if (queuePtr->head == queuePtr->rear) {
        queuePtr->rear = MY_DATA_STRUCT_EMPTY_POS;
        queuePtr->head = MY_DATA_STRUCT_EMPTY_POS;
    }
    queuePtr->head = (queuePtr->head + 1) % queuePtr->capacity;

    queuePtr->curSize--;
    return true;
}

bool Zuoru_IsFullQueue(ZUORU_QUEUE_T *queuePtr)
{
    if (queuePtr->curSize == queuePtr->capacity) {
        return true;
    }
    return false;
}

bool Zuoru_IsEmptyQueue(ZUORU_QUEUE_T *queuePtr)
{
    if (queuePtr->curSize == 0) {
        return true;
    }
    return false;
}

void Zuoru_FreeQueue(ZUORU_QUEUE_T *queuePtr)
{
    free(queuePtr->data);
    free(queuePtr);
    return;
}

/**
 *********************************************
 ***               for list
 *********************************************
 */

typedef struct {
    ZUORU_DATA_T *data;
    int capacity;
    int curSize;
} ZUORU_ARR_LIST_T;

ZUORU_ARR_LIST_T* Zuoru_InitArrList(int capacity)
{
    ZUORU_ARR_LIST_T *arrListPtr = (ZUORU_ARR_LIST_T*)calloc(1, sizeof(ZUORU_ARR_LIST_T));
    arrListPtr->data = (ZUORU_DATA_T*)calloc(capacity, sizeof(ZUORU_DATA_T));
    arrListPtr->capacity = capacity;
    arrListPtr->curSize = 0;

    return arrListPtr;
}

bool Zuoru_IsFullArrList(ZUORU_ARR_LIST_T *arrListPtr)
{
    if (arrListPtr->curSize == arrListPtr->capacity) {
        return true;
    }
    return false;
}

bool Zuoru_IsEmptyArrList(ZUORU_ARR_LIST_T *arrListPtr)
{
    if (arrListPtr->curSize == 0) {
        return true;
    }
    return false;
}

void Zuoru_FreeArrList(ZUORU_ARR_LIST_T *arrListPtr)
{
    free(arrListPtr->data);
    free(arrListPtr);
}

bool Zuoru_AppendArrList(ZUORU_ARR_LIST_T *arrListPtr, ZUORU_DATA_T *inVal)
{
    if (Zuoru_IsFullArrList(arrListPtr)) {
        fprintf(stderr, "list is full\n");
        return false;
    }

    memcpy(&arrListPtr->data[arrListPtr->curSize], inVal, sizeof(ZUORU_DATA_T));
    arrListPtr->curSize++;

    return true;
}

bool Zuoru_InsertArrList(ZUORU_ARR_LIST_T *arrListPtr, int posIdx, ZUORU_DATA_T *inVal)
{
    if (Zuoru_IsFullArrList(arrListPtr)) {
        fprintf(stderr, "list is full\n");
        return false;
    }

    if (posIdx > arrListPtr->curSize) {
        fprintf(stderr, "list insert pos is invalid, posIdx: %d, curSize%d\n",
            posIdx, arrListPtr->curSize);
        return false;
    }

    for (int idx = arrListPtr->curSize - 1; idx >= posIdx; idx--) {
        memcpy(&arrListPtr->data[idx + 1], &arrListPtr->data[idx], sizeof(ZUORU_DATA_T));
    }

    memcpy(&arrListPtr->data[posIdx], inVal, sizeof(ZUORU_DATA_T));
    arrListPtr->curSize++;

    return true;
}

bool Zuoru_FindArrList(ZUORU_ARR_LIST_T *arrListPtr, ZUORU_DATA_T* inVal, int *posIdx)
{
    for (int idx = 0; idx < arrListPtr->curSize; idx++) {
        if (memcmp(&arrListPtr->data[idx], inVal, sizeof(ZUORU_DATA_T)) == 0) {
            *posIdx = idx;
            return true;
        }
    }

    return false;
}

bool Zuoru_DeleteArrList(ZUORU_ARR_LIST_T *arrListPtr, int posIdx, ZUORU_DATA_T *delVal)
{
    if (Zuoru_IsEmptyArrList(arrListPtr)) {
        fprintf(stderr, "list is empty\n");
        return false;
    }

    if (posIdx >= arrListPtr->curSize) {
        fprintf(stderr, "list del pos is invalid, posIdx: %d, curSize%d\n",
            posIdx, arrListPtr->curSize);
        return false;
    }

    memcpy(delVal, &arrListPtr->data[posIdx], sizeof(ZUORU_DATA_T));

    for (int idx = 0; idx < arrListPtr->curSize - 1; idx++) {
        memcpy(&arrListPtr->data[idx], &arrListPtr->data[idx + 1],
            sizeof(ZUORU_DATA_T));
    }

    arrListPtr->curSize--;
    return true;
}

void Zuoru_SortArrList(ZUORU_ARR_LIST_T *arrListPtr)
{
    qsort(arrListPtr->data, arrListPtr->curSize, sizeof(ZUORU_DATA_T), Zuoru_CompFunc);
    return;
}

/**
 *********************************************
 ***               for stack
 *********************************************
 */

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
 *********************************************
 ***               for double-linked list
 *********************************************
 */

struct ZUORU_DL_LIST_NODE_T {
    ZUORU_DATA_T data;
    struct ZUORU_DL_LIST_NODE_T *next;
    struct ZUORU_DL_LIST_NODE_T *prev;
};

typedef struct ZUORU_DL_LIST_NODE_T ZUORU_DL_LIST_NODE_T;

typedef struct {
    ZUORU_DL_LIST_NODE_T *head;
    ZUORU_DL_LIST_NODE_T *tail;
    int curSize;
} ZUORU_DL_LIST_T;

ZUORU_DL_LIST_T* Zuoru_InitDLList()
{
    ZUORU_DL_LIST_T *dlListPtr = (ZUORU_DL_LIST_T*)calloc(1, sizeof(ZUORU_DL_LIST_T));
    dlListPtr->head = NULL;
    dlListPtr->tail = NULL;
    dlListPtr->curSize = 0;
    return dlListPtr;
}

void Zuoru_FreeDLList(ZUORU_DL_LIST_T *dlListPtr)
{
    ZUORU_DL_LIST_NODE_T *curNode = dlListPtr->head;
    ZUORU_DL_LIST_NODE_T *delNode = NULL;

    while (curNode != NULL) {
        delNode = curNode;
        curNode = curNode->next;
        free(delNode);
    }

    free(dlListPtr);
    return;
}

ZUORU_DL_LIST_NODE_T* Zuoru_InsertHeadDLList(ZUORU_DL_LIST_T *dlListPtr, ZUORU_DATA_T *inVal)
{
    ZUORU_DL_LIST_NODE_T *newNode = (ZUORU_DL_LIST_NODE_T*)calloc(1, sizeof(ZUORU_DL_LIST_NODE_T));
    memcpy(&newNode->data, inVal, sizeof(ZUORU_DATA_T));
    newNode->next = NULL;
    newNode->prev = NULL;

    if (dlListPtr->curSize == 0) {
        dlListPtr->tail = newNode;
    } else {
        dlListPtr->head->prev = newNode;
        newNode->next = dlListPtr->head;
    }

    dlListPtr->head = newNode;
    dlListPtr->curSize++;

    return newNode;
}

ZUORU_DL_LIST_NODE_T* Zuoru_InsertTailDLList(ZUORU_DL_LIST_T *dlListPtr, ZUORU_DATA_T *inVal)
{
    ZUORU_DL_LIST_NODE_T *newNode = (ZUORU_DL_LIST_NODE_T*)calloc(1, sizeof(ZUORU_DL_LIST_NODE_T));
    memcpy(&newNode->data, inVal, sizeof(ZUORU_DATA_T));
    newNode->next = NULL;
    newNode->prev = NULL;

    if (dlListPtr->curSize == 0) {
        dlListPtr->head = newNode;
    } else {
        dlListPtr->tail->next = newNode;
        newNode->prev = dlListPtr->tail;
    }

    dlListPtr->tail = newNode;
    dlListPtr->curSize++;

    return newNode;
}

ZUORU_DL_LIST_NODE_T* Zuoru_InsertAfterNodeDLList(ZUORU_DL_LIST_T *dlListPtr, ZUORU_DL_LIST_NODE_T *targetNode,
    ZUORU_DL_LIST_NODE_T *inVal)
{
    ZUORU_DL_LIST_NODE_T *newNode = (ZUORU_DL_LIST_NODE_T*)calloc(1, sizeof(ZUORU_DL_LIST_NODE_T));
    memcpy(newNode, inVal, sizeof(ZUORU_DL_LIST_NODE_T));
    newNode->next = NULL;
    newNode->prev = NULL;

    if (targetNode == dlListPtr->tail) {
        newNode->next = NULL;
        dlListPtr->tail = newNode;
    } else {
        newNode->next = targetNode->next;
        targetNode->next->prev = newNode;
    }

    newNode->prev = targetNode;
    targetNode->next = newNode;
    dlListPtr->curSize++;
    return newNode;
}

bool Zuoru_FindDLList(ZUORU_DL_LIST_T *dlListPtr, ZUORU_DATA_T *inVal, ZUORU_DL_LIST_NODE_T *findNode)
{
    ZUORU_DL_LIST_NODE_T *curNode = dlListPtr->head;

    if (dlListPtr->curSize == 0) {
        return false;
    }

    while (memcmp(&curNode->data, inVal, sizeof(ZUORU_DATA_T)) != 0) {
        if (curNode->next == NULL) {
            return false;
        } else {
            curNode = curNode->next;
        }
    }

    memcpy(findNode, curNode, sizeof(ZUORU_DATA_T));
    return true;
}

bool Zuoru_DelDLListWithPtr(ZUORU_DL_LIST_T *dlListPtr, ZUORU_DL_LIST_NODE_T *targetNode)
{
    if (dlListPtr->curSize == 0) {
        return false;
    }

    if (targetNode == dlListPtr->head) {
        dlListPtr->head = targetNode->next;
    } else {
        targetNode->prev->next = targetNode->next;
    }

    if (targetNode == dlListPtr->tail) {
        dlListPtr->tail = targetNode->prev;
    } else {
        targetNode->next->prev = targetNode->prev;
    }

    dlListPtr->curSize--;
    free(targetNode);
    return true;
}

#endif
