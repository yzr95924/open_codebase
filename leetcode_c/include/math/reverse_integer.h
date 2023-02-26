/**
 * @file reverse_integer.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/reverse-integer/
 * @version 0.1
 * @date 2023-02-26
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef LEETCODE_REVERSE_INTEGER_H
#define LEETCODE_REVERSE_INTEGER_H

#include "../../include/const.h"

int reverse(int x){
    int retVal = 0;

    int curDigit;
    while (x != 0) {
        // avoid using uint64_t
        if (retVal < (INT32_MIN / 10) || retVal > (INT32_MAX / 10)) {
            return 0;
        }

        curDigit = x % 10;
        x /= 10;
        retVal = retVal * 10 + curDigit;
    }

    return retVal;
}

#endif