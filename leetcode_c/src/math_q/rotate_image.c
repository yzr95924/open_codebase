/**
 * @file rotate_image.c
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/rotate-image
 * @version 0.1
 * @date 2023-09-10
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../../include/math_q.h"

void rotate(int** matrix, int matrixSize, int* matrixColSize)
{
    int **tmpMatrix = (int**)calloc(matrixSize, sizeof(int*));
    for (int idx = 0; idx < matrixSize; idx++) {
        tmpMatrix[idx] = (int*)calloc(matrixSize, sizeof(int));
        memcpy(tmpMatrix[idx], matrix[idx], sizeof(int) * matrixSize);
    }

    for (int row = 0; row < matrixSize; row++) {
        for (int col = 0; col < matrixSize; col++) {
            matrix[col][matrixSize - row - 1] = tmpMatrix[row][col];
        }
    }
    return;
}
