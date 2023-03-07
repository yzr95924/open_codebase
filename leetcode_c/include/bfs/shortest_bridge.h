/**
 * @file shortest_bridge.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/shortest-bridge/description/
 * @version 0.1
 * @date 2023-03-05
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef LEETCODE_SHORTEST_BRIDGE_H
#define LEETCODE_SHORTEST_BRIDGE_H

#include "../const.h"

#define EMPTY_POS -1

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
    return ;
}

void DeMyQueue(MyQueue_T* queuePtr, int* outVal) {
    memcpy(outVal, &queuePtr->data[queuePtr->head], sizeof(*(queuePtr->data)));

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

int shortestBridge(int** grid, int gridSize, int* gridColSize){
    int n = gridSize;
    int gPosTable[][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};

    MyQueue_T* queuePtr = InitMyQueue(n * n);
    MyQueue_T* islandPtr = InitMyQueue(n * n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            // find the first island
            if (grid[i][j] == 1) {
                int tmpIdx = i * n + j; // include both x and y info
                EnMyQueue(queuePtr, &tmpIdx);
                grid[i][j] = -1;
                while (!IsEmptyMyQueue(queuePtr)) {
                    int curIdx = 0;
                    DeMyQueue(queuePtr, &curIdx);
                    int x = curIdx / n;
                    int y = curIdx % n;
                    EnMyQueue(islandPtr, &curIdx);

                    // search the first island
                    for (int k = 0; k < 4; k++) {
                        int nextX = x + gPosTable[k][0];
                        int nextY = y + gPosTable[k][1];
                        if (nextX >= 0 && nextY >=0 && nextX < n && nextY < n) {
                            if (grid[nextX][nextY] == 1) {
                                int newIdx = nextX * n + nextY;
                                EnMyQueue(queuePtr, &newIdx);
                                grid[nextX][nextY] = -1;
                            }
                        }
                    }
                }

                // find the next island based on the first island queue
                int totalStep = 0;
                while (!IsEmptyMyQueue(islandPtr)) {
                    int curQueueSize = islandPtr->curSize;
                    for (int i = 0; i < curQueueSize; i++) {
                        int curIdx;
                        DeMyQueue(islandPtr, &curIdx);
                        int x = curIdx / n;
                        int y = curIdx % n;

                        // search it next level
                        for (int k = 0; k < 4; k++) {
                            int nextX = x + gPosTable[k][0];
                            int nextY = y + gPosTable[k][1];
                            if (nextX >= 0 && nextY >=0 && nextX < n && nextY < n) {
                                if (grid[nextX][nextY] == 1) {
                                    FreeMyQueue(islandPtr);
                                    FreeMyQueue(queuePtr);
                                    return totalStep;
                                } else if (grid[nextX][nextY] == 0) {
                                    int newIdx = nextX * n + nextY;
                                    EnMyQueue(islandPtr, &newIdx);
                                    grid[nextX][nextY] = -1;
                                }
                            }
                        }
                    }
                    totalStep++;
                }
            }
        }
    }

    FreeMyQueue(islandPtr);
    FreeMyQueue(queuePtr);
    return 0;
}

#endif