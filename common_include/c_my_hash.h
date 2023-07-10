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

typedef int Zuoru_Hash_Data;

typedef struct {
    int hashKey;
    Zuoru_Hash_Data hashVal;
    UT_hash_handle hh;
} Zuoru_HashTbl_Item;

typedef struct {
    void *hashKey;
    Zuoru_Hash_Data hashVal;
    UT_hash_handle hh;
} ZUORU_HASH_TBL_PTR_ITEM_H;

typedef struct {
    char hashKey[MAX_HASH_KEY_SIZE];
    Zuoru_Hash_Data hashVal;
    UT_hash_handle hh;
} ZUORU_HASH_TBL_STR_ITEM_H;

/**
 *********************************************
 ***               for int key hash table
 *********************************************
 */

Zuoru_HashTbl_Item** ZuoruInitIntHashTbl()
{
    Zuoru_HashTbl_Item **hashTblPtr = (Zuoru_HashTbl_Item**)calloc(1,
        sizeof(Zuoru_HashTbl_Item*));
    *hashTblPtr = NULL;
    return hashTblPtr;
}

Zuoru_HashTbl_Item* ZuoruInsertIntHashTbl(Zuoru_HashTbl_Item **hashTblPtr,
    int key, Zuoru_Hash_Data *inVal)
{
    Zuoru_HashTbl_Item *tmpHashItem;

    HASH_FIND_INT(*hashTblPtr, &key, tmpHashItem);
    if (tmpHashItem == NULL) {
        tmpHashItem = (Zuoru_HashTbl_Item*)calloc(1, sizeof(Zuoru_HashTbl_Item));
        tmpHashItem->hashKey = key;
        HASH_ADD_INT(*hashTblPtr, hashKey, tmpHashItem);
    }
    memcpy(&tmpHashItem->hashVal, inVal, sizeof(Zuoru_Hash_Data));
    return tmpHashItem;
}

bool ZuoruFindIntHashTbl(Zuoru_HashTbl_Item **hashTblPtr, int key,
    Zuoru_HashTbl_Item **ret)
{
    Zuoru_HashTbl_Item *tmpHashItem = NULL;
    HASH_FIND_INT(*hashTblPtr, &key, tmpHashItem);
    if (tmpHashItem == NULL) {
        *ret = NULL;
        return false;
    }

    *ret = tmpHashItem;
    return true;
}

void ZuoruDelIntHashTbl(Zuoru_HashTbl_Item **hashTblPtr,
    Zuoru_HashTbl_Item *hashItem)
{
    HASH_DEL(*hashTblPtr, hashItem);
    free(hashItem);
    return;
}

void ZuoruFreeIntHashTbl(Zuoru_HashTbl_Item **hashTblPtr)
{
    Zuoru_HashTbl_Item *curItem;
    Zuoru_HashTbl_Item *tmpItem;

    HASH_ITER(hh, *hashTblPtr, curItem, tmpItem) {
        HASH_DEL(*hashTblPtr, curItem);
        free(curItem);
    }
    free(hashTblPtr);
    return;
}

/**
 *********************************************
 ***               for ptr key hash table
 *********************************************
 */

ZUORU_HASH_TBL_PTR_ITEM_H** Zuoru_InitPtrHashTbl()
{
    ZUORU_HASH_TBL_PTR_ITEM_H **hashTblPtr = (ZUORU_HASH_TBL_PTR_ITEM_H**)calloc(1,
        sizeof(ZUORU_HASH_TBL_PTR_ITEM_H*));
    *hashTblPtr = NULL;
    return hashTblPtr;
}

void Zuoru_InsertPtrHashTbl(ZUORU_HASH_TBL_PTR_ITEM_H **hashTblPtr, void *key,
    Zuoru_Hash_Data *inVal)
{
    ZUORU_HASH_TBL_PTR_ITEM_H *tmpHashItem = NULL;
    HASH_FIND_PTR(*hashTblPtr, &key, tmpHashItem);
    if (tmpHashItem == NULL) {
        tmpHashItem = (ZUORU_HASH_TBL_PTR_ITEM_H*)calloc(1, sizeof(ZUORU_HASH_TBL_PTR_ITEM_H));
        tmpHashItem->hashKey = key;
        HASH_ADD_PTR(*hashTblPtr, hashKey, tmpHashItem);
    }
    memcpy(&tmpHashItem->hashVal, inVal, sizeof(Zuoru_Hash_Data));
    return;
}

bool Zuoru_FindPtrHashTbl(ZUORU_HASH_TBL_PTR_ITEM_H **hashTblPtr, void *key,
    ZUORU_HASH_TBL_PTR_ITEM_H **ret)
{
    ZUORU_HASH_TBL_PTR_ITEM_H *tmpHashItem = NULL;
    HASH_FIND_PTR(*hashTblPtr, &key, tmpHashItem);
    if (tmpHashItem == NULL) {
        *ret = NULL;
        return false;
    }

    *ret = tmpHashItem;
    return true;
}

void Zuoru_DelPtrHashTbl(ZUORU_HASH_TBL_PTR_ITEM_H **hashTblPtr,
    ZUORU_HASH_TBL_PTR_ITEM_H *hashItem)
{
    HASH_DEL(*hashTblPtr, hashItem);
    free(hashItem);
    return;
}

void Zuoru_FreePtrHashTbl(ZUORU_HASH_TBL_PTR_ITEM_H **hashTblPtr)
{
    ZUORU_HASH_TBL_PTR_ITEM_H *curItem;
    ZUORU_HASH_TBL_PTR_ITEM_H *tmpItem;

    HASH_ITER(hh, *hashTblPtr, curItem, tmpItem) {
        HASH_DEL(*hashTblPtr, curItem);
        free(curItem);
    }
    free(hashTblPtr);
    return;
}

/**
 *********************************************
 ***               for str key hash table
 *********************************************
 */

ZUORU_HASH_TBL_STR_ITEM_H** Zuoru_InitStrHashTbl()
{
    ZUORU_HASH_TBL_STR_ITEM_H **hashTblPtr = (ZUORU_HASH_TBL_STR_ITEM_H**)calloc(1,
        sizeof(ZUORU_HASH_TBL_STR_ITEM_H*));
    *hashTblPtr = NULL;
    return hashTblPtr;
}

void Zuoru_InsertStrHashTbl(ZUORU_HASH_TBL_STR_ITEM_H **hashTblPtr, const char *key,
    Zuoru_Hash_Data *inVal)
{
    ZUORU_HASH_TBL_STR_ITEM_H *tmpHashItem = NULL;
    HASH_FIND_STR(*hashTblPtr, key, tmpHashItem);
    if (tmpHashItem == NULL) {
        tmpHashItem = (ZUORU_HASH_TBL_STR_ITEM_H*)calloc(1, sizeof(ZUORU_HASH_TBL_STR_ITEM_H));
        strcpy(tmpHashItem->hashKey, key);
        HASH_ADD_STR(*hashTblPtr, hashKey, tmpHashItem);
    }
    memcpy(&tmpHashItem->hashVal, inVal, sizeof(Zuoru_Hash_Data));
    return;
}

bool Zuoru_FindStrHashTbl(ZUORU_HASH_TBL_STR_ITEM_H **hashTblPtr, const char *key,
    ZUORU_HASH_TBL_STR_ITEM_H **ret)
{
    ZUORU_HASH_TBL_STR_ITEM_H *tmpHashItem = NULL;
    HASH_FIND_STR(*hashTblPtr, key, tmpHashItem);
    if (tmpHashItem == NULL) {
        *ret = NULL;
        return false;
    }

    *ret = tmpHashItem;
    return true;
}

void Zuoru_DelStrHashTbl(ZUORU_HASH_TBL_STR_ITEM_H **hashTblPtr,
    ZUORU_HASH_TBL_STR_ITEM_H *hashItem)
{
    HASH_DEL(*hashTblPtr, hashItem);
    free(hashItem);
    return;
}

void Zuoru_FreeStrHashTbl(ZUORU_HASH_TBL_STR_ITEM_H **hashTblPtr)
{
    ZUORU_HASH_TBL_STR_ITEM_H *curItem;
    ZUORU_HASH_TBL_STR_ITEM_H *tmpItem;

    HASH_ITER(hh, *hashTblPtr, curItem, tmpItem) {
        HASH_DEL(*hashTblPtr, curItem);
        free(curItem);
    }
    free(hashTblPtr);
    return;
}

#endif
