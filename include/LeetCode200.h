#pragma once

#include <cassert>
#include <memory>
#include <vector>

class LeetCode200 {
public:
    static void medium_33();

    static void medium_34();

    //. ������ά����
    static void medium_74();

    // 25  k ��һ�鷭ת����
    static void reverseKGroup();

    //162 Ѱ�ҷ�ֵ
    static void findPeakElement();

    // 153 �ҵ���ת����ĵ���Сֵ
    static void findMin();

    //198. ��ҽ���
    static void houseRobber();

    //11. ʢ���ˮ������
    static void maxArea();

    //79. ��������

    static void existInMesh();

    //82. ɾ�����������е��ظ�Ԫ�� II
    static void deleteDuplicatesFromList();

    //15. ����֮��
    static void three_num();

    //17. �绰�������ĸ���
    static void letterCombinations();

    //70. ��¥��
    static void climbStairs();

    //117. ���ÿ���ڵ����һ���Ҳ�ڵ�ָ�� II
    static void connectRight();

    //1091 �����ƾ����е����·��
    static void shortestPathBinaryMatrix();

    //130. ��Χ�Ƶ�����
    static void solveRound();

    // 78�Ӽ�
    static void subsets();

    //90. �Ӽ� II
    static void otherSubSets();

    //39. ����ܺ�
    static void combinationSum();

    //797. ���п��ܵ�·��
    static void allPathsSourceTarget();

    //22. ��������
    static void generateParenthesisByBrackets();

    // ��ҽ���2
    static void robOnStreet();


    static void jumpGame();

    //5. ������Ӵ�
    static void longestPalindrome();
    // 178 �����
    static void maxNum();
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