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

bool Zuoru_IsFullQueue(ZUORU_QUEUE_T *queuePtr) {
    if (queuePtr->curSize == queuePtr->capacity) {
        return true;
    }
    return false;
}

bool Zuoru_IsEmptyQueue(ZUORU_QUEUE_T *queuePtr) {
    if (queuePtr->curSize == 0) {
        return true;
    }
    return false;
}

void Zuoru_FreeQueue(ZUORU_QUEUE_T *queuePtr) {
    free(queuePtr->data);
    free(queuePtr);
    return;
}

#endif
