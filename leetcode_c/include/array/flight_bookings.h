#ifndef LEETCODE_FLIGHT_BOOKINGS_H
#define LEETCODE_FLIGHT_BOOKINGS_H

#include "../const.h"

int* corpFlightBookings(int** bookings, int bookingsSize, int* bookingsColSize, int n, int* returnSize) {
    int* nums = (int*)calloc(n, sizeof(int));
    *returnSize = n;
    for (int i = 0; i < bookingsSize; i++) {
        // answer[i] --> i+1 station
        nums[bookings[i][0] - 1] += bookings[i][2];
        if (bookings[i][1] < n) {
            nums[bookings[i][1]] -= bookings[i][2];
        }
    }
    for (int i = 1; i < n; i++) {
        nums[i] += nums[i - 1];
    }
    return nums;
}

#endif