/**
 * @file car_pooling.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/car-pooling/
 * @version 0.1
 * @date 2023-02-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef LEETCODE_CAR_POOLING_H
#define LEETCODE_CAR_POOLING_H

#include "../const.h"

void UpdateTripMap(int* tripMap, int numPassenger, int startPos, int endPos) {
    tripMap[startPos] += numPassenger;
    tripMap[endPos] -= numPassenger;
    return ;
}

bool carPooling(int** trips, int tripsSize, int* tripsColSize, int capacity){
    const int maxRangeSize = 1001;
    int* tripMap = (int*)calloc(maxRangeSize, sizeof(int));

    for (int i = 0; i < tripsSize; i++) {
        UpdateTripMap(tripMap, trips[i][0], trips[i][1], trips[i][2]);
        // printf("%d\n", tripMap[0]);
    }

    for (int i = 0; i < maxRangeSize; i++) {
        if (i > 0) {
            tripMap[i] += tripMap[i - 1];
        }
        if (tripMap[i] > capacity) {
            free(tripMap);
            return false;
        }
    }

    // for (int i = 0; i < maxRangeSize; i++) {
    //     printf("%d ", tripMap[i]);
    // }

    free(tripMap);

    return true;
}

#endif