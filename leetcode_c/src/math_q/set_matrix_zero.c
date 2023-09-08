/**
 * @file set_matrix_zero.c
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/set-matrix-zeroes/
 * @version 0.1
 * @date 2023-09-09
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../../include/math_q.h"

void setZeroes(int** matrix, int matrixSize, int* matrixColSize)
{
    bool *rowFlagArr = (bool*)calloc(matrixSize, sizeof(bool));
    bool *colFlagArr = (bool*)calloc(matrixColSize[0], sizeof(bool));

    for (int rowIdx = 0; rowIdx < matrixSize; rowIdx++) {
        for (int colIdx = 0; colIdx < matrixColSize[0]; colIdx++) {
            if (matrix[rowIdx][colIdx] == 0) {
                rowFlagArr[rowIdx] = true;
                colFlagArr[colIdx] = true;
            }
        }
    }

    for (int rowIdx = 0; rowIdx < matrixSize; rowIdx++) {
        for (int colIdx = 0; colIdx < matrixColSize[0]; colIdx++) {
            if (rowFlagArr[rowIdx] || colFlagArr[colIdx]) {
                matrix[rowIdx][colIdx] = 0;
            }
        }
    }
    return;
}
