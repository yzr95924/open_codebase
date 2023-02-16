/**
 * @file combine.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/combinations/
 * @version 0.1
 * @date 2023-02-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef LEETCODE_COMBINE_H
#define LEETCODE_COMBINE_H

#include "../const.h"

int** combine(int n, int k, int* returnSize, int** returnColumnSizes){
    int retSize = GetFactorial(n) / (GetFactorial(k) * GetFactorial(n - k));
    int** retAns = (int**)calloc(retSize, sizeof(int*));

    for (int i = 0; i < retSize; i++) {
        retAns[i] = (int*)calloc(k, sizeof(int));
    }

    return retAns;
}

#endif