/**
 * @file merge_intervals.c
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/merge-intervals
 * @version 0.1
 * @date 2023-09-05
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../../include/find_sort_q.h"

typedef struct {
    int leftBound;
    int rightBound;
} IntervalItem;

int CompFunc(const void *rawInput1, const void *rawInput2)
{
    IntervalItem *input1 = (IntervalItem*)rawInput1;
    IntervalItem *input2 = (IntervalItem*)rawInput2;
    int ret = (*input1).leftBound - (*input2).leftBound; // ascend
    return ret;
}

int** merge(int** intervals, int intervalsSize, int* intervalsColSize,
    int* returnSize, int** returnColumnSizes)
{
    if (intervalsSize == 1) {
        *returnSize = 1;
        *returnColumnSizes = (int*)calloc(1, sizeof(int));
        (*returnColumnSizes)[0] = 2;
        int **retArr = (int**)calloc(1, sizeof(int*));
        retArr[0] = (int*)calloc(2, sizeof(int));
        retArr[0][0] = intervals[0][0];
        retArr[0][1] = intervals[0][1];
        return retArr;
    }

    IntervalItem *interValsArr = (IntervalItem*)calloc(intervalsSize, sizeof(IntervalItem));
    for (int idx = 0; idx < intervalsSize; idx++) {
        interValsArr[idx].leftBound = intervals[idx][0];
        interValsArr[idx].rightBound = intervals[idx][1];
    }
    qsort(interValsArr, intervalsSize, sizeof(IntervalItem), CompFunc);

    int **retArr = (int**)calloc(intervalsSize, sizeof(int*));
    for (int idx = 0; idx < intervalsSize; idx++) {
        retArr[idx] = (int*)calloc(2, sizeof(int));
    }
    int retCnt = 0;

    int curLeftBound = interValsArr[0].leftBound;
    int curRightBound = interValsArr[0].rightBound;
    for (int idx = 1; idx < intervalsSize; idx++) {
        if (curRightBound >= interValsArr[idx].leftBound) {
            if (curRightBound < interValsArr[idx].rightBound) {
                curRightBound = interValsArr[idx].rightBound;
            }
        } else {
            retArr[retCnt][0] = curLeftBound;
            retArr[retCnt][1] = curRightBound;
            retCnt++;

            curLeftBound = interValsArr[idx].leftBound;
            curRightBound = interValsArr[idx].rightBound;
        }
    }

    retArr[retCnt][0] = curLeftBound;
    retArr[retCnt][1] = curRightBound;
    retCnt++;

    free(interValsArr);
    *returnSize = retCnt;
    *returnColumnSizes = (int*)calloc(retCnt, sizeof(int));
    for (int idx = 0; idx < retCnt; idx++) {
        (*returnColumnSizes)[idx] = 2;
    }
    return retArr;
}
