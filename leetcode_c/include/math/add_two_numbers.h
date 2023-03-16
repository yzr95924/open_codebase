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
    uint64_t carry = 0;
    ListNode* curl1Node = l1;
    ListNode* curl2Node = l2;

    ListNode* retHead = NULL;
    ListNode* tailNodePtr = NULL;
    while (curl1Node != NULL || curl2Node != NULL) {
        if (curl1Node != NULL) {
            l1Val = curl1Node->val;
            curl1Node = curl1Node->next;
        } else {
            l1Val = 0;
        }

        if (curl2Node != NULL) {
            l2Val = curl2Node->val;
            curl2Node = curl2Node->next;
        } else {
            l2Val = 0;
        }

        uint64_t newVal;
        newVal = l1Val + l2Val + carry;
        if (newVal > 9) {
            newVal -= 10;
            carry = 1;
        } else {
            carry = 0;
        }

        if (retHead == NULL) {
            tailNodePtr = (ListNode*)malloc(sizeof(ListNode));
            tailNodePtr->val = newVal;
            tailNodePtr->next = NULL;
            retHead = tailNodePtr;
        } else {
            tailNodePtr->next = (ListNode*)malloc(sizeof(ListNode));
            tailNodePtr->next->val = newVal;
            tailNodePtr = tailNodePtr->next;
            tailNodePtr->next = NULL;
        }
    }

    if (carry == 1) {
        tailNodePtr->next = (ListNode*)malloc(sizeof(ListNode));
        tailNodePtr->next->val = 1;
        tailNodePtr = tailNodePtr->next;
        tailNodePtr->next = NULL;
    }

    return retHead;
}

#endif