Question List (in C)
----------------------------

## 前缀和 && Hash
128. 最长连续序列 [ans](./include/prefix_sum_hash/longest_consecutive_seq.h)[medium]
146. LRU 缓存 [ans](./include/prefix_sum_hash/lru_cache.h)[medium]
523. 连续的子数组和 [ans](./include/array/cont_subarray_sum.h)[medium]
560. 和为 K 的子数组 [ans](./include/array/sub_sum_k.h)[medium]
974. 和可被 K 整除的子数组 [ans](./include/array/sub_sum_divisible.h)[medium]
1590. 使数组和能被P整除 [ans](./include/prefix_sum/make_sum_divisible_by_p.h)[medium]

## 贪心 && DP
55. 跳跃游戏 [ans](./src/greedy_dp_q/jump_game.c)[medium]
70. 爬楼梯 [ans](./src/greedy_dp_q/)[easy]
121. 买卖股票的最佳时机 [ans](./src/greedy_dp_q/max_pro.c)[easy]
122. 买卖股票的最佳时机 II [ans](./include/array/best_time_sell_stock_2.h)[medium]
413. 等差数列划分 [ans](./include/array/arith_slices.h)[medium]
1094. 拼车 [ans](./include/array/car_pooling.h)[medium]
1109. 航班预订统计 [ans](./include/array/flight_bookings.h)[medium]

## 滑动窗口
3. 无重复字符的最长子串 [ans](./include/sliding_win/long_sub_str_wo_repeat.h)[medium]
5. 最长回文子串 [ans](./include/sliding_win/long_palind_sub_str.h)[medium]
209. 长度最小的子数组 [ans](./include/sliding_win/min_size_sub_array.h)[medium]
438. 找到字符串中所有字母异位词 [ans](./include/sliding_win/find_anagrams.h)[medium]
1004. 最大连续1的个数 III [ans](./include/sliding_win/max_con_ones_3.h)[medium]
1208. 尽可能使字符串相等 [ans](./include/sliding_win/get_equal_sub_str.h)[medium]

## 排序
56. 合并区间 [ans](./include/sorting/merge_intervals.h)[medium]
406. 根据身高重建队列 [ans](./include/sorting/queue_rebuild_by_height.h)[medium]
853. 车队 [ans](./include/sorting/car_fleet.h)[medium]

## 字符串
6. N字形变换 [ans](./include/str/zigzag_conversion.h)[medium]
8. 字符串转换整数 (atoi) [ans](./include/str/my_atoi.h)[medium]
43. 字符串相乘 [ans](./include/str/multiply_str.h)[medium]
165. 比较版本号 [ans](./include/str/compare_version.h)[medium]
1071. 字符串的最大公因子 [ans](./include/str/greatest_common_divisor_str.h)[easy]

## 回溯
17. 电话号码的字母组合 [ans](./include/backtrack/letter_combine_of_phone_num.h)[medium]
22. 括号生成 [ans](./include/backtrack/gen_parenth.h)[medium]
37. 解数独 [ans](./include/backtrack/solve_sudoku.h)[hard]
46. 全排列 [ans](./include/backtrack/permutations.h)[medium]
60. 排列序列 [ans](./include/backtrack/permutation_seq.h)[hard]
77. 组合 [ans](./include/backtrack/combine.h)[medium]
78. 子集 [ans](./include/backtrack/subsets.h)[medium]
113. 路径总和 II [ans](./include/backtrack/path_sum_2.h)[medium]

## 栈
678. 有效的括号字符串 [ans](./src/stack_q/valid_paren_str.c)[medium]

## 单调栈
84. 柱状图中最大的矩形 [ans](./include/array/largest_rectangle_his.h)[medium]
739. 每日温度 [ans](./include/array/daily_temperature.h)[medium]
962. 最大宽度坡 [ans](./include/array/max_width_ramp.h)[medium]

## 双指针
11. 盛最多水的容器 [ans](./include/two_pointer/container_with_most_water.h)[medium]
876. 链表的中间结点 [ans](./include/two_pointer/)[easy]

## 数学
1. 两数之和 [ans](./src/math_q/two_sum.c)[easy]
2. 两数相加 [ans](./include/math/add_two_numbers.h)[medium]
4. 寻找两个正序数组的中位数 [ans](./include/math/median_two_sorted_array.h)[hard]
7. 整数反转 [ans](./include/math/reverse_integer.h)[medium]
9. 回文数 [ans](./src/math_q/palindrome_num.c)[easy]
66. 加一 [ans](./src/math_q/plus_one.c)[easy]
13. 罗马数字转整数 [ans](./src/math/roman_2_int.c)[easy]
1089. 复写零 [ans](./include/math/duplicate_zeros.h)[easy]

## BFS
102. 二叉树的层序遍历 [ans](./src/bfs_q/level_order_trav.c)[medium]
111. 二叉树的最小深度 [ans](./src/bfs_q/min_depth_bin_tree.c)[easy]
127. 单词接龙 [ans](./include/bfs/word_ladder.h)[hard]
139. 单词拆分 [ans](./include/bfs/word_break.h)[medium]
815. 公交路线 [ans](./include/bfs/bus_routes.h)[hard]
934. 最短的桥 [ans](./include/bfs/shortest_bridge.h)[medium]

## 系统应用
146. LRU 缓存 [ans](./src/app_sys_q/lru_cache.c)[medium]
215. 数组中的第K个最大元素 [ans](./src/app_sys_q/kth_largest.c)[medium]
347. 前K个高频元素 [ans](./src/app_sys_q/top_k_freq.c)[medium]
295. 数据流的中位数 [ans](./src/app_sys_q/find_median_from_stream.c)[hard]
    - (MinHeap + MaxHeap)找中位数