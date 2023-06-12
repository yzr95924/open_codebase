/**
 * @file c_my_hash.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief my hash table
 * @version 0.1
 * @date 2023-06-13
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef MY_HASH_TYPE_H
#define MY_HASH_TYPE_H

#include "define_const.h"
#include "c_include.h"
#include "third_party/uthash.h"

#define MAX_HASH_KEY_SIZE 64

typedef int ZUORU_HASH_DATA_T;

typedef struct {
    int hashKey;
    ZUORU_HASH_DATA_T hashVal;
    UT_hash_handle hh;
} ZUORU_HASH_TBL_INT_ITEM_H;

typedef struct {
    void *hashKey;
    ZUORU_HASH_DATA_T hashVal;
    UT_hash_handle hh;
} ZUORU_HASH_TBL_PTR_ITEM_H;

typedef struct {
    char hashKey[MAX_HASH_KEY_SIZE];
    ZUORU_HASH_DATA_T hashVal;
    UT_hash_handle hh;
} ZUORU_HASH_TBL_STR_ITEM_H;

/**
 *********************************************
 ***               for int key
 *********************************************
 */

ZUORU_HASH_TBL_INT_ITEM_H** Zuoru_InitIntHashTbl()
{
    ZUORU_HASH_TBL_INT_ITEM_H **hashTblPtr = (ZUORU_HASH_TBL_INT_ITEM_H**)calloc(1,
        sizeof(ZUORU_HASH_TBL_INT_ITEM_H*));
    *hashTblPtr = NULL;
    return hashTblPtr;
}

void Zuoru_InsertIntHashTbl(ZUORU_HASH_TBL_INT_ITEM_H **hashTblPtr, int key, ZUORU_HASH_DATA_T *inVal)
{
    ZUORU_HASH_TBL_INT_ITEM_H *tmpHashItem;

    HASH_FIND_INT(*hashTblPtr, &key, tmpHashItem);
    if (tmpHashItem == NULL) {
        tmpHashItem = (ZUORU_HASH_TBL_INT_ITEM_H*)calloc(1, sizeof(ZUORU_HASH_TBL_INT_ITEM_H));
        tmpHashItem->hashKey = key;
        HASH_ADD_INT(*hashTblPtr, hashKey, tmpHashItem);
    }
    memcpy(&tmpHashItem->hashVal, inVal, sizeof(ZUORU_HASH_DATA_T));
    return;
}

bool Zuoru_FindIntHashTbl(ZUORU_HASH_TBL_INT_ITEM_H **hashTblPtr, int key,
    ZUORU_HASH_TBL_INT_ITEM_H **ret)
{
    ZUORU_HASH_TBL_INT_ITEM_H *tmpHashItem = NULL;
    HASH_FIND_INT(*hashTblPtr, &key, tmpHashItem);
    if (tmpHashItem == NULL) {
        *ret = NULL;
        return false;
    }

    *ret = tmpHashItem;
    return true;
}

void Zuoru_DelIntHashTbl(ZUORU_HASH_TBL_INT_ITEM_H **hashTblPtr,
    ZUORU_HASH_TBL_INT_ITEM_H *hashItem)
{
    HASH_DEL(*hashTblPtr, hashItem);
    free(hashItem);
    return;
}

void Zuoru_FreeIntHashTbl(ZUORU_HASH_TBL_INT_ITEM_H **hashTblPtr)
{
    ZUORU_HASH_TBL_INT_ITEM_H *curItem;
    ZUORU_HASH_TBL_INT_ITEM_H *tmpItem;

    HASH_ITER(hh, *hashTblPtr, curItem, tmpItem) {
        HASH_DEL(*hashTblPtr, curItem);
        free(curItem);
    }
    free(hashTblPtr);
    return;
}

#endif
