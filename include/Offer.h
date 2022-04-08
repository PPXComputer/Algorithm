//
// Created by Administrator on 2022/3/21.
//

#ifndef SSH_OFFER_H
#define SSH_OFFER_H

#include <cassert>

struct Offer {
public:
    static int divide();

    static int addBinary();

    static void singleNum();

    static void threeSum();

    static void threeSumFirstAnswer(std::vector<int> &data);

    static void threeSumSecondAnswer(std::vector<int> &data);

    static void minSubArrayLen();

    static void numSubarrayProductLessThanK();

    static void findMaxLengthWithSameCount();

    static int pivotIndex();

    static int NumMatrix();

    static void checkInclusion();

    static int lengthOfLongestSubstring(std::string &s);

    static int countSubstrings();

    static void removeNthFromEnd() {
        const std::unique_ptr<ListNode> &ptr = Offer::ListNode::new_list(10);
        auto root = ptr.get();
        ListNode::printAll(root);
        auto a = ListNode(0, root);
        auto dummy = std::addressof(a);
        int n = 2;

        auto first = dummy;
        auto second = dummy;
        while (n-- != 0) {
            second = second->next;
        }
        while (second != nullptr) {
            second = second->next;
            first = first->next;
        }
        first->next = first->next->next;
        dummy->next;
    }

private:
    struct ListNode {
        ListNode() : val(0), next{nullptr} {}

        explicit ListNode(int x) : val(x), next(nullptr) {}

        explicit ListNode(int x, ListNode *raw_ptr) : val(x), next(raw_ptr) {}

        ListNode(const ListNode &) = delete;

        ListNode &operator=(const ListNode &) = delete;

        ListNode *next;
        int val;


        static void printAll(ListNode *cur) {
            std::cout << "list:[";
            while (cur != nullptr) {
                std::cout << cur->val << ' ';
                cur = cur->next;
            }
            std::cout << "]\n";
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

        ~ListNode() {

            for (auto data: node) {
                delete data;
            }
        }

    private:

        std::vector<ListNode *> node = {};
    };
};


#endif //SSH_OFFER_H
