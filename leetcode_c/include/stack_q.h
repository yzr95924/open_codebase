/**
 * @file stack_q.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief the question set of stack
 * @version 0.1
 * @date 2023-07-10
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef LEETCODE_C_STACK_Q_H
#define LEETCODE_C_STACK_Q_H

#include "../../common_include/c_include.h"

/**
 * @brief 20. 有效的括号
 * @cite https://leetcode.cn/problems/valid-parentheses/
 *
 */
bool isValid(char * s);

/**
 * @brief 84. 柱状图中最大的矩形
 * @cite https://leetcode.cn/problems/largest-rectangle-in-histogram
 *
 */
int largestRectangleArea(int* heights, int heightsSize);

/**
 * @brief 155. 最小栈
 * @cite https://leetcode.cn/problems/min-stack/
 *
 */
typedef struct {
    void *realStack;
    void *minStack;
} MinStack;
MinStack* minStackCreate();
void minStackPush(MinStack* obj, int val);
void minStackPop(MinStack* obj);
int minStackTop(MinStack* obj);
int minStackGetMin(MinStack* obj);
void minStackFree(MinStack* obj);

/**
 * @brief 394. 字符串解码
 * @cite https://leetcode.cn/problems/decode-string/
 *
 */
char * decodeString(char * s);

/**
 * @brief 678. 有效的括号字符串
 * @cite https://leetcode.cn/problems/valid-parenthesis-string/
 *
 */
bool checkValidString(char * s);

/**
 * @brief 739. 每日温度
 * @cite https://leetcode.cn/problems/daily-temperatures
 *
 */
int* dailyTemperatures(int* temperatures, int temperaturesSize, int* returnSize);

#endif
