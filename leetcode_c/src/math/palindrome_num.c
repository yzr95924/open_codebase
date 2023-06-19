/**
 * @file palindrome_num.c
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/palindrome-number/
 * @version 0.1
 * @date 2023-06-20
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../../include/math_q.h"
#include "../../../common_include/c_include.h"

#define MAX_ARR_SIZE 32

bool isPalindrome(int x){

    int digitArr[MAX_ARR_SIZE] = { 0 };
    int curDigitNum = 0;

    if (x < 0) {
        return false;
    }

    int digit;
    int remain = x;

    while (remain != 0) {
        digit = remain % 10;
        remain /= 10;

        digitArr[curDigitNum] = digit;
        curDigitNum++;
    }

    int startIdx = 0;
    int endIdx = curDigitNum - 1;

    while (startIdx != endIdx && startIdx <= endIdx) {
        if (digitArr[startIdx] != digitArr[endIdx]) {
            return false;
        }
        startIdx++;
        endIdx--;
    }

    return true;
}