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

#include "../const.h"
#include "../third/uthash.h"

#define EMPTY_POS -1

typedef struct {
    int* data;
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
    queuePtr->data = (int*)calloc(capacity, sizeof(int));
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
    memcpy(&queuePtr->data[queuePtr->rear], inVal, sizeof(int));

    queuePtr->curSize++;
    return ;
}

void DeMyQueue(MyQueue_T* queuePtr, int* outVal) {
    memcpy(outVal, &queuePtr->data[queuePtr->head], sizeof(int));
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
    int retAns = 0;

    // build the position map
    bool** connectionMap = (bool**)calloc(routesSize, sizeof(bool*));
    for (int i = 0; i < routesSize; i++) {
        connectionMap[i] = (bool*)calloc(routesSize, sizeof(bool));
    }

    PosMap_T* globalMap = NULL;
    for(int i = 0; i < routesSize; i++) {
        for (int j = 0; j < routesColSize[i]; j++) {
            int curPosIdx = routes[i][j];
            // find pos already in the map?
            PosMap_T* tempItem = NULL;
            HASH_FIND_INT(globalMap, &curPosIdx, tempItem);
            if (tempItem == NULL) {
                // not exist
                tempItem = (PosMap_T*)calloc(1, sizeof(PosMap_T));
                tempItem->posIdx = routes[i][j];
                tempItem->routesSet = (bool*)calloc(routesSize, sizeof(bool));
                tempItem->routesSet[i] = true;
                HASH_ADD_INT(globalMap, posIdx, tempItem);
            } else {
                // exist
                for (int k = 0; k < routesSize; k++) {
                    if (tempItem->routesSet[k] == true) {
                        connectionMap[i][k] = true;
                        connectionMap[k][i] = true;
                    }
                }
                tempItem->routesSet[i] = true;
            }
        }
    }

    int* dis2route = (int*)calloc(routesSize, sizeof(int));
    MyQueue_T* queuePtr = InitMyQueue(routesSize);

    do {
        // init the source
        PosMap_T* tempItem = NULL;
        HASH_FIND_INT(globalMap, &source, tempItem);
        if (tempItem != NULL) {
            for (int i = 0; i < routesSize; i++) {
                if (tempItem->routesSet[i] == true) {
                    EnMyQueue(queuePtr, &i);
                    dis2route[i] += 1;
                }
            }
        } else {
            retAns = -1;
            break;
        }

        while (!IsEmptyMyQueue(queuePtr)) {
            int curRouteIdx;
            DeMyQueue(queuePtr, &curRouteIdx);

            for (int i = 0; i < routesSize; i++) {
                if ((connectionMap[curRouteIdx][i] == true) &&
                    (dis2route[i] == 0)) {
                    dis2route[i] = dis2route[curRouteIdx] + 1;
                    EnMyQueue(queuePtr, &i);
                }
            }
        }

        retAns = INT_MAX;

        HASH_FIND_INT(globalMap, &target, tempItem);
        if (tempItem != NULL) {
            for (int i = 0; i < routesSize; i++) {
                if (tempItem->routesSet[i] == true) {
                    retAns = MIN(retAns, dis2route[i]);
                }
            }
        } else {
            retAns = -1;
            break;
        }

        if (retAns == INT_MAX || retAns == 0) {
            retAns = -1;
            break;
        }
    } while (0);

    // free the map
    PosMap_T* delItem = NULL;
    PosMap_T* fakeItem = NULL;
    HASH_ITER(hh, globalMap, delItem, fakeItem) {
        free(delItem->routesSet);
        HASH_DEL(globalMap, delItem);
        free(delItem);
    }

    for (int i = 0; i < routesSize; i++) {
        free(connectionMap[i]);
    }
    free(connectionMap);
    free(dis2route);
    FreeMyQueue(queuePtr);

    return retAns;
}

int numBusesToDestination(int** routes, int routesSize, int* routesColSize, int source, int target){
    if (source == target) {
        return 0;
    }

    return BFS(routes, routesSize, routesColSize, source, target);
}

#endif