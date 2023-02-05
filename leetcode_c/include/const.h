/**
 * @file const.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/two-sum/
 * @version 0.1
 * @date 2023-01-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef LEETCODE_C_CONST_H
#define LEETCODE_C_CONST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define MIN(a,b) (((a) <= (b)) ? (a) : (b))
#define MAX(a,b) (((a) >= (b)) ? (a) : (b))

int** ConvertTwoDemArrayToPtr(int* startPos, size_t row, size_t col) {
    int** ret = NULL;
    ret = (int**)malloc(sizeof(int*) * row);
    for (int i = 0; i < row; i++) {
        ret[i] = (int*)malloc(sizeof(int) * col);
    }

    return ret;
}

void FreeTwoDemArray(int** inputArray, size_t row) {
    for (int i = 0; i < row; i++) {
        free(inputArray[i]);
    }
    return ;
}

#endif