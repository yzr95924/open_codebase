/**
 * @file path_sum_2.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/path-sum-ii/
 * @version 0.1
 * @date 2023-03-08
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef LEETCODE_PATH_SUM_2_H
#define LEETCODE_PATH_SUM_2_H

#include "../const.h"

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

#define MAX_ANS_NUM 2001

typedef struct TreeNode TreeNode;

typedef struct {
    int** retAns;
    int* returnColSizes;
    int cnt;
} AnsWrapper_T;

typedef struct {
    int* curPath;
    int curSize;
    int remainTarget;
} BackTrackState_T;

static void BackTrack(TreeNode* root, AnsWrapper_T* ansWrapper, BackTrackState_T* curState) {
    if (root->left == NULL && root->right == NULL) {
        if (curState->remainTarget == 0) {
            ansWrapper->retAns[ansWrapper->cnt] = (int*)calloc(curState->curSize, sizeof(int));
            memcpy(ansWrapper->retAns[ansWrapper->cnt], curState->curPath,
                curState->curSize * sizeof(int));
            ansWrapper->returnColSizes[ansWrapper->cnt] = curState->curSize;
            ansWrapper->cnt++;
            return;
        }
        return;
    }

    //
    if (root->left != NULL) {
        curState->curPath[curState->curSize] = root->left->val;
        curState->curSize++;
        curState->remainTarget -= root->left->val;
        BackTrack(root->left, ansWrapper, curState);
        curState->curSize--;
        curState->remainTarget += root->left->val;
    }

    if (root->right != NULL) {
        curState->curPath[curState->curSize] = root->right->val;
        curState->curSize++;
        curState->remainTarget -= root->right->val;
        BackTrack(root->right, ansWrapper, curState);
        curState->curSize--;
        curState->remainTarget += root->right->val;
    }

    return;
}

int** pathSum(struct TreeNode* root, int targetSum, int* returnSize, int** returnColumnSizes){
    AnsWrapper_T ansWrapper;
    ansWrapper.retAns = (int**)calloc(MAX_ANS_NUM, sizeof(int*));
    ansWrapper.returnColSizes = (int*)calloc(MAX_ANS_NUM, sizeof(int));
    ansWrapper.cnt = 0;

    BackTrackState_T curState;
    curState.curPath = (int*)calloc(MAX_ANS_NUM, sizeof(int));
    curState.curSize = 0;
    curState.remainTarget = targetSum;

    if (root != NULL) {
        curState.curPath[curState.curSize] = root->val;
        curState.curSize++;
        curState.remainTarget = targetSum - root->val;
        BackTrack(root, &ansWrapper, &curState);
    }

    *returnSize = ansWrapper.cnt;
    *returnColumnSizes = ansWrapper.returnColSizes;
    return ansWrapper.retAns;
}

#endif