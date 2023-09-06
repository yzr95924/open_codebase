/**
 * @file slide_two_q.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief the question set of sliding window and two pointer
 * @version 0.1
 * @date 2023-08-10
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef LEETCODE_C_SLIDE_TWO_Q_H
#define LEETCODE_C_SLIDE_TWO_Q_H

#include "../../common_include/c_include.h"

/**
 * @brief 3. 无重复字符的最长子串
 * @cite https://leetcode.cn/problems/longest-substring-without-repeating-characters
 *
 */
int lengthOfLongestSubstring(char * s);

/**
 * @brief 11. 盛最多水的容器
 * @cite https://leetcode.cn/problems/container-with-most-water
 *
 */
int maxArea(int* height, int heightSize);

/**
 * @brief 15. 三数之和
 * @cite https://leetcode.cn/problems/3sum
 *
 */
int** threeSum(int* nums, int numsSize, int* returnSize, int** returnColumnSizes);

/**
 * @brief 42. 接雨水
 * @cite https://leetcode.cn/problems/trapping-rain-water/
 *
 */
int trap(int* height, int heightSize);

/**
 * @brief 76. 最小覆盖子串
 * @cite https://leetcode.cn/problems/minimum-window-substring
 *
 */
char * minWindow(char * s, char * t);

/**
 * @brief 189. 轮转数组
 * @cite https://leetcode.cn/problems/rotate-array
 *
 */
void rotate(int* nums, int numsSize, int k);

/**
 * @brief 283. 移动零
 * @cite https://leetcode.cn/problems/move-zeroes
 *
 */
void moveZeroes(int* nums, int numsSize);

/**
 * @brief 438. 找到字符串中所有字母异位词
 * @cite https://leetcode.cn/problems/find-all-anagrams-in-a-string
 *
 */
int* findAnagrams(char * s, char * p, int* returnSize);

#endif
