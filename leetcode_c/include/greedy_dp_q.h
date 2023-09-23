/**
 * @file greedy_dp_q.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief greedy algo and dp question
 * @version 0.1
 * @date 2023-07-21
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef LEETCODE_C_GREEDY_DP_Q_H
#define LEETCODE_C_GREEDY_DP_Q_H

#include "../../common_include/c_include.h"

/**
 * @brief 121. 买卖股票的最佳时机
 * @cite https://leetcode.cn/problems/best-time-to-buy-and-sell-stock/
 *
 */
int maxProfit_121(int* prices, int pricesSize);

/**
 * @brief 45. 跳跃游戏 II
 * @cite https://leetcode.cn/problems/jump-game-ii/
 *
 */
int jump_45(int* nums, int numsSize);

/**
 * @brief 53. 最大子数组和
 * @cite https://leetcode.cn/problems/maximum-subarray/
 *
 */
int maxSubArray_53(int* nums, int numsSize);

/**
 * @brief 55. 跳跃游戏
 * @cite https://leetcode.cn/problems/jump-game/
 *
 */
bool canJump_55(int* nums, int numsSize);

/**
 * @brief 70. 爬楼梯
 * @cite https://leetcode.cn/problems/climbing-stairs
 *
 */
int climbStairs_70(int n);

/**
 * @brief 118. 杨辉三角
 * @cite https://leetcode.cn/problems/pascals-triangle
 *
 */
int** generate_118(int numRows, int* returnSize, int** returnColumnSizes);

/**
 * @brief 763. 划分字母区间
 * @cite https://leetcode.cn/problems/partition-labels/
 *
 */
int* partitionLabels_763(char * s, int* returnSize);

#endif
