//
// Created by 破忆断回 on 2021/9/26.
//

#ifndef SSH_ARRAYALGO_H
#define SSH_ARRAYALGO_H

#include <iostream>


#include "folly/FBVector.h"
#include "folly/String.h"
#include "folly/Format.h"
#include "GreedyAlgo.h"
#include <string_view>

using folly::fbstring;
using folly::fbvector;
using folly::Optional;
using fmt::format;

using std::addressof;
using std::cout;

//定义一个类 ,用于描述日期


class ArrayAlgo {
public:
    //Consistent Hashing
    // 一致性函数

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

    ///????????????????????????????????????????????
    // 这是什么 jb写法?
    static constexpr unsigned int (max)() {
        return static_cast<unsigned int>(-1);
    }
};


#endif //SSH_ARRAYALGO_H
