//
// Created by ppx on 2022/1/16.
//
#include <array>
#include<fmt/core.h>

#include "TreeAlgo.h"
#include <optional>

void TreeAlgo::cal_node_distance() {
    // ????????????
    const std::unique_ptr<TreeNode> &tree = create_tree();


    auto impl = [](TreeNode *root, auto &&self) -> std::pair<int, int> {
        // ??????? root ??????
        if (root == nullptr) {
            return {0, 0};//??????????
        } else {
            std::pair<int, int> left = self(root->left.get(), self);
            std::pair<int, int> right = self(root->right.get(), self);
            int cur_height = std::max(left.first, right.first) + 1;
            int result = std::max(std::max(left.second, right.second), cur_height);
            return {cur_height, result};
        }
    };
    fmt::print("impl(tree.get(), impl) {}", impl(tree.get(), impl).second);
}

std::unique_ptr<TreeNode> TreeAlgo::create_tree() {
    using std::make_unique;
    std::unique_ptr<TreeNode> root = make_unique<TreeNode>(0);
    root->left = make_unique<TreeNode>(1);
    root->left->left = make_unique<TreeNode>(3);
    root->right = make_unique<TreeNode>(2);
    root->right->left = make_unique<TreeNode>(4);
    root->right->right = make_unique<TreeNode>(5);
    root->right->right->right = make_unique<TreeNode>(6);

    return root;
}


void TreeAlgo::find_non_exist_num() {
    // ?????????? ???????? 2^16 ?????? 2^15
    // ???????????????д????count???
//        constexpr int length = 1 << 16;
//        std::array<int, length> data{};

}

void TreeAlgo::run() {
    TreeAlgo::cal_node_distance();
}

void TreeAlgo::find_most_search_subtree() {  // ????????????? ????????????

    std::unique_ptr<TreeNode> root = TreeAlgo::create_tree();

    auto fn = [](TreeNode *cur) {

        auto count = [](TreeNode *subTree, auto &&count) -> int {
            if (subTree != nullptr) {

                int left = count(subTree->left.get(), count);
                int right = count(subTree->right.get(), count);
                return left + right + 1;
            } else { return 0; }
        };

        auto search_sub_tree = [](TreeNode *data, auto &&search_sub_tree) -> bool {
            if (data == nullptr)return true;
            if (data->left != nullptr and (data->left->value > data->value))
                return false;
            if (data->right != nullptr and (data->right->value < data->value))
                return false;
            return search_sub_tree(data->left.get(), search_sub_tree) and
                   search_sub_tree(data->right.get(), search_sub_tree);
        };

        auto impl = [&](TreeNode *data, auto &&impl) -> int {
            if (search_sub_tree(data, search_sub_tree)) {
                return count(data, count);
            }
            if (data != nullptr) {
                int left = 0, right = 0;
                if (search_sub_tree(data->left.get(), search_sub_tree)) {
                    left = count(data->left.get(), count);
                }
                if (search_sub_tree(data->right.get(), search_sub_tree)) {
                    right = count(data->right.get(), count);
                }
                return std::max(left, right);
            }
        };
        return impl(cur, impl);
    };

    struct BstNodeResult {
        int min; // ???? ????С?? ?
        int max; // ???? ?????? ?
        Node *bstNodeHead;
        int height;
        bool isBst; //???????????? ???????????ж?
        BstNodeResult(int mi, int ma, Node *bst, int he, int isb) : min(mi),
                                                                    max(ma), bstNodeHead(bst), height(he), isBst(isb) {}
    };
    auto searchImpl = [](Node *root, auto &&searchImpl) -> std::optional<BstNodeResult> {
        if (root == nullptr) {
            return {};
        }

        std::optional<BstNodeResult> leftValue = searchImpl(root->left, searchImpl);
        std::optional<BstNodeResult> rightValue = searchImpl(root->right, searchImpl);

        BstNodeResult bstNodeResult = BstNodeResult(INT_MAX, INT_MIN, nullptr, 1, false);

        if (leftValue) {
            auto &left = leftValue.value();
            bstNodeResult.min = std::min(left.min, bstNodeResult.min);
            bstNodeResult.max = std::max(left.max, bstNodeResult.max);
        }
        if (rightValue) {
            auto &right = rightValue.value();
            bstNodeResult.min = std::min(right.min, bstNodeResult.min);
            bstNodeResult.max = std::max(right.max, bstNodeResult.max);
        }

        if (leftValue and rightValue) {
            auto &left = leftValue.value();
            auto &right = rightValue.value();
            if (left.isBst and right.isBst) {
                if (left.max <= right.min and root->value >= left.max
                    and root->value <= right.min) {
                    bstNodeResult.bstNodeHead = root; // ?????????????????????????
                }
            } else {

            }

        }



        // return;
    };


}
