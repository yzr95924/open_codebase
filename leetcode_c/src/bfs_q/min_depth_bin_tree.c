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

typedef struct TreeNode Zuoru_Data;

typedef struct {
    Zuoru_Data *data;
    int head;
    int rear;
    int capacity;
    int curSize;
} Zuoru_Queue;

Zuoru_Queue* ZuoruInitQueue(int capacity)
{
    Zuoru_Queue *queuePtr = (Zuoru_Queue*)calloc(1, sizeof(Zuoru_Queue));
    queuePtr->data = (Zuoru_Data*)calloc(capacity, sizeof(Zuoru_Data));
    queuePtr->head = MY_DATA_STRUCT_EMPTY_POS;
    queuePtr->rear = MY_DATA_STRUCT_EMPTY_POS;
    queuePtr->capacity = capacity;
    queuePtr->curSize = 0;

    return queuePtr;
}

bool ZuoruEnQueue(Zuoru_Queue *queuePtr, Zuoru_Data *inVal)
{
    if (queuePtr->curSize + 1 > queuePtr->capacity) {
        fprintf(stderr, "queue is full\n");
        return false;
    }

    if (queuePtr->head == MY_DATA_STRUCT_EMPTY_POS) {
        queuePtr->head = 0;
    }
    queuePtr->rear = (queuePtr->rear + 1) % queuePtr->capacity;
    memcpy(&queuePtr->data[queuePtr->rear], inVal, sizeof(Zuoru_Data));

    queuePtr->curSize++;
    return true;
}

bool ZuoruDeQueue(Zuoru_Queue *queuePtr, Zuoru_Data *outVal)
{
    if (queuePtr->curSize == 0) {
        fprintf(stderr, "queue is empty\n");
        return false;
    }

    memcpy(outVal, &queuePtr->data[queuePtr->head], sizeof(Zuoru_Data));
    if (queuePtr->head == queuePtr->rear) {
        queuePtr->rear = MY_DATA_STRUCT_EMPTY_POS;
        queuePtr->head = MY_DATA_STRUCT_EMPTY_POS;
    }
    queuePtr->head = (queuePtr->head + 1) % queuePtr->capacity;

    queuePtr->curSize--;
    return true;
}

bool ZuoruIsFullQueue(Zuoru_Queue *queuePtr)
{
    if (queuePtr->curSize == queuePtr->capacity) {
        return true;
    }
    return false;
}

bool ZuoruIsEmptyQueue(Zuoru_Queue *queuePtr)
{
    if (queuePtr->curSize == 0) {
        return true;
    }
    return false;
}

void ZuoruFreeQueue(Zuoru_Queue *queuePtr)
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

    Zuoru_Queue *myQueuePtr = ZuoruInitQueue(100000);
    ZuoruEnQueue(myQueuePtr, root);
    int depth = 1;

    struct TreeNode tmpTreeNode;
    while (!ZuoruIsEmptyQueue(myQueuePtr)) {
        int curQueueSize = myQueuePtr->curSize;

        for (int idx = 0; idx < curQueueSize; idx++) {
            ZuoruDeQueue(myQueuePtr, &tmpTreeNode);
            if (tmpTreeNode.left == NULL && tmpTreeNode.right == NULL) {
                ZuoruFreeQueue(myQueuePtr);
                return depth;
            }
            if (tmpTreeNode.left != NULL) {
                ZuoruEnQueue(myQueuePtr, tmpTreeNode.left);
            }
            if (tmpTreeNode.right != NULL) {
                ZuoruEnQueue(myQueuePtr, tmpTreeNode.right);
            }
        }
        depth++;
    }

    ZuoruFreeQueue(myQueuePtr);
    return depth;
}
