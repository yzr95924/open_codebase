/**
 * @file longest_consecutive_seq.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/longest-consecutive-sequence/description/?favorite=2cktkvj
 * @version 0.1
 * @date 2023-03-23
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef LEETCODE_LONGEST_CONSECUTIVE_SEQ_H
#define LEETCODE_LONGEST_CONSECUTIVE_SEQ_H

#include "../const.h"
#include "../../include/third/uthash.h"

typedef struct {
    int hashKey;
    int hashVal;
    UT_hash_handle hh;
} HashTblItem_T;

void InsertHashTable(HashTblItem_T** hashTable, int key, int val) {
    HashTblItem_T* curItem = NULL;
    HASH_FIND_INT(*hashTable, &key, curItem);

    if (curItem == NULL) {
        // not exist
        curItem = (HashTblItem_T*)malloc(sizeof(HashTblItem_T));
        curItem->hashKey = key;
        curItem->hashVal = val;
        HASH_ADD_INT(*hashTable, hashKey, curItem);
    } else {
        curItem->hashVal = val;
    }
    return;
}

bool GetHashTable(const HashTblItem_T* hashTable, int key, int* val) {
    HashTblItem_T* curItem = NULL;
    HASH_FIND_INT(hashTable, &key, curItem);
    if (curItem == NULL) {
        // not exist
        return false;
    }

    memcpy(val, &curItem->hashVal, sizeof(*val));
    return true;
};

void FreeHashTable(HashTblItem_T* hashTable) {
    HashTblItem_T* curItem;
    HashTblItem_T* tmp;
    HASH_ITER(hh, hashTable, curItem, tmp) {
        HASH_DEL(hashTable, curItem);
        free(curItem);
    }

    return;
}

int longestConsecutive(int* nums, int numsSize)
{
    HashTblItem_T* globalHashTbl = NULL;

    for (int i = 0; i < numsSize; i++) {
        InsertHashTable(&globalHashTbl, nums[i], 0);
    }

    int ret = 0;
    bool isExist = false;
    for (int i = 0; i < numsSize; i++) {
        int getVal;
        isExist = GetHashTable(globalHashTbl, (nums[i] - 1), &getVal);
        if (isExist) {
            continue;
        } else {
            int curSearchVal = nums[i] + 1;
            int curLength = 1;
            while (GetHashTable(globalHashTbl, curSearchVal, &getVal)) {
                curLength++;
                curSearchVal++;
            }
            ret = MAX(ret, curLength);
        }
    }

    return ret;
}

#endif