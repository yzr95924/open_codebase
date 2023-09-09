/**
 * @file math_q.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief math question
 * @version 0.1
 * @date 2023-06-20
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef LEETCODE_C_MATH_Q_H
#define LEETCODE_C_MATH_Q_H

#include "../../common_include/c_include.h"

/**
 * @brief 1. Two Sum
 * @cite https://leetcode.cn/problems/two-sum/
 *
 */
int* twoSum(int* nums, int numsSize, int target, int* returnSize);

/**
 * @brief 9. Palindrome Number
 * @cite https://leetcode.cn/problems/palindrome-number/
 *
 */
bool isPalindrome(int x);

/**
 * @brief 41. 缺失的第一个正数
 * @cite https://leetcode.cn/problems/first-missing-positive
 *
 */
int firstMissingPositive(int* nums, int numsSize);

/**
 * @brief 48. 旋转图像
 * @cite https://leetcode.cn/problems/rotate-image
 *
 */
void rotate(int** matrix, int matrixSize, int* matrixColSize);

/**
 * @brief 54. 螺旋矩阵
 * @cite https://leetcode.cn/problems/spiral-matrix
 *
 */
int* spiralOrder(int** matrix, int matrixSize,
    int* matrixColSize, int* returnSize);

/**
 * @brief 66. Plus One
 * @cite https://leetcode.cn/problems/plus-one/
 *
 */
int* plusOne(int* digits, int digitsSize, int* returnSize);

/**
 * @brief 73. 矩阵置零
 * @cite https://leetcode.cn/problems/set-matrix-zeroes/
 *
 */
void setZeroes(int** matrix, int matrixSize, int* matrixColSize);

#endif