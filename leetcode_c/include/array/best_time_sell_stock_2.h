/**
 * @file best_time_sell_stock_2.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-ii/
 * @version 0.1
 * @date 2023-02-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef LEETCODE_BEST_TIME_SELL_STOCK_2_H
#define LEETCODE_BEST_TIME_SELL_STOCK_2_H

#include "../const.h"

int maxProfit(int* prices, int pricesSize){
    int curProfit = 0;
    int curPrice = prices[0];

    for (int i = 1; i < pricesSize; i++) {
        if (curPrice < prices[i]) {
            curProfit += prices[i] - curPrice;
        }

        curPrice = prices[i];
    }
    return curProfit;
}

#endif