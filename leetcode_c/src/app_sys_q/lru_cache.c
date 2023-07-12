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

#include "../../include/app_sys_q.h"
#include "../../../common_include/third_party/uthash.h"

typedef struct {
    int val;
    void *lListNodePtr;
} ZUORU_HashData;

typedef struct {
    int hashKey;
    ZUORU_HashData hashVal;
    UT_hash_handle hh;
} ZUORU_HashTblIntItem;

typedef ZUORU_HashTblIntItem* ZUORU_DataItem;

ZUORU_HashTblIntItem** ZUORU_InitIntHashTbl()
{
    ZUORU_HashTblIntItem **hashTblPtr = (ZUORU_HashTblIntItem**)calloc(1,
        sizeof(ZUORU_HashTblIntItem*));
    *hashTblPtr = NULL;
    return hashTblPtr;
}

ZUORU_HashTblIntItem* ZUORU_InsertIntHashTbl(ZUORU_HashTblIntItem **hashTblPtr,
    int key, ZUORU_HashData *inVal)
{
    ZUORU_HashTblIntItem *tmpHashItem;

    HASH_FIND_INT(*hashTblPtr, &key, tmpHashItem);
    if (tmpHashItem == NULL) {
        tmpHashItem = (ZUORU_HashTblIntItem*)calloc(1, sizeof(ZUORU_HashTblIntItem));
        tmpHashItem->hashKey = key;
        HASH_ADD_INT(*hashTblPtr, hashKey, tmpHashItem);
    }
    memcpy(&tmpHashItem->hashVal, inVal, sizeof(ZUORU_HashData));
    return tmpHashItem;
}

bool ZUORU_FindIntHashTbl(ZUORU_HashTblIntItem **hashTblPtr, int key,
    ZUORU_HashTblIntItem **ret)
{
    ZUORU_HashTblIntItem *tmpHashItem = NULL;
    HASH_FIND_INT(*hashTblPtr, &key, tmpHashItem);
    if (tmpHashItem == NULL) {
        *ret = NULL;
        return false;
    }

    *ret = tmpHashItem;
    return true;
}

void ZUORU_DelIntHashTbl(ZUORU_HashTblIntItem **hashTblPtr,
    ZUORU_HashTblIntItem *hashItem)
{
    HASH_DEL(*hashTblPtr, hashItem);
    free(hashItem);
    return;
}

void ZUORU_FreeIntHashTbl(ZUORU_HashTblIntItem **hashTblPtr)
{
    ZUORU_HashTblIntItem *curItem;
    ZUORU_HashTblIntItem *tmpItem;

    HASH_ITER(hh, *hashTblPtr, curItem, tmpItem) {
        HASH_DEL(*hashTblPtr, curItem);
        free(curItem);
    }
    free(hashTblPtr);
    return;
}

struct ZUORU_DLListNode {
    ZUORU_DataItem data;
    struct ZUORU_DLListNode *next;
    struct ZUORU_DLListNode *prev;
};

typedef struct ZUORU_DLListNode ZUORU_DLListNode;

typedef struct {
    ZUORU_DLListNode *head;
    ZUORU_DLListNode *tail;
    int curSize;
} ZUORU_DLList;

ZUORU_DLList* ZUORU_InitDLList()
{
    ZUORU_DLList *dlListPtr = (ZUORU_DLList*)calloc(1, sizeof(ZUORU_DLList));
    dlListPtr->head = NULL;
    dlListPtr->tail = NULL;
    dlListPtr->curSize = 0;
    return dlListPtr;
}

void ZUORU_FreeDLList(ZUORU_DLList *dlListPtr)
{
    ZUORU_DLListNode *curNode = dlListPtr->head;
    ZUORU_DLListNode *delNode = NULL;

    while (curNode != NULL) {
        delNode = curNode;
        curNode = curNode->next;
        free(delNode);
    }

    free(dlListPtr);
    return;
}

ZUORU_DLListNode* ZUORU_InsertHeadDLList(ZUORU_DLList *dlListPtr, ZUORU_DataItem *inVal)
{
    ZUORU_DLListNode *newNode = (ZUORU_DLListNode*)calloc(1, sizeof(ZUORU_DLListNode));
    memcpy(&newNode->data, inVal, sizeof(ZUORU_DataItem));
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

ZUORU_DLListNode* ZUORU_InsertTailDLList(ZUORU_DLList *dlListPtr, ZUORU_DataItem *inVal)
{
    ZUORU_DLListNode *newNode = (ZUORU_DLListNode*)calloc(1, sizeof(ZUORU_DLListNode));
    memcpy(&newNode->data, inVal, sizeof(ZUORU_DataItem));
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

ZUORU_DLListNode* ZUORU_InsertAfterNodeDLList(ZUORU_DLList *dlListPtr, ZUORU_DLListNode *targetNode,
    ZUORU_DLListNode *inVal)
{
    ZUORU_DLListNode *newNode = (ZUORU_DLListNode*)calloc(1, sizeof(ZUORU_DLListNode));
    memcpy(newNode, inVal, sizeof(ZUORU_DLListNode));
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

bool ZUORU_FindDLList(ZUORU_DLList *dlListPtr, ZUORU_DataItem *inVal, ZUORU_DLListNode *findNode)
{
    ZUORU_DLListNode *curNode = dlListPtr->head;

    if (dlListPtr->curSize == 0) {
        return false;
    }

    while (memcmp(&curNode->data, inVal, sizeof(ZUORU_DataItem)) != 0) {
        if (curNode->next == NULL) {
            return false;
        } else {
            curNode = curNode->next;
        }
    }

    memcpy(findNode, curNode, sizeof(ZUORU_DataItem));
    return true;
}

bool ZUORU_DelDLListWithPtr(ZUORU_DLList *dlListPtr, ZUORU_DLListNode *targetNode)
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
    newLRUCache->hashTblPtr = (void*)ZUORU_InitIntHashTbl();
    newLRUCache->dLListPtr = (void*)ZUORU_InitDLList();
    newLRUCache->curSize = 0;
    return newLRUCache;
}

int lRUCacheGet(LRUCache *obj, int key)
{
    ZUORU_HashTblIntItem **hashTblPtr =
        (ZUORU_HashTblIntItem**)obj->hashTblPtr;
    ZUORU_DLList *dLListPtr =
        (ZUORU_DLList*)obj->dLListPtr;
    ZUORU_HashTblIntItem *retItem = NULL;

    if (ZUORU_FindIntHashTbl(hashTblPtr, key,
        &retItem)) {
        ZUORU_DelDLListWithPtr(dLListPtr,
            retItem->hashVal.lListNodePtr);
        retItem->hashVal.lListNodePtr =
            ZUORU_InsertTailDLList(dLListPtr, &retItem);

        return retItem->hashVal.val;
    }

    return -1;
}

void lRUCachePut(LRUCache *obj, int key, int value)
{
    ZUORU_HashTblIntItem **hashTblPtr =
        (ZUORU_HashTblIntItem**)obj->hashTblPtr;
    ZUORU_DLList *dLListPtr =
        (ZUORU_DLList*)obj->dLListPtr;
    ZUORU_HashTblIntItem *retItem = NULL;
    ZUORU_HashData tmpVal;
    tmpVal.val = value;

    if (obj->curSize < obj->capacity) {
        if (!ZUORU_FindIntHashTbl(hashTblPtr, key, &retItem)) {
            retItem = ZUORU_InsertIntHashTbl(hashTblPtr, key, &tmpVal);
            retItem->hashVal.lListNodePtr =
                ZUORU_InsertTailDLList(dLListPtr, &retItem);
            obj->curSize++;
        } else {
            ZUORU_DelDLListWithPtr(dLListPtr, retItem->hashVal.lListNodePtr);
            memcpy(&retItem->hashVal, &tmpVal, sizeof(ZUORU_HashData));
            retItem->hashVal.lListNodePtr =
                ZUORU_InsertTailDLList(dLListPtr, &retItem);
        }
    } else {
        if (!ZUORU_FindIntHashTbl(hashTblPtr, key, &retItem)) {
            ZUORU_DelIntHashTbl(hashTblPtr, dLListPtr->head->data);
            ZUORU_DelDLListWithPtr(dLListPtr, dLListPtr->head);

            retItem = ZUORU_InsertIntHashTbl(hashTblPtr, key, &tmpVal);
            retItem->hashVal.lListNodePtr =
                ZUORU_InsertTailDLList(dLListPtr, &retItem);
        } else {
            ZUORU_DelDLListWithPtr(dLListPtr, retItem->hashVal.lListNodePtr);
            memcpy(&retItem->hashVal, &tmpVal, sizeof(ZUORU_HashData));
            retItem->hashVal.lListNodePtr =
                ZUORU_InsertTailDLList(dLListPtr, &retItem);
        }
    }

    return;
}

void lRUCacheFree(LRUCache *obj)
{
    ZUORU_HashTblIntItem **hashTblPtr =
        (ZUORU_HashTblIntItem**)obj->hashTblPtr;
    ZUORU_DLList *dLListPtr =
        (ZUORU_DLList*)obj->dLListPtr;
    ZUORU_FreeIntHashTbl(hashTblPtr);
    ZUORU_FreeDLList(dLListPtr);
    free(obj);
    return;
}
