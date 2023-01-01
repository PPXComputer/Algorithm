//
// Created by 破忆断回 on 2021/9/26.
//

#ifndef ARRAYALGO_H
#define ARRAYALGO_H

#include <vector>

// 定义一个类 ,用于描述日期



class ArrayAlgo {
 public:
  // Consistent Hashing
  //  一致性函数

  static void change_position();

  static void huffman_tree();

  static void long_increase_sub_array();

  static void standard_str();

  static void data_array();

  static void not_exists_num();

  static void coin_change();

  static void xor_max_range();

  static void change_array_data();

  static void find_top_k();

  static void JosephProblem();

  static void longestTotalArray();

  static void findKthBit();

  static void salesRange();

  static void binarySearch();

  // LeetCode 870
  static void advantageCount();

  // leetcode 875
  static void minEatingSpeed();

  // leetcode 1011
  static void shipWithinDays();

  // leetcode 528
  static void pickIndex();

  // leetcode 209
  static void minSubArrayLen(int target, std::vector<int> &nums);

  // leetcode 219
  static bool containsNearbyDuplicate();

  // 2516
  static void takeCharacters();
  ///????????????????????????????????????????????
  // 这是什么 jb写法?
  static constexpr unsigned int(max)() { return static_cast<unsigned int>(-1); }
};

#endif  // ARRAYALGO_H
