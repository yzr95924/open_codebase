/**
 * @file bus_routes.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/bus-routes/
 * @version 0.1
 * @date 2023-03-04
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef LEETCODE_BUS_ROUTES_H
#define LEETCODE_BUS_ROUTES_H

#define EMPTY_POS -1

#include "../const.h"
#include "../third/uthash.h"

typedef struct {
    int posIdx;
    int curStep;
} StepWrapper_T;

typedef struct {
    StepWrapper_T* data;
    int head;
    int rear;
    int capacity;
    int curSize;
} MyQueue_T;

typedef struct {
    int posIdx;
    bool* routesSet;
    UT_hash_handle hh;
} PosMap_T;

MyQueue_T* InitMyQueue(int capacity) {
    MyQueue_T* queuePtr = (MyQueue_T*)calloc(1, sizeof(MyQueue_T));
    queuePtr->data = (StepWrapper_T*)calloc(capacity, sizeof(StepWrapper_T));
    queuePtr->head = EMPTY_POS;
    queuePtr->rear = EMPTY_POS;
    queuePtr->capacity = capacity;
    queuePtr->curSize = 0;

    return queuePtr;
}

void EnMyQueue(MyQueue_T* queuePtr, StepWrapper_T* inVal) {
    if (queuePtr->head == EMPTY_POS) {
        queuePtr->head = 0;
    }
    queuePtr->rear = (queuePtr->rear + 1) % queuePtr->capacity;
    memcpy(&queuePtr->data[queuePtr->rear], inVal, sizeof(StepWrapper_T));

    queuePtr->curSize++;
    return ;
}

void DeMyQueue(MyQueue_T* queuePtr, StepWrapper_T* outVal) {
    memcpy(outVal, &queuePtr->data[queuePtr->head], sizeof(StepWrapper_T));
    if (queuePtr->head == queuePtr->rear) {
        queuePtr->rear = EMPTY_POS;
        queuePtr->head = EMPTY_POS;
    }
    queuePtr->head = (queuePtr->head + 1) % queuePtr->capacity;

    queuePtr->curSize--;
    return ;
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
    return ;
}

static int BFS(int** routes, int routesSize, int* routesColSize, int source, int target) {
    if (source == target) {
        return 0;
    }

    // build the position map
    PosMap_T* globalMap = NULL;
    for(int i = 0; i < routesSize; i++) {
        for (int j = 0; j < routesColSize[i]; j++) {
            // find pos already in the map?
            PosMap_T* tempItem = NULL;
            HASH_FIND_INT(globalMap, &routes[i][j], tempItem);
            if (tempItem == NULL) {
                // not exist
                tempItem = (PosMap_T*)calloc(1, sizeof(PosMap_T));
                tempItem->posIdx = routes[i][j];
                tempItem->routesSet = (bool*)calloc(routesSize, sizeof(bool));
                tempItem->routesSet[i] = true;
                HASH_ADD_INT(globalMap, posIdx, tempItem);
            } else {
                // exist
                tempItem->routesSet[i] = true;
            }
        }
    }

    // StepWrapper_T curStepWrapper;
    // StepWrapper_T inputStepWrapper;

    // bool* isUsed = (bool*)calloc(routesSize, sizeof(bool));
    // MyQueue_T* queuePtr = InitMyQueue(routesSize);

    // inputStepWrapper.posIdx = source;
    // inputStepWrapper.curStep = 0;



    // FreeMyQueue(queuePtr);

    // free the map
    PosMap_T* delItem = NULL;
    PosMap_T* fakeItem = NULL;
    HASH_ITER(hh, globalMap, delItem, fakeItem) {
        printf("pos: %d: routes: ", delItem->posIdx);
        for (int i = 0; i < routesSize; i++) {
            if (delItem->routesSet[i] == true) {
                printf("%d ", i);
            }
        }
        printf("\n");
        free(delItem->routesSet);
        HASH_DEL(globalMap, delItem);
        free(delItem);
    }

    return 0;
}

int numBusesToDestination(int** routes, int routesSize, int* routesColSize, int source, int target){
    return BFS(routes, routesSize, routesColSize, source, target);
}

#endif