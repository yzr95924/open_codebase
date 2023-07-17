/**
 * @file my_hash_type.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief my hash_type
 * @version 0.1
 * @date 2023-03-12
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef LEETCODE_MY_HASH_TYPE_H
#define LEETCODE_MY_HASH_TYPE_H

#include "const.h"
#include "third/uthash.h"

typedef struct {
    int hashKey;
    int hashVal;
    UT_hash_handle hh;
} HashTblItem_T;

void InsertHashTable(HashTblItem_T** hashTable, int key, int val)
{
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

bool GetHashTable(const HashTblItem_T* hashTable, int key, int* val)
{
    HashTblItem_T* curItem = NULL;
    HASH_FIND_INT(hashTable, &key, curItem);
    if (curItem == NULL) {
        // not exist
        return false;
    }

    memcpy(val, &curItem->hashVal, sizeof(*val));
    return true;
};

void FreeHashTable(HashTblItem_T* hashTable)
{
    HashTblItem_T* curItem;
    HashTblItem_T* tmp;
    HASH_ITER(hh, hashTable, curItem, tmp) {
        HASH_DEL(hashTable, curItem);
        free(curItem);
    }

    return;
}

#endif
