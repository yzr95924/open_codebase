/**
 * @file add_two_numbers.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/add-two-numbers/description/
 * @version 0.1
 * @date 2023-03-15
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef LEETCODE_ADD_TWO_NUMBERS_H
#define LEETCODE_ADD_TWO_NUMBERS_H

#include "../const.h"

struct ListNode {
    int val;
    struct ListNode *next;
};

typedef struct ListNode ListNode;

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2)
{
    uint64_t l1Val = 0;
    uint64_t l2Val = 0;
    ListNode* curNode = NULL;
    uint64_t weightCnt = 1;

    // iterate l1
    curNode = l1;
    while (curNode != NULL) {
        l1Val += (curNode->val * weightCnt);
        curNode = curNode->next;
        weightCnt *= 10;
    }

    // iterate l2
    curNode = l2;
    weightCnt = 1;
    while (curNode != NULL) {
        l2Val += (curNode->val * weightCnt);
        curNode = curNode->next;
        weightCnt *= 10;
    }

    ListNode* retHead = NULL;
    uint64_t totalSum = l1Val + l2Val;

    if (totalSum == 0) {
        retHead = (ListNode*)malloc(sizeof(ListNode));
        retHead->val = 0;
        retHead->next = NULL;
        return retHead;
    }

    weightCnt = 10;
    // covert to output
    retHead = NULL;
    ListNode* tailPtr = NULL;
    while (totalSum != 0) {
        if (retHead == NULL) {
            tailPtr = (ListNode*)malloc(sizeof(ListNode));
            tailPtr->val = totalSum % weightCnt;
            tailPtr->next = NULL;
            retHead = tailPtr;
            printf("%d\n", tailPtr->val);
        } else {
            tailPtr->next = (ListNode*)malloc(sizeof(ListNode));
            tailPtr->next->val = totalSum % weightCnt;
            printf("%d\n", tailPtr->next->val);
            tailPtr = tailPtr->next;
        }
        totalSum /= 10;
    }

    return retHead;
}

#endif