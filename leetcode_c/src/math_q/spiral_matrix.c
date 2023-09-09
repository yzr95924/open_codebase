/**
 * @file spiral_matrix.c
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/spiral-matrix/
 * @version 0.1
 * @date 2023-09-10
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../../include/math_q.h"

int* spiralOrder(int** matrix, int matrixSize,
    int* matrixColSize, int* returnSize)
{
    int directStat[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    int totalCnt = 0;
    for (int idx = 0; idx < matrixSize; idx++) {
        totalCnt += matrixColSize[idx];
    }
    int *retArr = (int*)calloc(totalCnt, sizeof(int));

    bool **visitMap = (int**)calloc(matrixSize, sizeof(bool*));
    for (int idx = 0; idx < matrixSize; idx++) {
        visitMap[idx] = (bool*)calloc(matrixColSize[idx], sizeof(bool));
    }

    int curDirect = 0;
    int curRow = 0;
    int curCol = 0;
    for (int idx = 0; idx < totalCnt; idx++) {
        retArr[idx] = matrix[curRow][curCol];
        visitMap[curRow][curCol] = true;
        int nextRow = curRow + directStat[curDirect][0];
        int nextCol = curCol + directStat[curDirect][1];
        if (nextRow < 0 || nextRow > matrixSize - 1 ||
            nextCol < 0 || nextCol > matrixColSize[0] - 1 ||
            visitMap[nextRow][nextCol]) {
            curDirect = (curDirect + 1) % 4;
        }
        curRow += directStat[curDirect][0];
        curCol += directStat[curDirect][1];
    }

    for (int idx = 0; idx < matrixSize; idx++) {
        free(visitMap[idx]);
    }
    free(visitMap);
    *returnSize = totalCnt;
    return retArr;
}
