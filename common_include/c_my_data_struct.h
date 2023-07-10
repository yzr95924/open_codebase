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

#define MY_DATA_STRUCT_EMPTY_POS (-1)
typedef int Zuoru_Data;

int ZuoruCompFunc(const void *rawInput1, const void *rawInput2)
{
    Zuoru_Data *input1 = (Zuoru_Data*)rawInput1;
    Zuoru_Data *input2 = (Zuoru_Data*)rawInput2;
    int ret = *input1 - *input2; // ascend

    return ret;
}

/**
 *********************************************
 ***               for queue
 *********************************************
 */

typedef struct {
    Zuoru_Data *data;
    int head;
    int rear;
    int capacity;
    int curSize;
} Zuoru_Queue;

Zuoru_Queue* ZuoruInitQueue(int capacity)
{
    Zuoru_Queue *queuePtr = (Zuoru_Queue*)calloc(1, sizeof(Zuoru_Queue));
    queuePtr->data = (Zuoru_Data*)calloc(capacity, sizeof(Zuoru_Data));
    queuePtr->head = MY_DATA_STRUCT_EMPTY_POS;
    queuePtr->rear = MY_DATA_STRUCT_EMPTY_POS;
    queuePtr->capacity = capacity;
    queuePtr->curSize = 0;

    return queuePtr;
}

bool ZuoruEnQueue(Zuoru_Queue *queuePtr, Zuoru_Data *inVal)
{
    if (queuePtr->curSize + 1 > queuePtr->capacity) {
        fprintf(stderr, "queue is full\n");
        return false;
    }

    if (queuePtr->head == MY_DATA_STRUCT_EMPTY_POS) {
        queuePtr->head = 0;
    }
    queuePtr->rear = (queuePtr->rear + 1) % queuePtr->capacity;
    memcpy(&queuePtr->data[queuePtr->rear], inVal, sizeof(Zuoru_Data));

    queuePtr->curSize++;
    return true;
}

bool ZuoruDeQueue(Zuoru_Queue *queuePtr, Zuoru_Data *outVal)
{
    if (queuePtr->curSize == 0) {
        fprintf(stderr, "queue is empty\n");
        return false;
    }

    memcpy(outVal, &queuePtr->data[queuePtr->head], sizeof(Zuoru_Data));
    if (queuePtr->head == queuePtr->rear) {
        queuePtr->rear = MY_DATA_STRUCT_EMPTY_POS;
        queuePtr->head = MY_DATA_STRUCT_EMPTY_POS;
    }
    queuePtr->head = (queuePtr->head + 1) % queuePtr->capacity;

    queuePtr->curSize--;
    return true;
}

bool ZuoruIsFullQueue(Zuoru_Queue *queuePtr)
{
    if (queuePtr->curSize == queuePtr->capacity) {
        return true;
    }
    return false;
}

bool ZuoruIsEmptyQueue(Zuoru_Queue *queuePtr)
{
    if (queuePtr->curSize == 0) {
        return true;
    }
    return false;
}

void ZuoruFreeQueue(Zuoru_Queue *queuePtr)
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
    Zuoru_Data *data;
    int capacity;
    int curSize;
} Zuoru_ArrList;

Zuoru_ArrList* ZuoruInitArrList(int capacity)
{
    Zuoru_ArrList *arrListPtr = (Zuoru_ArrList*)calloc(1, sizeof(Zuoru_ArrList));
    arrListPtr->data = (Zuoru_Data*)calloc(capacity, sizeof(Zuoru_Data));
    arrListPtr->capacity = capacity;
    arrListPtr->curSize = 0;

    return arrListPtr;
}

bool ZuoruIsFullArrList(Zuoru_ArrList *arrListPtr)
{
    if (arrListPtr->curSize == arrListPtr->capacity) {
        return true;
    }
    return false;
}

bool ZuoruIsEmptyArrList(Zuoru_ArrList *arrListPtr)
{
    if (arrListPtr->curSize == 0) {
        return true;
    }
    return false;
}

void ZuoruFreeArrList(Zuoru_ArrList *arrListPtr)
{
    free(arrListPtr->data);
    free(arrListPtr);
}

bool ZuoruAppendArrList(Zuoru_ArrList *arrListPtr, Zuoru_Data *inVal)
{
    if (ZuoruIsFullArrList(arrListPtr)) {
        fprintf(stderr, "list is full\n");
        return false;
    }

    memcpy(&arrListPtr->data[arrListPtr->curSize], inVal, sizeof(Zuoru_Data));
    arrListPtr->curSize++;

    return true;
}

bool ZuoruInsertArrList(Zuoru_ArrList *arrListPtr, int posIdx, Zuoru_Data *inVal)
{
    if (ZuoruIsFullArrList(arrListPtr)) {
        fprintf(stderr, "list is full\n");
        return false;
    }

    if (posIdx > arrListPtr->curSize) {
        fprintf(stderr, "list insert pos is invalid, posIdx: %d, curSize%d\n",
            posIdx, arrListPtr->curSize);
        return false;
    }

    for (int idx = arrListPtr->curSize - 1; idx >= posIdx; idx--) {
        memcpy(&arrListPtr->data[idx + 1], &arrListPtr->data[idx], sizeof(Zuoru_Data));
    }

    memcpy(&arrListPtr->data[posIdx], inVal, sizeof(Zuoru_Data));
    arrListPtr->curSize++;

    return true;
}

bool ZuoruFindArrList(Zuoru_ArrList *arrListPtr, Zuoru_Data* inVal, int *posIdx)
{
    for (int idx = 0; idx < arrListPtr->curSize; idx++) {
        if (memcmp(&arrListPtr->data[idx], inVal, sizeof(Zuoru_Data)) == 0) {
            *posIdx = idx;
            return true;
        }
    }

    return false;
}

bool ZuoruDeleteArrList(Zuoru_ArrList *arrListPtr, int posIdx, Zuoru_Data *delVal)
{
    if (ZuoruIsEmptyArrList(arrListPtr)) {
        fprintf(stderr, "list is empty\n");
        return false;
    }

    if (posIdx >= arrListPtr->curSize) {
        fprintf(stderr, "list del pos is invalid, posIdx: %d, curSize%d\n",
            posIdx, arrListPtr->curSize);
        return false;
    }

    memcpy(delVal, &arrListPtr->data[posIdx], sizeof(Zuoru_Data));

    for (int idx = 0; idx < arrListPtr->curSize - 1; idx++) {
        memcpy(&arrListPtr->data[idx], &arrListPtr->data[idx + 1],
            sizeof(Zuoru_Data));
    }

    arrListPtr->curSize--;
    return true;
}

void ZuoruSortArrList(Zuoru_ArrList *arrListPtr)
{
    qsort(arrListPtr->data, arrListPtr->curSize, sizeof(Zuoru_Data), ZuoruCompFunc);
    return;
}

/**
 *********************************************
 ***               for stack
 *********************************************
 */

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
 *********************************************
 ***               for double-linked list
 *********************************************
 */

struct Zuoru_DLList_Node {
    Zuoru_Data data;
    struct Zuoru_DLList_Node *next;
    struct Zuoru_DLList_Node *prev;
};

typedef struct Zuoru_DLList_Node Zuoru_DLList_Node;

typedef struct {
    Zuoru_DLList_Node *head;
    Zuoru_DLList_Node *tail;
    int curSize;
} Zuoru_DLList;

Zuoru_DLList* ZuoruInitDLList()
{
    Zuoru_DLList *dlListPtr = (Zuoru_DLList*)calloc(1, sizeof(Zuoru_DLList));
    dlListPtr->head = NULL;
    dlListPtr->tail = NULL;
    dlListPtr->curSize = 0;
    return dlListPtr;
}

void ZuoruFreeDLList(Zuoru_DLList *dlListPtr)
{
    Zuoru_DLList_Node *curNode = dlListPtr->head;
    Zuoru_DLList_Node *delNode = NULL;

    while (curNode != NULL) {
        delNode = curNode;
        curNode = curNode->next;
        free(delNode);
    }

    free(dlListPtr);
    return;
}

Zuoru_DLList_Node* ZuoruInsertHeadDLList(Zuoru_DLList *dlListPtr, Zuoru_Data *inVal)
{
    Zuoru_DLList_Node *newNode = (Zuoru_DLList_Node*)calloc(1, sizeof(Zuoru_DLList_Node));
    memcpy(&newNode->data, inVal, sizeof(Zuoru_Data));
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

Zuoru_DLList_Node* ZuoruInsertTailDLList(Zuoru_DLList *dlListPtr, Zuoru_Data *inVal)
{
    Zuoru_DLList_Node *newNode = (Zuoru_DLList_Node*)calloc(1, sizeof(Zuoru_DLList_Node));
    memcpy(&newNode->data, inVal, sizeof(Zuoru_Data));
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

Zuoru_DLList_Node* ZuoruInsertAfterNodeDLList(Zuoru_DLList *dlListPtr, Zuoru_DLList_Node *targetNode,
    Zuoru_DLList_Node *inVal)
{
    Zuoru_DLList_Node *newNode = (Zuoru_DLList_Node*)calloc(1, sizeof(Zuoru_DLList_Node));
    memcpy(newNode, inVal, sizeof(Zuoru_DLList_Node));
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

bool ZuoruFindDLList(Zuoru_DLList *dlListPtr, Zuoru_Data *inVal, Zuoru_DLList_Node *findNode)
{
    Zuoru_DLList_Node *curNode = dlListPtr->head;

    if (dlListPtr->curSize == 0) {
        return false;
    }

    while (memcmp(&curNode->data, inVal, sizeof(Zuoru_Data)) != 0) {
        if (curNode->next == NULL) {
            return false;
        } else {
            curNode = curNode->next;
        }
    }

    memcpy(findNode, curNode, sizeof(Zuoru_Data));
    return true;
}

bool ZuoruDelDLListWithPtr(Zuoru_DLList *dlListPtr, Zuoru_DLList_Node *targetNode)
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
