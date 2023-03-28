/**
 * @file make_sum_divisible_by_p.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/make-sum-divisible-by-p/
 * @version 0.1
 * @date 2023-03-10
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef LEETCODE_MAKE_SUM_DIVISIBLE_BY_Q_H
#define LEETCODE_MAKE_SUM_DIVISIBLE_BY_Q_H

#include "../const.h"
#include "../third/uthash.h"

typedef struct {
    int remainder; // remainder
    int latestIdx; // last idx
    UT_hash_handle hh;
} HashTableItem_t;

void InsertHashTable(HashTableItem_t** hashTable, int key, int val) {
    HashTableItem_t* tmpItem = NULL;
    HASH_FIND_INT(*hashTable, &key, tmpItem);
    if (tmpItem == NULL) {
        // not exist
        tmpItem = (HashTableItem_t*)malloc(sizeof(HashTableItem_t));
        tmpItem->remainder = key;
        tmpItem->latestIdx = val;
        HASH_ADD_INT(*hashTable, remainder, tmpItem);
    } else {
        tmpItem->latestIdx = val;
    }
    return ;
}

bool FindHashTable(HashTableItem_t* hashTable, int key) {
    HashTableItem_t* tmpItem = NULL;
    HASH_FIND_INT(hashTable, &key, tmpItem);
    if (tmpItem == NULL) {
        // not exist
        return false;
    } else {
        return true;
    }
}

void GetHashTable(HashTableItem_t* hashTable, int key, int* val) {
    HashTableItem_t* tmpItem = NULL;
    HASH_FIND_INT(hashTable, &key, tmpItem);
    if (tmpItem == NULL) {
        // not exist
        printf("the query item not exists.\n");
        return ;
    } else {
        memcpy(val, &tmpItem->latestIdx, sizeof(*val));
    }

    return ;
}

void FreeHashHashTable(HashTableItem_t* hashTable) {
    HashTableItem_t* tmpItem;
    HashTableItem_t* tmp;
    HASH_ITER(hh, hashTable, tmpItem, tmp) {
        HASH_DEL(hashTable, tmpItem);
        free(tmpItem);
    }
    return ;
}

int minSubarray(int* nums, int numsSize, int p){
    HashTableItem_t* globalHashTable = NULL;

    int x = 0;
    for (int i = 0; i < numsSize; i++) {
        x = (x + nums[i]) % p;
    }

    if (x == 0) {
        return 0;
    }

    HashTableItem_t* index = NULL;
    int y = 0, res = numsSize;
    int curRemainder = 0;
    for (int i = 0; i < numsSize; i++) {
        InsertHashTable(&index, y, i); // f[i] mod p = y，因此哈希表记录 y 对应的下标为 i
        y = (y + nums[i]) % p;
        curRemainder = (y - x + p) % p;
        if (FindHashTable(index, curRemainder)) {
            int val = 0;
            GetHashTable(index, curRemainder, &val);
            res = MIN(res, i - val + 1);
        }
    }

    FreeHashHashTable(globalHashTable);

    return res == numsSize ? -1 : res;
}

#endif