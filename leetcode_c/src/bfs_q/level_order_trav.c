/**
 * @file level_order_trav.c
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/binary-tree-level-order-traversal/description/
 * @version 0.1
 * @date 2023-07-06
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../../include/bfs_q.h"

#define MY_DATA_STRUCT_EMPTY_POS -1

typedef struct TreeNode ZUORU_DATA_T;

typedef struct {
    ZUORU_DATA_T *data;
    int head;
    int rear;
    int capacity;
    int curSize;
} ZUORU_QUEUE_T;

ZUORU_QUEUE_T* Zuoru_InitQueue(int capacity)
{
    ZUORU_QUEUE_T *queuePtr = (ZUORU_QUEUE_T*)calloc(1, sizeof(ZUORU_QUEUE_T));
    queuePtr->data = (ZUORU_DATA_T*)calloc(capacity, sizeof(ZUORU_DATA_T));
    queuePtr->head = MY_DATA_STRUCT_EMPTY_POS;
    queuePtr->rear = MY_DATA_STRUCT_EMPTY_POS;
    queuePtr->capacity = capacity;
    queuePtr->curSize = 0;

    return queuePtr;
}

bool Zuoru_EnQueue(ZUORU_QUEUE_T *queuePtr, ZUORU_DATA_T *inVal)
{
    if (queuePtr->curSize + 1 > queuePtr->capacity) {
        fprintf(stderr, "queue is full\n");
        return false;
    }

    if (queuePtr->head == MY_DATA_STRUCT_EMPTY_POS) {
        queuePtr->head = 0;
    }
    queuePtr->rear = (queuePtr->rear + 1) % queuePtr->capacity;
    memcpy(&queuePtr->data[queuePtr->rear], inVal, sizeof(ZUORU_DATA_T));

    queuePtr->curSize++;
    return true;
}

bool Zuoru_DeQueue(ZUORU_QUEUE_T *queuePtr, ZUORU_DATA_T *outVal)
{
    if (queuePtr->curSize == 0) {
        fprintf(stderr, "queue is empty\n");
        return false;
    }

    memcpy(outVal, &queuePtr->data[queuePtr->head], sizeof(ZUORU_DATA_T));
    if (queuePtr->head == queuePtr->rear) {
        queuePtr->rear = MY_DATA_STRUCT_EMPTY_POS;
        queuePtr->head = MY_DATA_STRUCT_EMPTY_POS;
    }
    queuePtr->head = (queuePtr->head + 1) % queuePtr->capacity;

    queuePtr->curSize--;
    return true;
}

bool Zuoru_IsFullQueue(ZUORU_QUEUE_T *queuePtr)
{
    if (queuePtr->curSize == queuePtr->capacity) {
        return true;
    }
    return false;
}

bool Zuoru_IsEmptyQueue(ZUORU_QUEUE_T *queuePtr)
{
    if (queuePtr->curSize == 0) {
        return true;
    }
    return false;
}

void Zuoru_FreeQueue(ZUORU_QUEUE_T *queuePtr)
{
    free(queuePtr->data);
    free(queuePtr);
    return;
}

/**
 * @brief Binary Tree Level Order Traversal
 *
 * @param root root ptr
 * @param returnSize return array
 * @param returnColumnSizes
 * @return int**
 */
int** levelOrder(struct TreeNode* root, int* returnSize, int** returnColumnSizes)
{
    int **retArr = NULL;
    int maxLevelNodeNum = 2000 / 2;
    int maxLevel = 2000;
    *returnSize = 0;
    int curLevel = 0;
    int curLevelIdx = 0;

    if (root == NULL) {
        return NULL;
    }

    retArr = (int**)calloc(maxLevel, sizeof(int*));
    for (int idx = 0; idx < maxLevel; idx++) {
        retArr[idx] = (int*)calloc(maxLevelNodeNum, sizeof(int));
    }
    *returnColumnSizes = (int*)calloc(maxLevel, sizeof(int));

    ZUORU_QUEUE_T *myQueuePtr = Zuoru_InitQueue(maxLevel);
    Zuoru_EnQueue(myQueuePtr, root);

    struct TreeNode tmpTreeNode;
    while(!Zuoru_IsEmptyQueue(myQueuePtr)) {
        int curQueueSize = myQueuePtr->curSize;

        for (int idx = 0; idx < curQueueSize; idx++) {
            Zuoru_DeQueue(myQueuePtr, &tmpTreeNode);
            (*returnColumnSizes)[curLevel]++;
            retArr[curLevel][curLevelIdx] = tmpTreeNode.val;
            curLevelIdx++;

            if (tmpTreeNode.left == NULL && tmpTreeNode.right == NULL) {
                continue;
            }
            if (tmpTreeNode.left != NULL) {
                Zuoru_EnQueue(myQueuePtr, tmpTreeNode.left);
            }
            if (tmpTreeNode.right != NULL) {
                Zuoru_EnQueue(myQueuePtr, tmpTreeNode.right);
            }
        }
        curLevel++;
        curLevelIdx = 0;
        (*returnSize)++;
    }

    Zuoru_FreeQueue(myQueuePtr);

    return retArr;
}
