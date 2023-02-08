/**
 * @file greatest_common_divisor_str.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/greatest-common-divisor-of-strings/
 * @version 0.1
 * @date 2023-02-08
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef LEETCODE_GREATEST_COMMON_DIVISOR_STR_H
#define LEETCODE_GREATEST_COMMON_DIVISOR_STR_H

#include "../const.h"

static bool CheckSizeValid(int curSize, int str1Len, int str2Len) {
    if ((str1Len % curSize == 0) && (str2Len % curSize) == 0) {
        return true;
    } else {
        return false;
    }
}

static bool CheckDivisor(char* longStr, int longSize, char* subStr, int subStrSize) {
    int step = longSize / subStrSize;
    for (int i = 0; i < step; i++) {
        if (strncmp(longStr + (i * subStrSize), subStr, subStrSize) != 0) {
            return false;
        }
    }
    return true;
}

char* gcdOfStrings(char* str1, char* str2){
    int str1Len = strlen(str1);
    int str2Len = strlen(str2);

    char* shortStr = NULL;
    char* longStr = NULL;
    int shortStrSize = 0;
    int longStrSize = 0;
    if (str1Len > str2Len) {
        shortStr = str2;
        longStr = str1;
    } else {
        shortStr = str1;
        longStr = str2;
    }

    shortStrSize = strlen(shortStr);
    longStrSize = strlen(longStr);

    char* ret = (char*)calloc(shortStrSize + 1, sizeof(char));
    int maxSize = 0;
    for (int i = 0; i < shortStrSize; i++) {
        int curSize = i + 1;
        if (CheckSizeValid(curSize, str1Len, str2Len)) {
            if (CheckDivisor(longStr, longStrSize, shortStr, curSize) &&
                CheckDivisor(shortStr, shortStrSize, shortStr, curSize)) {
                maxSize = MAX(maxSize, curSize); 
            }
        } 
    }

    memcpy(ret, shortStr, maxSize);
    ret[maxSize] = '\0';
    return ret;
}

#endif