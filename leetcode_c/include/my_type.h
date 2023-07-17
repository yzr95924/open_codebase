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

MyQueue_T* InitMyQueue(int capacity) {
    MyQueue_T* queuePtr = (MyQueue_T*)calloc(1, sizeof(MyQueue_T));
    queuePtr->data = (int*)calloc(capacity, sizeof(*(queuePtr->data)));
    queuePtr->head = EMPTY_POS;
    queuePtr->rear = EMPTY_POS;
    queuePtr->capacity = capacity;
    queuePtr->curSize = 0;

    return queuePtr;
}

void EnMyQueue(MyQueue_T* queuePtr, int* inVal) {
    if (queuePtr->head == EMPTY_POS) {
        queuePtr->head = 0;
    }
    queuePtr->rear = (queuePtr->rear + 1) % queuePtr->capacity;
    memcpy(&queuePtr->data[queuePtr->rear], inVal, sizeof(*(queuePtr->data)));

    queuePtr->curSize++;
    return;
}

void DeMyQueue(MyQueue_T* queuePtr, int* outVal) {
    memcpy(outVal, &queuePtr->data[queuePtr->head], sizeof(*(queuePtr->data)));

    if (queuePtr->head == queuePtr->rear) {
        queuePtr->rear = EMPTY_POS;
        queuePtr->head = EMPTY_POS;
    }
    queuePtr->head = (queuePtr->head + 1) % queuePtr->capacity;

    queuePtr->curSize--;
    return;
}

bool IsFullMyQueue(MyQueue_T* queuePtr) {
    if (queuePtr->curSize == queuePtr->capacity) {
        return true;
    }
    return false;
}

bool IsEmptyMyQueue(MyQueue_T* queuePtr) {
    if (queuePtr->curSize == 0) {
        return true;
    }
    return false;
}

void FreeMyQueue(MyQueue_T* queuePtr) {
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
    int* data;
    int capacity;
    int curSize;
} MyList_T;

MyList_T* InitMyList(int capacity) {
    MyList_T* listPtr = (MyList_T*)calloc(1, sizeof(MyList_T));
    listPtr->data = (int*)calloc(capacity, sizeof(*(listPtr->data)));
    listPtr->capacity = capacity;
    listPtr->curSize = 0;

    return listPtr;
}

bool IsFullMyList(MyList_T* listPtr) {
    if (listPtr->curSize == listPtr->capacity) {
        return true;
    }
    return false;
}

bool IsEmptyMyList(MyList_T* listPtr) {
    if (listPtr->curSize == 0) {
        return true;
    }
    return false;
}

void FreeMyList(MyList_T* listPtr) {
    free(listPtr->data);
    free(listPtr);
    return;
}

void AppendMyList(MyList_T* listPtr, int* inVal) {
    if (IsFullMyList(listPtr)) {
        printf("list is full.\n");
        return;
    }
    memcpy(&listPtr->data[listPtr->curSize], inVal, sizeof(*(listPtr->data)));
    listPtr->curSize++;
    return;
}

void InsertMyList(MyList_T* listPtr, int posIdx, int* inVal) {
    if (IsFullMyList(listPtr)) {
        printf("list is full.\n");
    }

    if (posIdx > listPtr->curSize) {
        printf("insert pos is invalid, posIdx: %d, curSize%d\n",
            posIdx, listPtr->curSize);
    }

    for (int i = listPtr->curSize - 1; i >= posIdx; i--) {
        listPtr->data[i + 1] = listPtr->data[i];
    }

    memcpy(&listPtr->data[listPtr->curSize], inVal, sizeof(*(listPtr->data)));
    listPtr->curSize++;

    return;
}

int FindMyList(MyList_T* listPtr, int inVal) {
    for (int i = 0; i < listPtr->curSize; i++) {
        if (listPtr->data[i] == inVal) {
            return i;
        }
    }

    return -1; // not found
}

bool DeleteMyList(MyList_T* listPtr, int posIdx, int* delVal) {
    if (IsEmptyMyList(listPtr)) {
        return false;
    }

    if (posIdx < 0 || posIdx >= listPtr->curSize) {
        return false;
    }

    *delVal = listPtr->data[posIdx];
    for (int i = posIdx; i < listPtr->curSize - 1; i++) {
        listPtr->data[i] = listPtr->data[i + 1];
    }

    listPtr->curSize--;
    return true;
}

void SortMyList(MyList_T* listPtr) {
    for (int i = 0; i < listPtr->curSize; i++) {
        for (int j = i + 1; j < listPtr->curSize; j++) {
            if (listPtr->data[i] > listPtr->data[j]) { // ascend
                int tmpVal = listPtr->data[i];
                listPtr->data[i] = listPtr->data[j];
                listPtr->data[j] = tmpVal;
            }
        }
    }
    return;
}

#endif