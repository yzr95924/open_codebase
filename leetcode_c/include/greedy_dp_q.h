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
int maxProfit(int* prices, int pricesSize);

/**
 * @brief 45. 跳跃游戏 II
 * @cite https://leetcode.cn/problems/jump-game-ii/
 *
 */
int jump(int* nums, int numsSize);

/**
 * @brief 55. 跳跃游戏
 * @cite https://leetcode.cn/problems/jump-game/
 *
 */
bool canJump(int* nums, int numsSize);

/**
 * @brief 70. 爬楼梯
 * @cite https://leetcode.cn/problems/climbing-stairs
 *
 */
int climbStairs(int n);

/**
 * @brief 763. 划分字母区间
 * @cite https://leetcode.cn/problems/partition-labels/
 *
 */
int* partitionLabels(char * s, int* returnSize);

#endif
