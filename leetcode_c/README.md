Question List (in C)
----------------------------

## 前缀和 && Hash && Heap
- 49: 字母异位词分组 [ans](./src/hash_q/group_anagrams.c)[medium]
    - 字符串内部排序作为key + hashMap统计
- 128: 最长连续序列 [ans](./src/hash_q/long_con_seq.c)[medium]
    - hashMap数组去重 + 遍历x, x+1, x+2, ... + 检查 x-1是否存在，避免重复扫描
- 239: 滑动窗口最大值 [ans](./src/hash_q/max_slide_win.c)[hard]
    - MaxHeap: 插入右边的item + item (val, idx) + idx判断是否在win里面
- 523: 连续的子数组和 [ans](./include/array/cont_subarray_sum.h)[medium]
- 560: 和为 K 的子数组 [ans](./src/hash_q//subarr_sum_k.c)[medium]
    - 前缀和：O(n)遍历数组，计算前缀和，找到目标值，更新hash table
- 974: 和可被 K 整除的子数组 [ans](./include/array/sub_sum_divisible.h)[medium]
- 1590: 使数组和能被P整除 [ans](./include/prefix_sum/make_sum_divisible_by_p.h)[medium]

## 贪心 && DP
- 45: 跳跃游戏 II [ans](./src/greedy_dp_q/jump_game_2.c)[medium]
    - 贪心：统计当前最远可达距离，注意加步数的条件
- 53: 最大子数组和 [ans](./src/greedy_dp_q//max_subarr.c)[medium]
    - 贪心：当前和如果为负数的话，应该重新清零开始计算
- 55: 跳跃游戏 [ans](./src/greedy_dp_q/jump_game.c)[medium]
    - 同45，判断当前可达最远距离是否满足边界
- 70: 爬楼梯 [ans](./src/greedy_dp_q/climb_stair.c)[easy]
- 121: 买卖股票的最佳时机 [ans](./src/greedy_dp_q/max_pro.c)[easy]
- 122: 买卖股票的最佳时机 II [ans](./include/array/best_time_sell_stock_2.h)[medium]
- 413: 等差数列划分 [ans](./include/array/arith_slices.h)[medium]
- 763: 划分字母区间 [ans](./src/greedy_dp_q/partition_lab.c)[medium]
    - 统计每个字母出现的最后位置，然后同45, 55
- 1094: 拼车 [ans](./include/array/car_pooling.h)[medium]
- 1109: 航班预订统计 [ans](./include/array/flight_bookings.h)[medium]

## 滑动窗口 && 双指针
- 3: 无重复字符的最长子串 [ans](./src/slide_two_q//long_substr_wo_repeat.c)[medium]
    - 滑动窗口 + 字符串判断重复
- 5: 最长回文子串 [ans](./include/sliding_win/long_palind_sub_str.h)[medium]
- 11: 盛最多水的容器 [ans](./src/slide_two_q/container_with_water.c)[medium]
    - 双指针：从两端开始扫，哪端高度小，调整哪端
- 15: 三数之和 [ans](./src/slide_two_q/three_sum.c)[medium]
    - 双指针 + 排序 + 去重：相同元素要去重
- 42: 接雨水 [ans](./src/slide_two_q/trapping_rain.c)[hard]
    - 双指针：遍历每一列，计算其左边max、右边max，再计算面积，可以优化提前计算每一列左边和右边的max
- 76: 最小覆盖子串 [ans](./src/slide_two_q/min_win_substr.c)[hard]
    - 滑动窗口：用hashmap判断是否为子串
- 189: 轮转数组 [ans](./src/slide_two_q/rotate_arr.c)[medium]
    - 旋转数组：整体旋转一次 + 分别旋转两次 + 不使用额外的空间
- 209: 长度最小的子数组 [ans](./include/sliding_win/min_size_sub_array.h)[medium]
- 283: 移动零 [ans](./src/slide_two_q/move_zero.c)[easy]
    - 双指针：先移动非零，再填0
- 438: 找到字符串中所有字母异位词 [ans](./src/slide_two_q/find_anagrams.c)[medium]
    - 滑动窗口 + 判断是不是异位词
- 1004: 最大连续1的个数 III [ans](./include/sliding_win/max_con_ones_3.h)[medium]
- 1208: 尽可能使字符串相等 [ans](./include/sliding_win/get_equal_sub_str.h)[medium]

## 查找 & 排序
- 35: 搜索插入位置 [ans](./src/find_sort_q/search_insert_pos.c)[easy]
    - 二分查找
- 74: 搜索二维矩阵 [ans](./src/find_sort_q/search_2d_mat.c)[medium]
    - 两次二分查找
- 56: 合并区间 [ans](./src/find_sort_q/merge_intervals.c)[medium]
    - 先sort区间的leftBound，然后再遍历，看是否需要合并
- 406: 根据身高重建队列 [ans](./include/sorting/queue_rebuild_by_height.h)[medium]
- 853: 车队 [ans](./include/sorting/car_fleet.h)[medium]

## 字符串 && 数组
- 6: N字形变换 [ans](./include/str/zigzag_conversion.h)[medium]
- 8: 字符串转换整数 (atoi) [ans](./include/str/my_atoi.h)[medium]
- 43: 字符串相乘 [ans](./include/str/multiply_str.h)[medium]
- 165: 比较版本号 [ans](./include/str/compare_version.h)[medium]
- 1071: 字符串的最大公因子 [ans](./include/str/greatest_common_divisor_str.h)[easy]

## 回溯
- 17: 电话号码的字母组合 [ans](./include/backtrack/letter_combine_of_phone_num.h)[medium]
- 22: 括号生成 [ans](./include/backtrack/gen_parenth.h)[medium]
- 37: 解数独 [ans](./include/backtrack/solve_sudoku.h)[hard]
- 46: 全排列 [ans](./include/backtrack/permutations.h)[medium]
- 60: 排列序列 [ans](./include/backtrack/permutation_seq.h)[hard]
- 77: 组合 [ans](./include/backtrack/combine.h)[medium]
- 78: 子集 [ans](./include/backtrack/subsets.h)[medium]
- 113: 路径总和 II [ans](./include/backtrack/path_sum_2.h)[medium]

## 栈
- 20: 有效的括号 [ans](./src/stack_q/valid_paren.c)[easy]
    - 基本栈操作
- 84: 柱状图中最大的矩形 [ans](./src/stack_q/largest_rect_hist.c)[medium]
    - 单调栈：单调递增，统计左边，右边的最近小于的高度，注意边界值处理
- 155: 最小栈 [ans](./src/stack_q/min_stack.c)[medium]
    - 维护两个栈：realStack + minStack
- 394: 字符串解码 [ans](./src/stack_q/decode_str.c)[medium]
    - 基本栈操作 + 倒序遍历字符串
    - 数字栈 + 字符栈：逆波兰表达式
- 678: 有效的括号字符串 [ans](./src/stack_q/valid_paren_str.c)[medium]
    - 维护两个栈：* + ()
- 739: 每日温度 [ans](./src/stack_q/daily_temp.c)[medium]
    - 单调栈：单调递减
- 84: 柱状图中最大的矩形 [ans](./include/array/largest_rectangle_his.h)[medium]
- 962: 最大宽度坡 [ans](./include/array/max_width_ramp.h)[medium]

## 双指针
- 11: 盛最多水的容器 [ans](./include/two_pointer/container_with_most_water.h)[medium]
- 876: 链表的中间结点 [ans](./include/two_pointer/)[easy]

## 数学
- 1: 两数之和 [ans](./src/math_q/two_sum.c)[easy]
- 2: 两数相加 [ans](./include/math/add_two_numbers.h)[medium]
- 4: 寻找两个正序数组的中位数 [ans](./include/math/median_two_sorted_array.h)[hard]
- 7: 整数反转 [ans](./include/math/reverse_integer.h)[medium]
- 9: 回文数 [ans](./src/math_q/palindrome_num.c)[easy]
- 66: 加一 [ans](./src/math_q/plus_one.c)[easy]
- 13: 罗马数字转整数 [ans](./src/math/roman_2_int.c)[easy]
- 1089: 复写零 [ans](./include/math/duplicate_zeros.h)[easy]

## BFS
- 102: 二叉树的层序遍历 [ans](./src/bfs_q/level_order_trav.c)[medium]
- 111: 二叉树的最小深度 [ans](./src/bfs_q/min_depth_bin_tree.c)[easy]
- 127: 单词接龙 [ans](./include/bfs/word_ladder.h)[hard]
- 139: 单词拆分 [ans](./include/bfs/word_break.h)[medium]
- 815: 公交路线 [ans](./include/bfs/bus_routes.h)[hard]
- 934: 最短的桥 [ans](./include/bfs/shortest_bridge.h)[medium]

## 系统应用
- 146: LRU 缓存 [ans](./src/app_sys_q/lru_cache.c)[medium]
    - Map + LinkedList
- 215: 数组中的第K个最大元素 [ans](./src/app_sys_q/kth_largest.c)[medium]
- 347: 前K个高频元素 [ans](./src/app_sys_q/top_k_freq.c)[medium]
- 295: 数据流的中位数 [ans](./src/app_sys_q/find_median_from_stream.c)[hard]
    - (MinHeap + MaxHeap)找中位数