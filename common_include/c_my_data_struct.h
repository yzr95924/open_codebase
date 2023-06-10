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
} ZUORU_LIST_T;

ZUORU_LIST_T* Zuoru_InitList(int capacity)
{
    ZUORU_LIST_T *listPtr = (ZUORU_LIST_T*)calloc(1, sizeof(ZUORU_LIST_T));
    listPtr->data = (ZUORU_DATA_T*)calloc(capacity, sizeof(ZUORU_DATA_T));
    listPtr->capacity = capacity;
    listPtr->curSize = 0;

    return listPtr;
}

bool Zuoru_IsFullList(ZUORU_LIST_T *listPtr)
{
    if (listPtr->curSize == listPtr->capacity) {
        return true;
    }
    return false;
}

bool Zuoru_IsEmptyList(ZUORU_LIST_T *listPtr)
{
    if (listPtr->curSize == 0) {
        return true;
    }
    return false;
}

void Zuoru_FreeList(ZUORU_LIST_T *listPtr)
{
    free(listPtr->data);
    free(listPtr);
}

bool Zuoru_AppendList(ZUORU_LIST_T *listPtr, ZUORU_DATA_T *inVal)
{
    if (Zuoru_IsFullList(listPtr)) {
        fprintf(stderr, "list is full\n");
        return false;
    }

    memcpy(&listPtr->data[listPtr->curSize], inVal, sizeof(ZUORU_DATA_T));
    listPtr->curSize++;

    return true;
}

bool Zuoru_InsertList(ZUORU_LIST_T *listPtr, int posIdx, ZUORU_DATA_T *inVal)
{
    if (Zuoru_IsFullList(listPtr)) {
        fprintf(stderr, "list is full\n");
        return false;
    }

    if (posIdx > listPtr->curSize) {
        fprintf(stderr, "list insert pos is invalid, posIdx: %d, curSize%d\n",
            posIdx, listPtr->curSize);
        return false;
    }

    for (int idx = listPtr->curSize - 1; idx >= posIdx; idx--) {
        memcpy(&listPtr->data[idx + 1], &listPtr->data[idx], sizeof(ZUORU_DATA_T));
    }

    memcpy(&listPtr->data[posIdx], inVal, sizeof(ZUORU_DATA_T));
    listPtr->curSize++;

    return true;
}

bool Zuoru_FindList(ZUORU_LIST_T *listPtr, ZUORU_DATA_T* inVal, int *posIdx)
{
    for (int idx = 0; idx < listPtr->curSize; idx++) {
        if (memcmp(&listPtr->data[idx], inVal, sizeof(ZUORU_DATA_T)) == 0) {
            *posIdx = idx;
            return true;
        }
    }

    return false;
}

bool Zuoru_DeleteList(ZUORU_LIST_T *listPtr, int posIdx, ZUORU_DATA_T *delVal)
{
    if (Zuoru_IsEmptyList(listPtr)) {
        fprintf(stderr, "list is empty\n");
        return false;
    }

    if (posIdx >= listPtr->curSize) {
        fprintf(stderr, "list del pos is invalid, posIdx: %d, curSize%d\n",
            posIdx, listPtr->curSize);
        return false;
    }

    memcpy(delVal, &listPtr->data[posIdx], sizeof(ZUORU_DATA_T));

    for (int idx = 0; idx < listPtr->curSize - 1; idx++) {
        memcpy(&listPtr->data[idx], &listPtr->data[idx + 1],
            sizeof(ZUORU_DATA_T));
    }

    listPtr->curSize--;
    return true;
}

void Zuoru_SortList(ZUORU_LIST_T *listPtr)
{
    qsort(listPtr->data, listPtr->curSize, sizeof(ZUORU_DATA_T), Zuoru_CompFunc);
    return ;
}


#endif
