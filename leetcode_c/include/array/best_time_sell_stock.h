/**
 * @file best_time_sell_stock.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/best-time-to-buy-and-sell-stock/
 * @version 0.1
 * @date 2023-02-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef LEETCODE_BEST_SELL_STOCK_H
#define LEETCODE_BEST_SELL_STOCK_H

#include "../const.h"

int maxProfit(int* prices, int pricesSize){
    int maxPro = 0;
    int minPrice = 0;

    // init 
    minPrice = prices[0];
    for (int i = 1; i < pricesSize; i++) {
        // check pro
        if (prices[i] < minPrice) {
            minPrice = prices[i];
        } else {
            // check profit
            int curPro = prices[i] - minPrice;
            maxPro = MAX(maxPro, curPro);
        }
        // printf("%d\n", maxPro);
    }

    return maxPro;
}

#endif