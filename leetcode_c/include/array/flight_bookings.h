/**
 * @file flight_bookings.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/corporate-flight-bookings/
 * @version 0.1
 * @date 2023-02-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef LEETCODE_FLIGHT_BOOKINGS_H
#define LEETCODE_FLIGHT_BOOKINGS_H

#include "../const.h"

int* corpFlightBookings(int** bookings, int bookingsSize, int* bookingsColSize, int n, int* returnSize){
    int* answer = (int*)calloc(n + 1, sizeof(int));
    *returnSize = n;

    for (int i = 0; i < bookingsSize; i++) {
        if (bookings[i][0] <= n) {
            answer[bookings[i][0]] += bookings[i][2];
        }
        if (bookings[i][1] < n) {
            answer[bookings[i][1] + 1] -= bookings[i][2];
        }
    }

    for (int i = 2; i <= n; i++) {
        answer[i] += answer[i - 1];
    }    

    return &answer[1];
}

#endif