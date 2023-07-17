/**
 * @file zigzag_conversion.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/zigzag-conversion/
 * @version 0.1
 * @date 2023-03-17
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef LEETCODE_ZIGZAG_CONVERSION_H
#define LEETCODE_ZIGZAG_CONVERSION_H

#include "../const.h"

#define EMPTY_POS -1

typedef struct {
    char* data;
    int head;
    int rear;
    int capacity;
    int curSize;
} MyQueue_T;

MyQueue_T* InitMyQueue(int capacity) {
    MyQueue_T* queuePtr = (MyQueue_T*)calloc(1, sizeof(MyQueue_T));
    queuePtr->data = (char*)calloc(capacity, sizeof(*(queuePtr->data)));
    queuePtr->head = EMPTY_POS;
    queuePtr->rear = EMPTY_POS;
    queuePtr->capacity = capacity;
    queuePtr->curSize = 0;

    return queuePtr;
}

void EnMyQueue(MyQueue_T* queuePtr, char* inVal) {
    if (queuePtr->head == EMPTY_POS) {
        queuePtr->head = 0;
    }
    queuePtr->rear = (queuePtr->rear + 1) % queuePtr->capacity;
    memcpy(&queuePtr->data[queuePtr->rear], inVal, sizeof(*(queuePtr->data)));

    queuePtr->curSize++;
    return;
}

void DeMyQueue(MyQueue_T* queuePtr, char* outVal) {
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

char* convert(char* s, int numRows)
{
    int totalSize = strlen(s);
    char* retStr = (char*)malloc((totalSize + 1) * sizeof(char));

    MyQueue_T** tmpStrQueueArray = (MyQueue_T**)malloc(numRows * sizeof(MyQueue_T*));
    for (int i = 0; i < numRows; i++) {
        tmpStrQueueArray[i] = InitMyQueue(totalSize);
    }

    bool isDown = true;
    uint32_t curIdx = 0;
    for (int i = 0; i < totalSize; i++) {
        EnMyQueue(tmpStrQueueArray[curIdx], &s[i]);

        // adjust the curIdx
        if (numRows == 1) {
            curIdx = 0;
        } else {
            if (isDown) {
                // down
                if (curIdx == numRows - 1) {
                    curIdx--;
                    isDown = false;
                } else {
                    curIdx++;
                }
            } else {
                // up
                if (curIdx == 0) {
                    curIdx++;
                    isDown = true;
                } else {
                    curIdx--;
                }
            }
        }
    }

    uint32_t curOffset = 0;
    for (int i = 0; i < numRows; i++) {
        memcpy(retStr + curOffset, tmpStrQueueArray[i]->data, tmpStrQueueArray[i]->curSize);
        curOffset += tmpStrQueueArray[i]->curSize;
    }
    retStr[totalSize] = '\0';

    for (int i = 0; i < numRows; i++) {
        FreeMyQueue(tmpStrQueueArray[i]);
    }
    free(tmpStrQueueArray);

    return retStr;
}

#endif