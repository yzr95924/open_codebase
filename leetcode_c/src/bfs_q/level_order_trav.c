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

    Zuoru_Queue *myQueuePtr = ZuoruInitQueue(maxLevel);
    ZuoruEnQueue(myQueuePtr, root);

    struct TreeNode tmpTreeNode;
    while(!ZuoruIsEmptyQueue(myQueuePtr)) {
        int curQueueSize = myQueuePtr->curSize;

        for (int idx = 0; idx < curQueueSize; idx++) {
            ZuoruDeQueue(myQueuePtr, &tmpTreeNode);
            (*returnColumnSizes)[curLevel]++;
            retArr[curLevel][curLevelIdx] = tmpTreeNode.val;
            curLevelIdx++;

            if (tmpTreeNode.left == NULL && tmpTreeNode.right == NULL) {
                continue;
            }
            if (tmpTreeNode.left != NULL) {
                ZuoruEnQueue(myQueuePtr, tmpTreeNode.left);
            }
            if (tmpTreeNode.right != NULL) {
                ZuoruEnQueue(myQueuePtr, tmpTreeNode.right);
            }
        }
        curLevel++;
        curLevelIdx = 0;
        (*returnSize)++;
    }

    ZuoruFreeQueue(myQueuePtr);

    return retArr;
}
