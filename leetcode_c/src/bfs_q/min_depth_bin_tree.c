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

int minDepth(struct TreeNode* root)
{
    if (root == NULL) {
        return 0;
    }

    ZUORU_QUEUE_T *myQueuePtr = Zuoru_InitQueue(100000);
    Zuoru_EnQueue(myQueuePtr, root);
    int depth = 1;

    struct TreeNode tmpTreeNode;
    while (!Zuoru_IsEmptyQueue(myQueuePtr)) {
        int curQueueSize = myQueuePtr->curSize;

        for (int idx = 0; idx < curQueueSize; idx++) {
            Zuoru_DeQueue(myQueuePtr, &tmpTreeNode);

            if (tmpTreeNode.left == NULL && tmpTreeNode.right == NULL) {
                break;
            }
            if (tmpTreeNode.left != NULL) {
                Zuoru_EnQueue(myQueuePtr, tmpTreeNode.left);
            }
            if (tmpTreeNode.right != NULL) {
                Zuoru_EnQueue(myQueuePtr, tmpTreeNode.right);
            }
        }
        depth++;
    }

    Zuoru_FreeQueue(myQueuePtr);
    return depth;
}
