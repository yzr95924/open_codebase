#ifndef LEETCODE_CAR_POOLING_H
#define LEETCODE_CAR_POOLING_H

#include "../const.h"

int g_tripMap[1001] = {0};

bool UpdateTripMap(int numPassenger, int startPos, int endPos, int capacity) {
    for (int i = startPos; i < endPos; i++) {
        g_tripMap[i] += numPassenger;
        if (g_tripMap[i] > capacity) {
            return false;
        }
    }
    return true;
}


bool carPooling(int** trips, int tripsSize, int* tripsColSize, int capacity){
    memset(g_tripMap, 0, sizeof(int) * 1001);
    for (int i = 0; i < tripsSize; i++) {
        if (!UpdateTripMap(trips[i][0], trips[i][1], trips[i][2], capacity)) {
            return false;
        }
    }

    return true;
}

#endif