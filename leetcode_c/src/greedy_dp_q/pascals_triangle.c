/**
 * @file pascals_triangle.c
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/pascals-triangle/
 * @version 0.1
 * @date 2023-09-23
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../../include/greedy_dp_q.h"

int** generate_118(int numRows, int* returnSize, int** returnColumnSizes)
{
    int *retColSize = (int*)calloc(numRows, sizeof(int));
    for (int idx = 0; idx < numRows; idx++) {
        retColSize[idx] = idx + 1;
    }

    int **retArr = (int**)calloc(numRows, sizeof(int*));
    for (int idx = 0; idx < numRows; idx++) {
        retArr[idx] = (int*)calloc(retColSize[idx], sizeof(int));
        retArr[idx][0] = 1;
        retArr[idx][retColSize[idx] - 1] = 1;
    }
    *returnColumnSizes = retColSize;
    *returnSize = numRows;

    for (int idx = 2; idx < numRows; idx++) {
        for (int colIdx = 1; colIdx < retColSize[idx] - 1; colIdx++) {
            retArr[idx][colIdx] = retArr[idx - 1][colIdx] + retArr[idx - 1][colIdx - 1];
        }
    }

    return retArr;
}
