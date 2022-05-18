#pragma once

#include <string>
#include <vector>
#include<memory>
#include <cassert>

using std::vector;

class LeetCode {
public:

    //746. ʹ����С������¥��
    static void minCostClimbingStairs();

    //844. �ȽϺ��˸���ַ���
    static void backspaceCompare();

    //986. �����б�Ľ���
    static void intervalIntersection();


    // 438. �ҵ��ַ�����������ĸ��λ��
    static void findAnagrams();

    //713. �˻�С��K��������
    static void numSubarrayProductLessThanK();

    //509 쳲����� ��
    static void fib();

    //1137 1137. �� N ��̩��������
    static void tribonacci();

    //797. ���п��ܵ�·��
    static void allPathsSourceTarget();

    //494. Ŀ���
    static void findTargetSumWays();

    //430. ��ƽ���༶˫������
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
