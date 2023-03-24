/**
 * @file merge_intervals.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/merge-intervals/description/?favorite=2cktkvj
 * @version 0.1
 * @date 2023-03-23
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef LEETCODE_MERGE_INTERVALS_H
#define LEETCODE_MERGE_INTERVALS_H

#include "../const.h"

typedef struct {
    int leftBound;
    int rightBound;
} Interval_T;

int CompFunc(const void* inputA, const void* inputB)
{
    Interval_T* inputAPtr = (Interval_T*)inputA;
    Interval_T* inputBPtr = (Interval_T*)inputB;

    return (inputAPtr->leftBound - inputBPtr->leftBound); // ascend
}

int** merge(int** intervals, int intervalsSize, int* intervalsColSize,
    int* returnSize, int** returnColumnSizes)
{
    int** retIntervalPtr = NULL;
    int intervalWidth = intervalsColSize[0];
    retIntervalPtr = (int**)calloc(intervalsSize, sizeof(int*));
    for (int i = 0; i < intervalsSize; i++) {
        retIntervalPtr[i] = (int*)calloc(intervalWidth, sizeof(int));
    }

    if (1 == intervalsSize) {
        *returnSize = 1;
        memcpy(retIntervalPtr[0], &intervals[0][0], sizeof(int) * intervalWidth);
        return retIntervalPtr;
    }

    int totalIntervalSize = 0;
    Interval_T* intervalArray = (Interval_T*)calloc(intervalsSize, sizeof(Interval_T));
    for (int i = 0; i < intervalsSize; i++) {
        intervalArray[i].leftBound = intervals[i][0];
        intervalArray[i].rightBound = intervals[i][1];
    }

    qsort(intervalArray, intervalsSize, sizeof(Interval_T), CompFunc);

    int curTail = 0;
    for (int i = 0; i < intervalsSize; i++) {
        int curLeft = intervalArray[i].leftBound;
        int curRight = intervalArray[i].rightBound;

        if (totalIntervalSize == 0) {
            retIntervalPtr[totalIntervalSize][0] = curLeft;
            retIntervalPtr[totalIntervalSize][1] = curRight;
            curTail = 0;
            totalIntervalSize++;
            continue;
        }

        if (retIntervalPtr[curTail][1] < curLeft) {
            retIntervalPtr[totalIntervalSize][0] = curLeft;
            retIntervalPtr[totalIntervalSize][1] = curRight;
            totalIntervalSize++;
            curTail++;
        } else {
            // merge
            retIntervalPtr[curTail][1] = MAX(curRight, retIntervalPtr[curTail][1]);
        }
    }

    free(intervalArray);

    *returnSize = totalIntervalSize;
    *returnColumnSizes = (int*)calloc(totalIntervalSize, sizeof(int));
    for (int i = 0 ; i< totalIntervalSize; i++) {
        (*returnColumnSizes)[i] = intervalWidth;
    }

    return retIntervalPtr;
}

#endif