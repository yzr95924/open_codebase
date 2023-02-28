/**
 * @file min_depth_binary_tree.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/minimum-depth-of-binary-tree/
 * @version 0.1
 * @date 2023-02-26
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef LEETCODE_MIN_DEPTH_BINARY_TREE_H
#define LEETCODE_MIN_DEPTH_BINARY_TREE_H

#include "../../include/const.h"

#define MAX_TREE_NUM (100000)
#define EMPTY_POS -1

 struct TreeNode {
     int val;
     struct TreeNode *left;
     struct TreeNode *right;
 } TreeNode;

 typedef struct TreeNode TreeNode;

typedef struct {
    TreeNode* data;
    int head;
    int rear;
    int capacity;
    int curSize;
} MyQueue_T;

MyQueue_T* InitMyQueue(int capacity) {
    MyQueue_T* queuePtr = (MyQueue_T*)calloc(1, sizeof(MyQueue_T));
    queuePtr->data = (TreeNode*)calloc(capacity, sizeof(TreeNode));
    queuePtr->head = EMPTY_POS;
    queuePtr->rear = EMPTY_POS;
    queuePtr->capacity = capacity;
    queuePtr->curSize = 0;

    return queuePtr;
}

void EnMyQueue(MyQueue_T* queuePtr, TreeNode* inVal) {
    if (queuePtr->head == EMPTY_POS) {
        queuePtr->head = 0;
    }
    queuePtr->rear = (queuePtr->rear + 1) % queuePtr->capacity;
    memcpy(&queuePtr->data[queuePtr->rear], inVal, sizeof(TreeNode));

    queuePtr->curSize++;
    return ;
}

void DeMyQueue(MyQueue_T* queuePtr, TreeNode* outVal) {
    mempcpy(outVal, &queuePtr->data[queuePtr->head], sizeof(TreeNode));
    if (queuePtr->head == queuePtr->rear) {
        queuePtr->rear = EMPTY_POS;
        queuePtr->head = EMPTY_POS;
    }
    queuePtr->head = (queuePtr->head + 1) % queuePtr->capacity;

    queuePtr->curSize--;
    return ;
}

bool IsFullMyQueue(MyQueue_T* queuePtr) {
    if (queuePtr->curSize == queuePtr->capacity) {
        return true;
    }
    return false;
}

bool IsEmptyMyQueue(MyQueue_T* queuePtr) {
    if (queuePtr->curSize == 0) {
        return true;
    }
    return false;
}

void FreeMyQueue(MyQueue_T* queuePtr) {
    free(queuePtr->data);
    free(queuePtr);
    return ;
}

int minDepth(struct TreeNode* root){
    if (root == NULL) {
        return 0;
    }

    MyQueue_T* myQueuePtr = InitMyQueue(MAX_TREE_NUM);
    EnMyQueue(myQueuePtr, root);
    int depth = 1;

    while (!IsEmptyMyQueue(myQueuePtr)) {
        int curQueueSize = myQueuePtr->curSize;

        TreeNode curTreeNode;
        for (int i = 0; i < curQueueSize; i++) {
            DeMyQueue(myQueuePtr, &curTreeNode);

            if (curTreeNode.left == NULL && curTreeNode.right == NULL) {
                FreeMyQueue(myQueuePtr);
                return depth;
            }

            if (curTreeNode.left != NULL) {
                EnMyQueue(myQueuePtr, curTreeNode.left);
            }

            if (curTreeNode.right != NULL) {
                EnMyQueue(myQueuePtr, curTreeNode.right);
            }
        }
        depth++;
    }
    return depth;
}

#endif