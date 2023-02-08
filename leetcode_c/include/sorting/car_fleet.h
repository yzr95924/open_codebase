/**
 * @file car_fleet.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/car-fleet/description/
 * @version 0.1
 * @date 2023-02-08
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef LEETCODE_CAR_FLEET_H
#define LEETCODE_CAR_FLEET_H

#include "../const.h"

typedef struct {
    int startPos;
    double costTime;
} Item_t;

static int CompFunc(const void* a, const void* b) {
    const Item_t* input1 = (Item_t*)a;
    const Item_t* input2 = (Item_t*)b;
    return (input2->startPos - input1->startPos); // descend 
}

int carFleet(int target, int* position, int positionSize, int* speed, int speedSize){
    Item_t* carVec = (Item_t*)calloc(positionSize, sizeof(Item_t));   

    if (positionSize == 0) {
        return 0;
    }

    for (int i = 0; i < positionSize; i++) {
        carVec[i].startPos = position[i];
        carVec[i].costTime = (double)(target - position[i]) / speed[i];
    }

    // sort carVec
    qsort(carVec, positionSize, sizeof(Item_t), CompFunc);

    int ret = 1;
    for (int i = 0; i < positionSize - 1; i++) {
        if (carVec[i].costTime < carVec[i + 1].costTime) {
            ret++;
        } else {
            carVec[i + 1].costTime = carVec[i].costTime;
        }
    }

    free(carVec);

    return ret;
}

#endif