/**
 * @file main.c
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief the main process
 * @version 0.1
 * @date 2023-06-11
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../../../common_include/my_log.h"
#include "../../include/app_sys_q.h"
#include "../../include/bfs_q.h"
#include "../../include/math_q.h"

#define MODULE_ID "LeetCodeMain"

int main(int argc, char* argv[]) {

    struct TreeNode root = { 0 };
    root.val = 3;
    struct TreeNode l1_9 = { 0 };
    l1_9.val = 9;
    struct TreeNode l1_20 = { 0 };
    l1_20.val = 20;
    struct TreeNode l2_15 = { 0 };
    l2_15.val = 15;
    struct TreeNode l2_7 = { 0 };
    l2_7.val = 7;

    root.left = &l1_9;
    root.right = &l1_20;
    l1_20.left = &l2_15;
    l1_20.right = &l2_7;

    int returnSize;
    int* returnVolume;
    levelOrder(&root, &returnSize, &returnVolume);

    // int input_1 = 1;
    // int *ptr = &input_1;
    // printf("ptr: %p\n", ptr);
    // printf("input_1: %d\n", input_1);

    // *ptr++;

    // printf("ptr: %p\n", ptr);
    // printf("input_1: %d\n", input_1);

    return 0;
}