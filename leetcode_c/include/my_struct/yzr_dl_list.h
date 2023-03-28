/**
 * @file yzr_dl_list.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief my double linked list
 * @version 0.1
 * @date 2023-03-26
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef LEETCODE_YZR_DL_LIST_H
#define LEETCODE_YZR_DL_LIST_H

#include "../const.h"

typedef struct {
    int data;
    int key;
    YzrDLListNode* nextNode;
    YzrDLListNode* prevNode;
} YzrDLListNode;

typedef struct {
    YzrDLListNode* headNode;
    YzrDLListNode* lastNode;
    int curSize;
} YzrDLList;

YzrDLList* YzrDLListCreateList()
{
    YzrDLList* newList = NULL;
    newList = (YzrDLList*)calloc(1, sizeof(YzrDLList));
    newList->curSize = 0;
    newList->headNode = NULL;
    newList->lastNode = NULL;
    return newList;
}

YzrDLListNode* YzrDLListInsertFirst(YzrDLList* inputList, int key, int data)
{
    YzrDLListNode* newNode = (YzrDLListNode*)calloc(1, sizeof(YzrDLListNode));
    newNode->key = key;
    newNode->data = data;
    newNode->nextNode = NULL;
    newNode->prevNode = NULL;

    if (inputList->curSize == 0) {
        inputList->lastNode = newNode;
    } else {
        inputList->headNode->prevNode = newNode;
        newNode->nextNode = inputList->headNode;
    }

    inputList->headNode = newNode;
    inputList->curSize++;

    return newNode;
}

YzrDLListNode* YzrDLListInsertLast(YzrDLList* inputList, int key, int data)
{
    YzrDLListNode* newNode = (YzrDLListNode*)calloc(1, sizeof(YzrDLListNode));
    newNode->key = key;
    newNode->data = data;
    newNode->nextNode = NULL;
    newNode->prevNode = NULL;

    if (inputList->curSize == 0) {
        inputList->headNode = newNode;
    } else {
        inputList->lastNode->nextNode = newNode;
        newNode->prevNode = inputList->lastNode;
    }

    inputList->lastNode = newNode;
    inputList->curSize++;

    return newNode;
}

bool YzrDLListInsertAfterKey(YzrDLList* inputLast, int key, int newKey, int newData)
{
    YzrDLListNode* curNode = inputLast->headNode;

    if (inputLast->curSize == 0) {
        return false;
    }

    while (curNode->key != key) {
        if (curNode->nextNode == NULL) {
            return false;
        } else {
            curNode = curNode->nextNode;
        }
    }

    YzrDLListNode* newNode = (YzrDLListNode*)calloc(1, sizeof(YzrDLListNode));
    newNode->key = newKey;
    newNode->data = newData;
    newNode->nextNode = NULL;
    newNode->prevNode = NULL;

    if (curNode == inputLast->lastNode) {
        newNode->nextNode = NULL;
        inputLast->lastNode = newNode;
    } else {
        newNode->nextNode = curNode->nextNode;
        curNode->nextNode->prevNode = newNode;
    }

    newNode->prevNode = curNode;
    curNode->nextNode = newNode;
    inputLast->curSize++;
    return true;
}

bool YzrDLListDeleteWithKey(YzrDLList* inputList, int key)
{
    YzrDLListNode* curNode = inputList->headNode;

    if (inputList->curSize == 0) {
        return false;
    }

    while (curNode->key != key) {
        if (curNode->nextNode == NULL) {
            return false;
        } else {
            curNode = curNode->nextNode;
        }
    }

    if (curNode == inputList->headNode) {
        inputList->headNode = curNode->nextNode;
    } else {
        curNode->prevNode->nextNode = curNode->nextNode;
    }

    if (curNode == inputList->lastNode) {
        inputList->lastNode = curNode->prevNode;
    } else {
        curNode->nextNode->prevNode = curNode->prevNode;
    }

    inputList->curSize--;
    free(curNode);
    return true;
}

bool YzrDLListDeleteWithPtr(YzrDLList* inputList, YzrDLListNode* targetNode)
{
    if (inputList->curSize == 0) {
        return false;
    }

    if (targetNode == inputList->headNode) {
        inputList->headNode = targetNode->nextNode;
    } else {
        targetNode->prevNode->nextNode = targetNode->nextNode;
    }

    if (targetNode == inputList->lastNode) {
        inputList->lastNode = targetNode->prevNode;
    } else {
        targetNode->nextNode->prevNode = targetNode->prevNode;
    }

    inputList->curSize--;
    free(targetNode);
    return true;
}

YzrDLListNode* YzrDLListFindKey(YzrDLList* inputList, int key)
{
    YzrDLListNode* curNode = inputList->headNode;

    if (inputList->curSize == 0) {
        return NULL;
    }

    while (curNode->key != key) {
        if (curNode->nextNode == NULL) {
            return NULL;
        } else {
            curNode = curNode->nextNode;
        }
    }

    return curNode;
}

void YzrDLListDeleteAll(YzrDLList* inputList)
{
    YzrDLListNode* curNode = inputList->headNode;
    YzrDLListNode* delNode = NULL;

    while (curNode != NULL) {
        delNode = curNode;
        curNode = curNode->nextNode;
        free(delNode);
    }

    free(inputList);
    return ;
}

#endif