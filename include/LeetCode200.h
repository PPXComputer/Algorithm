#pragma once

#include <cassert>
#include <memory>
#include <vector>

class LeetCode200 {
public:
    static void medium_33();

    static void medium_34();

    //. 搜索二维矩阵
    static void medium_74();

    // 25  k 个一组翻转链表
    static void reverseKGroup();

    //162 寻找峰值
    static void findPeakElement();

    // 153 找到旋转数组的的最小值
    static void findMin();

    //198. 打家劫舍
    static void houseRobber();

    //11. 盛最多水的容器
    static void maxArea();

    //79. 单词搜索

    static void existInMesh();

    //82. 删除排序链表中的重复元素 II
    static void deleteDuplicatesFromList();

    //15. 三数之和
    static void three_num();

    //17. 电话号码的字母组合
    static void letterCombinations();

    //70. 爬楼梯
    static void climbStairs();

    //117. 填充每个节点的下一个右侧节点指针 II
    static void connectRight();

    //1091 二进制矩阵中的最短路径
    static void shortestPathBinaryMatrix();

    //130. 被围绕的区域
    static void solveRound();

    // 78子集
    static void subsets();

    //90. 子集 II
    static void otherSubSets();

    //39. 组合总和
    static void combinationSum();

    //797. 所有可能的路径
    static void allPathsSourceTarget();

    //22. 括号生成
    static void generateParenthesisByBrackets();

    // 打家劫舍2
    static void robOnStreet();


    static void jumpGame();

    //5. 最长回文子串
    static void longestPalindrome();
    // 178 最大数
    static void maxNum();

    //48 旋转图像
    static void rotateImage();
    static void groupAnagrams();
private:

    struct ListNode {
        ListNode() : val(0), next{nullptr} {}

        explicit ListNode(int x) : val(x), next(nullptr) {}

        ListNode(int x, ListNode *raw_ptr) : val(x), next(raw_ptr) {}

        ListNode(const ListNode &) = delete;

        ListNode *next;
        int val;


        ~ListNode() {

            for (auto data: node) {
                delete data;
            }
        }

        static std::unique_ptr<ListNode> new_list(size_t length) {
            assert(length != 0);
            auto result = std::make_unique<ListNode>(0);
            result->node.reserve(length - 1);
            auto root = result.get();
            for (size_t i = 1; i < length; i++) {
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

        std::vector<ListNode *> node = {};
    };


};