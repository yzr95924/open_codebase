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

    if (s[0] <= '0' || s[0] >= '9') {
        // start not num
        if (s[0] != " " && s[0] != '-' && s[0] != '+') {
            return 0;
        }
    }

    int64_t curVal = 0;
    int weight = 1;
    int leftIdx = inputSize - 1;
    bool isOut = false;
    for (int i = inputSize - 1; i >= 0; i--) {
        if (s[i] >= '0' && s[i] <= '9') {
            // it is a number
            curVal += (int)(s[i] - '0') * weight;
            weight *= 10;
            leftIdx = i;

            if (curVal > ((uint64_t)(1) << 31)) {
                isOut = true;
                break;
            }
        } else {
            // it is not a number
            continue;
        }
    }

    if (leftIdx - 1 >= 0) {
        // check symbol
        if (s[leftIdx - 1] == '-') {
            // it is negative
            if (isOut) {
                retVal = INT32_MIN;
            } else {
                retVal = -1 * curVal;
            }
        } else {
            // it is positive
            if (isOut) {
                retVal = INT32_MAX;
            } else {
                retVal = (int32_t)curVal;
            }
        }
    } else {
        // it is positive
        if (isOut) {
            retVal = INT32_MAX;
        } else {
            retVal = (int32_t)curVal;
        }
    }

    return retVal;
}

#endif