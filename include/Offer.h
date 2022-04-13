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

    static void removeNthFromEnd();

    // 二叉树的最大路径和
    static void maxPathSum();

private:
    struct TreeNode {
        TreeNode() : val(0), left{nullptr}, right{nullptr} {}

        explicit TreeNode(int x) : val(x), left{nullptr}, right{nullptr} {}


        TreeNode(const TreeNode &) = delete;

        TreeNode &operator=(const TreeNode &) = delete;

        TreeNode *left;
        TreeNode *right;
        int val;


        // decode tree node
        static std::unique_ptr<TreeNode> new_list(int length) {
            assert(length != 0);
            std::vector<int> data;
            data.reserve(length);
            for (int i = 0; i < length; ++i) {
                data.push_back(i + 1);
            }
            auto tree = TreeNode();
            std::vector<TreeNode *> container;
            decode(data, std::addressof(tree), 0, length - 1, true, container);
            std::unique_ptr<TreeNode> result{tree.left};
            tree.left->setNode(std::move(container));
            return result;
        }



        ~TreeNode() {

            for (auto data: node) {
                delete data;
            }
        }


        void setNode(std::vector<TreeNode *> &&container) {
            node = std::forward<decltype(container)>(container);
        }

    private:
         static void decode(const std::vector<int> &data, TreeNode *parent, int left, int right, bool isLeft,
                            std::vector<TreeNode *> &container) {
            if (left > right)return;
            int mid = (right + left) >> 1;
            if (isLeft) {
                parent->left = new TreeNode(data[mid]);
                container.emplace_back(parent->left);
                decode(data, parent->left, left, mid - 1, true, container);
                decode(data, parent->left, mid + 1, right, false, container);
            } else {
                parent->right = new TreeNode(data[mid]);
                container.emplace_back(parent->right);
                decode(data, parent->right, left, mid - 1, true, container);
                decode(data, parent->right, mid + 1, right, false, container);
            }
        }
        std::vector<TreeNode *> node = {};
    };

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
