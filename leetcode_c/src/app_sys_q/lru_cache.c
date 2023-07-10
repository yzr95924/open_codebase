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
} Zuoru_Hash_Data;

typedef struct {
    int hashKey;
    Zuoru_Hash_Data hashVal;
    UT_hash_handle hh;
} Zuoru_HashTbl_Item;

typedef Zuoru_HashTbl_Item* Zuoru_Data;

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

struct Zuoru_DLList_Node {
    Zuoru_Data data;
    struct Zuoru_DLList_Node *next;
    struct Zuoru_DLList_Node *prev;
};

typedef struct Zuoru_DLList_Node Zuoru_DLList_Node;

typedef struct {
    Zuoru_DLList_Node *head;
    Zuoru_DLList_Node *tail;
    int curSize;
} Zuoru_DLList;

Zuoru_DLList* ZuoruInitDLList()
{
    Zuoru_DLList *dlListPtr = (Zuoru_DLList*)calloc(1, sizeof(Zuoru_DLList));
    dlListPtr->head = NULL;
    dlListPtr->tail = NULL;
    dlListPtr->curSize = 0;
    return dlListPtr;
}

void ZuoruFreeDLList(Zuoru_DLList *dlListPtr)
{
    Zuoru_DLList_Node *curNode = dlListPtr->head;
    Zuoru_DLList_Node *delNode = NULL;

    while (curNode != NULL) {
        delNode = curNode;
        curNode = curNode->next;
        free(delNode);
    }

    free(dlListPtr);
    return;
}

Zuoru_DLList_Node* ZuoruInsertHeadDLList(Zuoru_DLList *dlListPtr, Zuoru_Data *inVal)
{
    Zuoru_DLList_Node *newNode = (Zuoru_DLList_Node*)calloc(1, sizeof(Zuoru_DLList_Node));
    memcpy(&newNode->data, inVal, sizeof(Zuoru_Data));
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

Zuoru_DLList_Node* ZuoruInsertTailDLList(Zuoru_DLList *dlListPtr, Zuoru_Data *inVal)
{
    Zuoru_DLList_Node *newNode = (Zuoru_DLList_Node*)calloc(1, sizeof(Zuoru_DLList_Node));
    memcpy(&newNode->data, inVal, sizeof(Zuoru_Data));
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

Zuoru_DLList_Node* ZuoruInsertAfterNodeDLList(Zuoru_DLList *dlListPtr, Zuoru_DLList_Node *targetNode,
    Zuoru_DLList_Node *inVal)
{
    Zuoru_DLList_Node *newNode = (Zuoru_DLList_Node*)calloc(1, sizeof(Zuoru_DLList_Node));
    memcpy(newNode, inVal, sizeof(Zuoru_DLList_Node));
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

bool ZuoruFindDLList(Zuoru_DLList *dlListPtr, Zuoru_Data *inVal, Zuoru_DLList_Node *findNode)
{
    Zuoru_DLList_Node *curNode = dlListPtr->head;

    if (dlListPtr->curSize == 0) {
        return false;
    }

    while (memcmp(&curNode->data, inVal, sizeof(Zuoru_Data)) != 0) {
        if (curNode->next == NULL) {
            return false;
        } else {
            curNode = curNode->next;
        }
    }

    memcpy(findNode, curNode, sizeof(Zuoru_Data));
    return true;
}

bool ZuoruDelDLListWithPtr(Zuoru_DLList *dlListPtr, Zuoru_DLList_Node *targetNode)
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
    newLRUCache->hashTblPtr = (void*)ZuoruInitIntHashTbl();
    newLRUCache->dLListPtr = (void*)ZuoruInitDLList();
    newLRUCache->curSize = 0;
    return newLRUCache;
}

int lRUCacheGet(LRUCache *obj, int key)
{
    Zuoru_HashTbl_Item **hashTblPtr =
        (Zuoru_HashTbl_Item**)obj->hashTblPtr;
    Zuoru_DLList *dLListPtr =
        (Zuoru_DLList*)obj->dLListPtr;
    Zuoru_HashTbl_Item *retItem = NULL;

    if (ZuoruFindIntHashTbl(hashTblPtr, key,
        &retItem)) {
        ZuoruDelDLListWithPtr(dLListPtr,
            retItem->hashVal.lListNodePtr);
        retItem->hashVal.lListNodePtr =
            ZuoruInsertTailDLList(dLListPtr, &retItem);

        return retItem->hashVal.val;
    }

    return -1;
}

void lRUCachePut(LRUCache *obj, int key, int value)
{
    Zuoru_HashTbl_Item **hashTblPtr =
        (Zuoru_HashTbl_Item**)obj->hashTblPtr;
    Zuoru_DLList *dLListPtr =
        (Zuoru_DLList*)obj->dLListPtr;
    Zuoru_HashTbl_Item *retItem = NULL;
    Zuoru_Hash_Data tmpVal;
    tmpVal.val = value;

    if (obj->curSize < obj->capacity) {
        if (!ZuoruFindIntHashTbl(hashTblPtr, key, &retItem)) {
            retItem = ZuoruInsertIntHashTbl(hashTblPtr, key, &tmpVal);
            retItem->hashVal.lListNodePtr =
                ZuoruInsertTailDLList(dLListPtr, &retItem);
            obj->curSize++;
        } else {
            ZuoruDelDLListWithPtr(dLListPtr, retItem->hashVal.lListNodePtr);
            memcpy(&retItem->hashVal, &tmpVal, sizeof(Zuoru_Hash_Data));
            retItem->hashVal.lListNodePtr =
                ZuoruInsertTailDLList(dLListPtr, &retItem);
        }
    } else {
        if (!ZuoruFindIntHashTbl(hashTblPtr, key, &retItem)) {
            ZuoruDelIntHashTbl(hashTblPtr, dLListPtr->head->data);
            ZuoruDelDLListWithPtr(dLListPtr, dLListPtr->head);

            retItem = ZuoruInsertIntHashTbl(hashTblPtr, key, &tmpVal);
            retItem->hashVal.lListNodePtr =
                ZuoruInsertTailDLList(dLListPtr, &retItem);
        } else {
            ZuoruDelDLListWithPtr(dLListPtr, retItem->hashVal.lListNodePtr);
            memcpy(&retItem->hashVal, &tmpVal, sizeof(Zuoru_Hash_Data));
            retItem->hashVal.lListNodePtr =
                ZuoruInsertTailDLList(dLListPtr, &retItem);
        }
    }

    return;
}

void lRUCacheFree(LRUCache *obj)
{
    Zuoru_HashTbl_Item **hashTblPtr =
        (Zuoru_HashTbl_Item**)obj->hashTblPtr;
    Zuoru_DLList *dLListPtr =
        (Zuoru_DLList*)obj->dLListPtr;
    ZuoruFreeIntHashTbl(hashTblPtr);
    ZuoruFreeDLList(dLListPtr);
    free(obj);
    return;
}
