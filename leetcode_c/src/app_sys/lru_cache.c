/**
 * @file lru_cache.c
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/lru-cache/
 * @version 0.1
 * @date 2023-06-15
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../../include/app_sys.h"
#include "../../../common_include/third_party/uthash.h"

typedef struct {
    int val;
    void *lListNodePtr;
} ZUORU_HASH_DATA_T;

typedef struct {
    int hashKey;
    ZUORU_HASH_DATA_T hashVal;
    UT_hash_handle hh;
} ZUORU_HASH_TBL_INT_ITEM_H;

typedef ZUORU_HASH_TBL_INT_ITEM_H* ZUORU_DATA_T;

ZUORU_HASH_TBL_INT_ITEM_H** Zuoru_InitIntHashTbl()
{
    ZUORU_HASH_TBL_INT_ITEM_H **hashTblPtr = (ZUORU_HASH_TBL_INT_ITEM_H**)calloc(1,
        sizeof(ZUORU_HASH_TBL_INT_ITEM_H*));
    *hashTblPtr = NULL;
    return hashTblPtr;
}

ZUORU_HASH_TBL_INT_ITEM_H* Zuoru_InsertIntHashTbl(ZUORU_HASH_TBL_INT_ITEM_H **hashTblPtr,
    int key, ZUORU_HASH_DATA_T *inVal)
{
    ZUORU_HASH_TBL_INT_ITEM_H *tmpHashItem;

    HASH_FIND_INT(*hashTblPtr, &key, tmpHashItem);
    if (tmpHashItem == NULL) {
        tmpHashItem = (ZUORU_HASH_TBL_INT_ITEM_H*)calloc(1, sizeof(ZUORU_HASH_TBL_INT_ITEM_H));
        tmpHashItem->hashKey = key;
        HASH_ADD_INT(*hashTblPtr, hashKey, tmpHashItem);
    }
    memcpy(&tmpHashItem->hashVal, inVal, sizeof(ZUORU_HASH_DATA_T));
    return tmpHashItem;
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

struct ZUORU_DL_LIST_NODE_T {
    ZUORU_DATA_T data;
    struct ZUORU_DL_LIST_NODE_T *next;
    struct ZUORU_DL_LIST_NODE_T *prev;
};

typedef struct ZUORU_DL_LIST_NODE_T ZUORU_DL_LIST_NODE_T;

typedef struct {
    ZUORU_DL_LIST_NODE_T *head;
    ZUORU_DL_LIST_NODE_T *tail;
    int curSize;
} ZUORU_DL_LIST_T;

ZUORU_DL_LIST_T* Zuoru_InitDLList()
{
    ZUORU_DL_LIST_T *dlListPtr = (ZUORU_DL_LIST_T*)calloc(1, sizeof(ZUORU_DL_LIST_T));
    dlListPtr->head = NULL;
    dlListPtr->tail = NULL;
    dlListPtr->curSize = 0;
    return dlListPtr;
}

void Zuoru_FreeDLList(ZUORU_DL_LIST_T *dlListPtr)
{
    ZUORU_DL_LIST_NODE_T *curNode = dlListPtr->head;
    ZUORU_DL_LIST_NODE_T *delNode = NULL;

    while (curNode != NULL) {
        delNode = curNode;
        curNode = curNode->next;
        free(delNode);
    }

    free(dlListPtr);
    return;
}

ZUORU_DL_LIST_NODE_T* Zuoru_InsertHeadDLList(ZUORU_DL_LIST_T *dlListPtr, ZUORU_DATA_T *inVal)
{
    ZUORU_DL_LIST_NODE_T *newNode = (ZUORU_DL_LIST_NODE_T*)calloc(1, sizeof(ZUORU_DL_LIST_NODE_T));
    memcpy(&newNode->data, inVal, sizeof(ZUORU_DATA_T));
    newNode->next = NULL;
    newNode->prev = NULL;

    if (dlListPtr->curSize == 0) {
        dlListPtr->tail = newNode;
    } else {
        dlListPtr->head->prev = newNode;
        newNode->next = dlListPtr->head;
    }

    dlListPtr->head = newNode;
    dlListPtr->curSize++;

    return newNode;
}

ZUORU_DL_LIST_NODE_T* Zuoru_InsertTailDLList(ZUORU_DL_LIST_T *dlListPtr, ZUORU_DATA_T *inVal)
{
    ZUORU_DL_LIST_NODE_T *newNode = (ZUORU_DL_LIST_NODE_T*)calloc(1, sizeof(ZUORU_DL_LIST_NODE_T));
    memcpy(&newNode->data, inVal, sizeof(ZUORU_DATA_T));
    newNode->next = NULL;
    newNode->prev = NULL;

    if (dlListPtr->curSize == 0) {
        dlListPtr->head = newNode;
    } else {
        dlListPtr->tail->next = newNode;
        newNode->prev = dlListPtr->tail;
    }

    dlListPtr->tail = newNode;
    dlListPtr->curSize++;

    return newNode;
}

ZUORU_DL_LIST_NODE_T* Zuoru_InsertAfterNodeDLList(ZUORU_DL_LIST_T *dlListPtr, ZUORU_DL_LIST_NODE_T *targetNode,
    ZUORU_DL_LIST_NODE_T *inVal)
{
    ZUORU_DL_LIST_NODE_T *newNode = (ZUORU_DL_LIST_NODE_T*)calloc(1, sizeof(ZUORU_DL_LIST_NODE_T));
    memcpy(newNode, inVal, sizeof(ZUORU_DL_LIST_NODE_T));
    newNode->next = NULL;
    newNode->prev = NULL;

    if (targetNode == dlListPtr->tail) {
        newNode->next = NULL;
        dlListPtr->tail = newNode;
    } else {
        newNode->next = targetNode->next;
        targetNode->next->prev = newNode;
    }

    newNode->prev = targetNode;
    targetNode->next = newNode;
    dlListPtr->curSize++;
    return newNode;
}

bool Zuoru_FindDLList(ZUORU_DL_LIST_T *dlListPtr, ZUORU_DATA_T *inVal, ZUORU_DL_LIST_NODE_T *findNode)
{
    ZUORU_DL_LIST_NODE_T *curNode = dlListPtr->head;

    if (dlListPtr->curSize == 0) {
        return false;
    }

    while (memcmp(&curNode->data, inVal, sizeof(ZUORU_DATA_T)) != 0) {
        if (curNode->next == NULL) {
            return false;
        } else {
            curNode = curNode->next;
        }
    }

    memcpy(findNode, curNode, sizeof(ZUORU_DATA_T));
    return true;
}

bool Zuoru_DelDLListWithPtr(ZUORU_DL_LIST_T *dlListPtr, ZUORU_DL_LIST_NODE_T *targetNode)
{
    if (dlListPtr->curSize == 0) {
        return false;
    }

    if (targetNode == dlListPtr->head) {
        dlListPtr->head = targetNode->next;
    } else {
        targetNode->prev->next = targetNode->next;
    }

    if (targetNode == dlListPtr->tail) {
        dlListPtr->tail = targetNode->prev;
    } else {
        targetNode->next->prev = targetNode->prev;
    }

    dlListPtr->curSize--;
    free(targetNode);
    return true;
}

LRUCache* lRUCacheCreate(int capacity)
{
    LRUCache *newLRUCache = calloc(1, sizeof(LRUCache));
    newLRUCache->capacity = capacity;
    newLRUCache->hashTblPtr = (void*)Zuoru_InitIntHashTbl();
    newLRUCache->dLListPtr = (void*)Zuoru_InitDLList();
    newLRUCache->curSize = 0;
    return newLRUCache;
}

int lRUCacheGet(LRUCache *obj, int key)
{
    ZUORU_HASH_TBL_INT_ITEM_H **hashTblPtr =
        (ZUORU_HASH_TBL_INT_ITEM_H**)obj->hashTblPtr;
    ZUORU_DL_LIST_T *dLListPtr =
        (ZUORU_DL_LIST_T*)obj->dLListPtr;
    ZUORU_HASH_TBL_INT_ITEM_H *retItem = NULL;

    if (Zuoru_FindIntHashTbl(hashTblPtr, key,
        &retItem)) {
        Zuoru_DelDLListWithPtr(dLListPtr,
            retItem->hashVal.lListNodePtr);
        retItem->hashVal.lListNodePtr =
            Zuoru_InsertTailDLList(dLListPtr, &retItem);

        return retItem->hashVal.val;
    }

    return -1;
}

void lRUCachePut(LRUCache *obj, int key, int value)
{
    ZUORU_HASH_TBL_INT_ITEM_H **hashTblPtr =
        (ZUORU_HASH_TBL_INT_ITEM_H**)obj->hashTblPtr;
    ZUORU_DL_LIST_T *dLListPtr =
        (ZUORU_DL_LIST_T*)obj->dLListPtr;
    ZUORU_HASH_TBL_INT_ITEM_H *retItem = NULL;
    ZUORU_HASH_DATA_T tmpVal;
    tmpVal.val = value;

    if (obj->curSize < obj->capacity) {
        if (!Zuoru_FindIntHashTbl(hashTblPtr, key, &retItem)) {
            retItem = Zuoru_InsertIntHashTbl(hashTblPtr, key, &tmpVal);
            retItem->hashVal.lListNodePtr =
                Zuoru_InsertTailDLList(dLListPtr, &retItem);
            obj->curSize++;
        } else {
            Zuoru_DelDLListWithPtr(dLListPtr, retItem->hashVal.lListNodePtr);
            memcpy(&retItem->hashVal, &tmpVal, sizeof(ZUORU_HASH_DATA_T));
            retItem->hashVal.lListNodePtr =
                Zuoru_InsertTailDLList(dLListPtr, &retItem);
        }
    } else {
        if (!Zuoru_FindIntHashTbl(hashTblPtr, key, &retItem)) {
            Zuoru_DelIntHashTbl(hashTblPtr, dLListPtr->head->data);
            Zuoru_DelDLListWithPtr(dLListPtr, dLListPtr->head);

            retItem = Zuoru_InsertIntHashTbl(hashTblPtr, key, &tmpVal);
            retItem->hashVal.lListNodePtr =
                Zuoru_InsertTailDLList(dLListPtr, &retItem);
        } else {
            Zuoru_DelDLListWithPtr(dLListPtr, retItem->hashVal.lListNodePtr);
            memcpy(&retItem->hashVal, &tmpVal, sizeof(ZUORU_HASH_DATA_T));
            retItem->hashVal.lListNodePtr =
                Zuoru_InsertTailDLList(dLListPtr, &retItem);
        }
    }

    return;
}

void lRUCacheFree(LRUCache *obj)
{
    ZUORU_HASH_TBL_INT_ITEM_H **hashTblPtr =
        (ZUORU_HASH_TBL_INT_ITEM_H**)obj->hashTblPtr;
    ZUORU_DL_LIST_T *dLListPtr =
        (ZUORU_DL_LIST_T*)obj->dLListPtr;
    Zuoru_FreeIntHashTbl(hashTblPtr);
    Zuoru_FreeDLList(dLListPtr);
    free(obj);
    return;
}
