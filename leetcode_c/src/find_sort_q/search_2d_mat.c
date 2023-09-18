/**
 * @file search_2d_mat.c
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/search-a-2d-matrix
 * @version 0.1
 * @date 2023-08-04
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../../include/find_sort_q.h"

bool searchMatrix_74(int** matrix, int matrixSize, int* matrixColSize, int target)
{
    int topIdx = 0;
    int downIdx = matrixSize - 1;
    int midIdx = 0;
    int curRowIdx = 0;
    bool isFind = false;

    while (topIdx <= downIdx) {
        midIdx = topIdx + ((downIdx - topIdx) / 2);
        if (target < matrix[midIdx][0]) {
            downIdx = midIdx - 1;
        } else if (target > matrix[midIdx][0]) {
            topIdx = midIdx + 1;
        } else {
            isFind = true;
            break;
        }
    }

    if (isFind == true) {
        return true;
    }

    if (topIdx - 1 >= 0) {
        curRowIdx = topIdx - 1;
    } else {
        return false;
    }

    topIdx = 0;
    downIdx = matrixColSize[curRowIdx] - 1;
    while (topIdx <= downIdx) {
        midIdx = topIdx + ((downIdx - topIdx) / 2);
        if (target < matrix[curRowIdx][midIdx]) {
            downIdx = midIdx - 1;
        } else if (target > matrix[curRowIdx][midIdx]) {
            topIdx = midIdx + 1;
        } else {
            isFind = true;
            break;
        }
    }

    if (isFind) {
        return true;
    } else {
        return false;
    }
}
