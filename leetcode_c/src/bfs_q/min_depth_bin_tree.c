/**
 * @file min_depth_bin_tree.c
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/minimum-depth-of-binary-tree/
 * @version 0.1
 * @date 2023-07-05
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../../include/bfs_q.h"

#define MY_DATA_STRUCT_EMPTY_POS (-1)

typedef struct TreeNode ZUORU_DataItem;

typedef struct {
    ZUORU_DataItem *data;
    int head;
    int rear;
    int capacity;
    int curSize;
} ZUORU_Queue;

ZUORU_Queue* ZUORU_InitQueue(int capacity)
{
    ZUORU_Queue *queuePtr = (ZUORU_Queue*)calloc(1, sizeof(ZUORU_Queue));
    queuePtr->data = (ZUORU_DataItem*)calloc(capacity, sizeof(ZUORU_DataItem));
    queuePtr->head = MY_DATA_STRUCT_EMPTY_POS;
    queuePtr->rear = MY_DATA_STRUCT_EMPTY_POS;
    queuePtr->capacity = capacity;
    queuePtr->curSize = 0;

    return queuePtr;
}

bool ZUORU_EnQueue(ZUORU_Queue *queuePtr, ZUORU_DataItem *inVal)
{
    if (queuePtr->curSize + 1 > queuePtr->capacity) {
        fprintf(stderr, "queue is full\n");
        return false;
    }

    if (queuePtr->head == MY_DATA_STRUCT_EMPTY_POS) {
        queuePtr->head = 0;
    }
    queuePtr->rear = (queuePtr->rear + 1) % queuePtr->capacity;
    memcpy(&queuePtr->data[queuePtr->rear], inVal, sizeof(ZUORU_DataItem));

    queuePtr->curSize++;
    return true;
}

bool ZUORU_DeQueue(ZUORU_Queue *queuePtr, ZUORU_DataItem *outVal)
{
    if (queuePtr->curSize == 0) {
        fprintf(stderr, "queue is empty\n");
        return false;
    }

    memcpy(outVal, &queuePtr->data[queuePtr->head], sizeof(ZUORU_DataItem));
    if (queuePtr->head == queuePtr->rear) {
        queuePtr->rear = MY_DATA_STRUCT_EMPTY_POS;
        queuePtr->head = MY_DATA_STRUCT_EMPTY_POS;
    }
    queuePtr->head = (queuePtr->head + 1) % queuePtr->capacity;

    queuePtr->curSize--;
    return true;
}

bool ZUORU_IsFullQueue(ZUORU_Queue *queuePtr)
{
    if (queuePtr->curSize == queuePtr->capacity) {
        return true;
    }
    return false;
}

bool ZUORU_IsEmptyQueue(ZUORU_Queue *queuePtr)
{
    if (queuePtr->curSize == 0) {
        return true;
    }
    return false;
}

void ZUORU_FreeQueue(ZUORU_Queue *queuePtr)
{
    free(queuePtr->data);
    free(queuePtr);
    return;
}

int minDepth(struct TreeNode* root)
{
    if (root == NULL) {
        return 0;
    }

    ZUORU_Queue *myQueuePtr = ZUORU_InitQueue(100000);
    ZUORU_EnQueue(myQueuePtr, root);
    int depth = 1;

    struct TreeNode tmpTreeNode;
    while (!ZUORU_IsEmptyQueue(myQueuePtr)) {
        int curQueueSize = myQueuePtr->curSize;

        for (int idx = 0; idx < curQueueSize; idx++) {
            ZUORU_DeQueue(myQueuePtr, &tmpTreeNode);
            if (tmpTreeNode.left == NULL && tmpTreeNode.right == NULL) {
                ZUORU_FreeQueue(myQueuePtr);
                return depth;
            }
            if (tmpTreeNode.left != NULL) {
                ZUORU_EnQueue(myQueuePtr, tmpTreeNode.left);
            }
            if (tmpTreeNode.right != NULL) {
                ZUORU_EnQueue(myQueuePtr, tmpTreeNode.right);
            }
        }
        depth++;
    }

    ZUORU_FreeQueue(myQueuePtr);
    return depth;
}
