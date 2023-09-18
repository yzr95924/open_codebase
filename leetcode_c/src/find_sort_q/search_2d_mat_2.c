/**
 * @file search_2d_mat_2.c
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/search-a-2d-matrix-ii/
 * @version 0.1
 * @date 2023-09-18
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../../include/find_sort_q.h"

static bool BinarySearch(int *rowArr, int arrLen, int target)
{
    int leftIdx = 0;
    int rightIdx = arrLen - 1;
    int midIdx = 0;
    bool isFind = false;

    while (leftIdx <= rightIdx) {
        midIdx = leftIdx + ((rightIdx - leftIdx) / 2);
        if (target < rowArr[midIdx]) {
            rightIdx = midIdx - 1;
        } else if (target > rowArr[midIdx]) {
            leftIdx = midIdx + 1;
        } else {
            isFind = true;
            break;
        }
    }

    return isFind;
}

bool searchMatrix_240(int** matrix, int matrixSize, int* matrixColSize, int target)
{
    for (int rowIdx = 0; rowIdx < matrixSize; rowIdx++) {
        if (BinarySearch(matrix[rowIdx], matrixColSize[rowIdx], target)) {
            return true;
        }
    }
    return false;
}
