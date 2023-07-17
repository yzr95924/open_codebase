/**
 * @file long_palind_sub_str.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/longest-palindromic-substring/description/
 * @version 0.1
 * @date 2023-02-06
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef LEETCODE_LONG_PALIND_SUB_STR_H
#define LEETCODE_LONG_PALIND_SUB_STR_H

#include "../const.h"

static bool CheckPalindrom(char*s, int startIdx, int endIdx) {
    char* frontPtr = &s[startIdx];
    char* tailPtr = &s[endIdx];

    int len = endIdx - startIdx + 1;
    int step = len / 2;
    // printf("step: %d\n", step);

    for (int i = 0; i < step; i++) {
        // printf("%c, %c\n", *frontPtr, *tailPtr);
        if ((*frontPtr) != (*tailPtr)) {
            return false;
        }
        frontPtr++;
        tailPtr--;
    }

    return true;
}

static void CheckSpec(char* s, int strSize, char** retStr) {
    int retSize = 0;
    if (strSize == 1) {
        retSize = 1;
        strncpy(*retStr, s, retSize);
    }

    if (strSize == 2) {
        if (s[0] == s[1]) {
            retSize = 2;
        } else {
            retSize = 1;
        }
        strncpy(*retStr, s, retSize);
    }

    (*retStr)[retSize] = '\0';

    return;
}

char* longestPalindrome(char* s){
    int strSize = strlen(s);
    char* retStr = (char*)calloc(strSize + 1, sizeof(char));

    CheckSpec(s, strSize, &retStr);

    // record
    int curMaxPalindSize = 0;
    int maxPalindStartIdx = 0;
    int maxPalindEndIdx = 0;

    if (strSize > 2) {
        for (int startIdx = 0; startIdx < strSize - 1; startIdx++) {
            for (int endIdx = startIdx + 1; endIdx < strSize; endIdx++) {
                bool isPalind = CheckPalindrom(s, startIdx, endIdx);
                if (isPalind) {
                    // printf("find one, %d, %d.\n", startIdx, endIdx);
                    int curPalindSize = endIdx - startIdx + 1;
                    if (curPalindSize > curMaxPalindSize) {
                        curMaxPalindSize = curPalindSize;
                        maxPalindStartIdx = startIdx;
                        maxPalindEndIdx = endIdx;
                    }
                }
            }
        }

        if (curMaxPalindSize == 0) {
            curMaxPalindSize = 1;
            strncpy(retStr, &s[0], 1);
        } else {
            strncpy(retStr, &s[maxPalindStartIdx], curMaxPalindSize);
        }
        retStr[curMaxPalindSize] = '\0';

    }

    // printf("max start idx: %d\n", maxPalindStartIdx);
    // printf("max end idx: %d\n", maxPalindEndIdx);
    // printf("max size: %d\n", curMaxPalindSize);

    return retStr;
}

#endif