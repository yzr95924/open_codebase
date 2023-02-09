/**
 * @file queue_rebuild_by_height.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/queue-reconstruction-by-height/description/
 * @version 0.1
 * @date 2023-02-09
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef QUEUE_REBUILD_BY_HEIGHT_H
#define QUEUE_REBUILD_BY_HEIGHT_H

#include "../const.h"

typedef struct {
    int* data;
    int capacity;
    int curSize;
} MyList_T;

MyList_T* InitMyList(int capacity) {
    MyList_T* listPtr = (MyList_T*)calloc(1, sizeof(MyList_T));
    listPtr->data = (int*)calloc(capacity, sizeof(int));
    listPtr->capacity = capacity;
    listPtr->curSize = 0;

    return listPtr;
}

bool IsFullMyList(MyList_T* listPtr) {
    if (listPtr->curSize == listPtr->capacity) {
        return true;
    }
    return false;
}

bool IsEmptyMyList(MyList_T* listPtr) {
    if (listPtr->curSize == 0) {
        return true;
    }
    return false;
}

void FreeMyList(MyList_T* listPtr) {
    free(listPtr->data);
    free(listPtr);
    return ;
}

void AppendMyList(MyList_T* listPtr, int inVal) {
    if (IsFullMyList(listPtr)) {
        printf("list is full.\n");
        return ;
    }
    listPtr->data[listPtr->curSize] = inVal;
    listPtr->curSize++;
    return ;
}

void InsertMyList(MyList_T* listPtr, int posIdx, int inVal) {
    if (IsFullMyList(listPtr)) {
        printf("list is full.\n");
    }

    if (posIdx > listPtr->curSize) {
        printf("insert pos is invalid, posIdx: %d, curSize%d\n",
            posIdx, listPtr->curSize);
    }

    for (int i = listPtr->curSize - 1; i >= posIdx; i--) {
        listPtr->data[i + 1] = listPtr->data[i];
    }

    listPtr->data[posIdx] = inVal;
    listPtr->curSize++;

    return ;
}

int FindMyList(MyList_T* listPtr, int inVal) {
    for (int i = 0; i < listPtr->curSize; i++) {
        if (listPtr->data[i] == inVal) {
            return i;
        }
    }

    return -1; // not found
}

bool DeleteMyList(MyList_T* listPtr, int posIdx, int* delVal) {
    if (IsEmptyMyList(listPtr)) {
        return false;
    }

    if (posIdx < 0 || posIdx >= listPtr->curSize) {
        return false;
    }

    *delVal = listPtr->data[posIdx];
    for (int i = posIdx; i < listPtr->curSize - 1; i++) {
        listPtr->data[i] = listPtr->data[i + 1];
    }

    listPtr->curSize--;
    return true;
}

void SortMyList(MyList_T* listPtr) {
    for (int i = 0; i < listPtr->curSize; i++) {
        for (int j = i + 1; j < listPtr->curSize; j++) {
            if (listPtr->data[i] > listPtr->data[j]) {
                int tmpVal = listPtr->data[i];
                listPtr->data[i] = listPtr->data[j];
                listPtr->data[j] = tmpVal;
            }
        }
    }
    return ;
}

int CmpFunc(const void* input1, const void* input2) {
    int* a = *(int**)input1;
    int* b = *(int**)input2;
    if (a[0] == b[0]) {
        return a[1] - b[1]; // ascend
    } else {
        return b[0] - a[0]; // descend
    }
}

int** reconstructQueue(int** people, int peopleSize, int* peopleColSize, int* returnSize, int** returnColumnSizes){
    qsort(people, peopleSize, sizeof(int*), CmpFunc);

    *returnColumnSizes = (int*)calloc(peopleSize, sizeof(int));
    for (int i = 0; i < peopleSize; i++) {
        (*returnColumnSizes)[i] = 2;
    }
    *returnSize = peopleSize;

    MyList_T* listPtr = InitMyList(peopleSize);

    for (int i = 0; i < peopleSize; i++) {
        InsertMyList(listPtr, people[i][1], i);
    }

    int** ret = (int**)calloc(peopleSize, sizeof(int*));
    for (int i = 0; i < listPtr->curSize; i++) {
        // printf("%d %d\n", people[listPtr->data[i]][0], people[listPtr->data[i]][1]);
        ret[i] = (int*)calloc(2, sizeof(int));
        ret[i][0] = people[listPtr->data[i]][0];
        ret[i][1] = people[listPtr->data[i]][1];
    }

    FreeMyList(listPtr);

    return ret;
}

#endif