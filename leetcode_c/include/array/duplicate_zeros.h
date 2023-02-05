/**
 * @file duplicate_zeros.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/duplicate-zeros/
 * @version 0.1
 * @date 2023-01-31
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef LEETCODE_DUPLICATE_ZEROS_H
#define LEETCODE_DUPLICATE_ZEROS_H

#include "../const.h"

static void adjustArray(int* const tailPos, int remainSize) {
    int* tailPtr = tailPos;
    int* prePtr = tailPos - 1;

    for (int i = 0; i < remainSize; i++) {
        printf("tail: %d\n", *tailPos);
        printf("pre: %d\n", *prePtr);
        *tailPos = *prePtr;
        tailPtr--;
        prePtr--;
    }

    return ;
}

void duplicateZeros(int* arr, int arrSize){
    int remainSize = arrSize;
    int* const tailPtr = arr + arrSize - 1;

    for (int i = 0; i < arrSize; i++) {
        if (arr[i] == 0 && (i + 1) < arrSize) {
            // arr[i + 1] = 0;
            remainSize = arrSize - i - 2;
            // [1,0,2,3,0,4,5,0] --> [1,0,0,2,3,0,4,5]
            adjustArray(tailPtr, remainSize);
            arr[i + 1] = 0;
            printf("remain size: %d\n", remainSize);
            printf("debug\n");
            for (int j = 0; j < arrSize; j++) {
                printf("%d ", arr[j]);
            }
            printf("\n");
            i++;
        }
    }
    return ;
}

#endif