/**
 * @file long_sub_str_wo_repeat.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/longest-substring-without-repeating-characters/
 * @version 0.1
 * @date 2023-02-08
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef LEETCODE_LONG_SUB_STR_WO_REPEAT_H
#define LEETCODE_LONG_SUB_STR_WO_REPEAT_H

#include "../const.h"

static const int g_alphabetNum = 128; 

static void AddMap(uint8_t* subMap, char input_c) {
    subMap[input_c]++;
}

static bool CheckUnique(uint8_t* subMap) {
    for (int i = 0; i < g_alphabetNum; i++) {
        if (subMap[i] > 1) {
            return false;
        }
    }
    return true;
}

static void RemoveMap(uint8_t* subMap, char input_c) {
    subMap[input_c]--;
    return ;
}

int lengthOfLongestSubstring(char * s){
    int sSize = strlen(s);
    if (sSize == 0) {
        return 0;
    }

    uint8_t* subMap = (uint8_t*)calloc(g_alphabetNum, sizeof(uint8_t));

    int frontIdx = 0;
    int rearIdx = 0;
    int ret = 1;
    AddMap(subMap, s[frontIdx]);
    while (frontIdx < sSize) {
        if (CheckUnique(subMap)) {
            // add
            ret = MAX(frontIdx - rearIdx + 1, ret);
            frontIdx++;
            if (frontIdx == sSize) {
                break;
            } 
            AddMap(subMap, s[frontIdx]);
        } else {
            // remove
            RemoveMap(subMap, s[rearIdx]);
            rearIdx++;
        }
    }

    free(subMap);

    return ret;
}

#endif