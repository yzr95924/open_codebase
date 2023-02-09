/**
 * @file compare_version.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/compare-version-numbers/
 * @version 0.1
 * @date 2023-02-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef LEETCODE_COMPARE_VERSION_H
#define LEETCODE_COMPARE_VERSION_H

#include "../const.h"

int compareVersion(char * version1, char * version2){
    int version1Size = strlen(version1);
    int version2Size = strlen(version2);

    int version1Val[500] = {0};
    int version1ValSize = 0;

    int version2Val[500] = {0};
    int version2ValSize = 0;

    const char delim[2] = ".";
    char* subStr = NULL;

    // printf("version1: \n");
    subStr = strtok(version1, delim); 
    while (subStr != NULL) {
        version1Val[version1ValSize] = atoi(subStr);
        // printf("%d\n", version1Val[version1ValSize]);
        version1ValSize++;
        subStr = strtok(NULL, delim);
    }

    // printf("version2: \n");
    subStr = strtok(version2, delim);
    while (subStr != NULL) {
        version2Val[version2ValSize] = atoi(subStr);
        // printf("%d\n", version2Val[version2ValSize]);
        version2ValSize++;
        subStr = strtok(NULL, delim);
    }

    int maxSize = MAX(version1ValSize, version2ValSize);

    for (int i = 0; i < maxSize; i++) {
        int diff = version1Val[i] - version2Val[i];
        if (diff == 0) {
            continue;
        } else if (diff > 0) {
            return 1;
        } else {
            return -1;
        }
    }
    return 0;
}

#endif