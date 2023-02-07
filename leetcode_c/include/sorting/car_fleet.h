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
#include "../third/utarray.h"

typedef struct {
    int startPos;
    double costTime;
} Item_t;

int CompFunc(const void* a, const void* b) {
    const Item_t* input1 = (Item_t*)a;
    const Item_t* input2 = (Item_t*)b;
    return (input2->startPos - input1->startPos); // descend 
}

UT_icd itemICD = {sizeof(Item_t), NULL, NULL, NULL};

int carFleet(int target, int* position, int positionSize, int* speed, int speedSize){
    UT_array* carVec;
    utarray_new(carVec, &itemICD);
    Item_t tmpItem;

    for (int i = 0; i < positionSize; i++) {
        tmpItem.startPos = position[i];
        tmpItem.costTime = (double)(target - position[i]) / speed[i];
        utarray_push_back(carVec, &tmpItem);
    }

    // sort carVec
    utarray_sort(carVec, CompFunc);

    Item_t* tmpPtr = NULL;
    while ((tmpPtr = (Item_t*)utarray_next(carVec, tmpPtr))) {
        printf("%d, %lf\n", tmpPtr->startPos, tmpPtr->costTime);
    }

    utarray_free(carVec);

    return 0;
}

#endif