/**
 * @file my_atoi.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/string-to-integer-atoi/
 * @version 0.1
 * @date 2023-02-24
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef LEETCODE_MY_ATOI_H
#define LEETCODE_MY_ATOI_H

#include "const.h"

int myAtoi(char * s){
    int inputSize = strlen(s);
    int retVal = 0;

    if (inputSize == 0) {
        return 0;
    }

    // jump the first space
    int realStartIdx = 0;
    for (int i = 0; i < inputSize; i++) {
        if (s[i] == ' ') {
            realStartIdx++;
        } else {
            break;
        }
    }

    bool isPositive = true;
    // check whether is a word
    if (s[realStartIdx] < '0' || s[realStartIdx] > '9') {
        // start not num
        switch (s[realStartIdx]) {
            case '-': {
                isPositive = false;
                realStartIdx++;
                break;
            }
            case '+': {
                realStartIdx++;
                break;
            }
            default: {
                return 0;
            }
        }
    }

    int realEndIdx = realStartIdx;
    for (int i = realStartIdx; i < inputSize; i++) {
        if (s[i] < '0' || s[i] > '9') {
            break;
        } else {
            realEndIdx++;
        }
    }

    // traverse the array backward
    uint64_t curVal = 0;
    uint64_t weight = 1;
    bool isOut = false;
    for (int i = realEndIdx; i >= realStartIdx; i--) {
        if (s[i] >= '0' && s[i] <= '9') {
            // it is a number
            curVal += (uint64_t)(s[i] - '0') * weight;

            if (isPositive) {
                if (curVal > (((uint64_t)(1) << 31) - 1) ||
                    (weight > INT32_MAX && s[realStartIdx] != '0')) {
                    printf("here: weight: %lu\n", weight);
                    isOut = true;
                    break;
                }
            } else {
                if (curVal > (((uint64_t)(1) << 31)) ||
                    (weight > INT32_MAX && s[realStartIdx] != '0')) {
                    isOut = true;
                    break;
                }
            }

            weight *= (uint64_t)10;
        } else {
            // it is not a number
            continue;
        }
    }

    if (isPositive) {
        // it is positive
        if (isOut) {
            retVal = INT32_MAX;
        } else {
            retVal = (int32_t)curVal;
        }
    } else {
        // it is negative
        if (isOut) {
            retVal = INT32_MIN;
        } else {
            retVal = (int32_t)(-curVal);
        }
    }

    return retVal;
}

#endif