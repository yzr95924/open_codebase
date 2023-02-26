/**
 * @file middle_linked_list.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/middle-of-the-linked-list/
 * @version 0.1
 * @date 2023-02-26
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef LEETCODE_MIDDLE_LINKED_LIST_H
#define LEETCODE_MIDDLE_LINKED_LIST_H

#include "../../include/const.h"

struct ListNode {
    int val;
    struct ListNode *next;
};

typedef struct ListNode ListNode;

struct ListNode* middleNode(struct ListNode* head){
    ListNode* fastPtr = head;
    ListNode* slowPtr = head;

    while (fastPtr != NULL && fastPtr->next != NULL) {
        fastPtr = fastPtr->next->next;
        slowPtr = slowPtr->next;
    }

    return slowPtr;
}

#endif