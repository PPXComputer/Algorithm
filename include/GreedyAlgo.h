
#ifndef SSH_GREEDYALGO_H
#define SSH_GREEDYALGO_H

#include <iostream>
#include <cassert>
#include <folly/FBString.h>
#include <random>
#include <array>
#include <folly/Format.h>
#include <folly/FBVector.h>
#include <memory>
#include <set>

using std::cout;
using std::make_unique;
using std::unique_ptr;
using std::array;
using std::addressof;
using folly::fbstring;
using folly::fbvector;
using FlexMatrix = folly::fbvector<folly::fbvector<int>>;

class GreedyAlgo {
public:
    static fbvector<int> geRandomArray
            (int len = 10, int min = 0, int max = 10, bool unique = false);

    static void CompareResult();

    static void concat_strings();

    // 切分铜板
    static void split_metal();

    template<typename T>
    static void get_last_two(folly::fbvector<int> &data, const T &min_heap);

    static void walk();

    static void aim_plus();

    static void chees();

    static void get_money();

    static void get_maximum_matrix();

    static void buy_apples();

    static void winner();

    static void k_step_pair();

    static void max_deep();

    static void long_bracket();

    static void matrix_multiplication();

    static void light_lame();

private:
    static bool isFirstOne(size_t rest);

    static int appleImpl(int money);

    //使用滑动窗口解法
    static int enum_rope_way2(const fbvector<int> &data, int rope_len);

    static int enum_rope(const fbvector<int> &data, const int rope_len);

    static int money_way3(const fbvector<int> &cost, int aim);

    static int money_way2(const fbvector<int> &cost, int aim);

    static int money_way1(int cur, int index, const fbvector<int> &cost);

    static void walkImpl(int x, int y, int cur, const fbvector<fbvector<int>> &matrix, int &result);

    static int walkImplWithNotVal(int x, int y, const fbvector<fbvector<int>> &matrix);

    // 备忘录递归
    static int walkMemo(int x, int y, const fbvector<fbvector<int>> &matrix,
                        fbvector<fbvector<int>> &memo);

    static bool aimPlusImpl(const fbvector<int> &datas, int index, int cur_sum, int aim);

    static int cheesImpl(int x, int y, const std::pair<int, int> &target, int step);
};


#endif //SSH_GREEDYALGO_H