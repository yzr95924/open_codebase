/**
 * @file max_pro.c
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/best-time-to-buy-and-sell-stock/
 * @version 0.1
 * @date 2023-07-21
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../../include/greedy_dp_q.h"

#define MIN(a,b) (((a) <= (b)) ? (a) : (b))
#define MAX(a,b) (((a) >= (b)) ? (a) : (b))

int maxProfit(int* prices, int pricesSize)
{
    int minCost = prices[0];
    int maxPro = 0;
    for (int idx = 1; idx < pricesSize; idx++) {
        minCost = MIN(minCost, prices[idx]);
        maxPro = MAX(prices[idx] - minCost, maxPro);
    }

    return maxPro;
}