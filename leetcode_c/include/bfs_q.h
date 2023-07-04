/**
 * @file bfs_q.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief the question set of BFS
 * @version 0.1
 * @date 2023-07-05
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef LEETCODE_C_BFS_Q_H
#define LEETCODE_C_BFS_Q_H

#include "../../common_include/c_include.h"

/**
 * @brief 111. Minimum Depth of Binary Tree
 * @cite https://leetcode.cn/problems/minimum-depth-of-binary-tree/
 *
 */
struct TreeNode {
     int val;
     struct TreeNode *left;
     struct TreeNode *right;
} TreeNode;
int minDepth(struct TreeNode *root);

#endif