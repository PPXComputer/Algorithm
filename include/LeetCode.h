#pragma once

#include <string>
#include <vector>
#include<memory>
#include <cassert>

using std::vector;

class LeetCode {
public:

    //746. 使用最小花费爬楼梯
    static void minCostClimbingStairs();

    //844. 比较含退格的字符串
    static void backspaceCompare();

    //986. 区间列表的交集
    static void intervalIntersection();


    // 438. 找到字符串中所有字母异位词
    static void findAnagrams();

    //713. 乘积小于K的子数组
    static void numSubarrayProductLessThanK();

    //509 斐波那契 数
    static void fib();

    //1137 1137. 第 N 个泰波那契数
    static void tribonacci();

    //797. 所有可能的路径
    static void allPathsSourceTarget();

    //494. 目标和
    static void findTargetSumWays();

    //430. 扁平化多级双向链表
    static void flattenList();

private:

    struct ListNode {
        ListNode() : val(0), next{nullptr} {}

        explicit ListNode(int x) : val(x), next(nullptr) {}

        ListNode(int x, ListNode *raw_ptr) : val(x), next(raw_ptr) {}

        ListNode(const ListNode &) = delete;

        ListNode *next;
        int val;


        static std::unique_ptr<ListNode> new_list(size_t length) {
            assert(length != 0);
            auto result = std::make_unique<ListNode>(0);
            result->node.reserve(length - 1);
            auto root = result.get();
            for (int i = 1; i < length; i++) {
                root->next = new ListNode(i);
                root = root->next;
                result->node.emplace_back(root);
            }
            return result;
        }

        static std::unique_ptr<ListNode> new_list(const std::vector<int> &data) {
            if (data.empty())return nullptr;
            auto result = std::make_unique<ListNode>(data[0]);
            auto root = result.get();
            result->node.reserve(data.size() - 1);
            size_t size = data.size();
            for (size_t i = 1; i < size; i++) {
                root->next = new ListNode(data[i]);
                root = root->next;
                result->node.emplace_back(root);
            }
            return result;
        }

        ~ListNode() {

            for (auto data: node) {
                delete data;
            }
        }

    private:

        std::vector<ListNode *> node = {};
    };


};
