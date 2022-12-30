//
// Created by ppx on 2022/1/16.
//
#include "TreeAlgo.h"

#include <fmt/core.h>
#include <folly/FBVector.h>

#include <algorithm>
#include <array>
#include <optional>
#include <unordered_map>
using folly::fbvector;
void TreeAlgo::cal_node_distance() {
  // ????????????
  const std::unique_ptr<TreeNode> &tree = create_tree();

  auto impl = [](TreeNode *root, auto &&self) -> std::pair<int, int> {
    // ??????? root ??????
    if (root == nullptr) {
      return {0, 0};  //??????????
    } else {
      std::pair<int, int> left = self(root->left, self);
      std::pair<int, int> right = self(root->right, self);
      int cur_height = std::max(left.first, right.first) + 1;
      int result = std::max(std::max(left.second, right.second), cur_height);
      return {cur_height, result};
    }
  };
  fmt::print("impl(tree, impl) {}", impl(tree.get(), impl).second);
}

std::unique_ptr<TreeNode> TreeAlgo::create_tree() {
  using std::make_unique;
  std::unique_ptr<TreeNode> root = make_unique<TreeNode>(0);
  root->left = new TreeNode(1);
  root->left->left = new TreeNode(3);
  root->right = new TreeNode(2);
  root->right->left = new TreeNode(4);
  root->right->right = new TreeNode(5);
  root->right->right->right = new TreeNode(6);

  return root;
}

void TreeAlgo::find_non_exist_num() {
  // ?????????? ???????? 2^16 ?????? 2^15
  // ???????????????д????count???
  //        constexpr int length = 1 << 16;
  //        std::array<int, length> data{};
}

void TreeAlgo::run() { TreeAlgo::cal_node_distance(); }

void TreeAlgo::find_most_search_subtree() {  // ????????????? ????????????

  std::unique_ptr<TreeNode> root = TreeAlgo::create_tree();

  auto fn = [](TreeNode *cur) {
    auto count = [](TreeNode *subTree, auto &&count) -> int {
      if (subTree != nullptr) {
        int left = count(subTree->left, count);
        int right = count(subTree->right, count);
        return left + right + 1;
      } else {
        return 0;
      }
    };

    auto search_sub_tree = [](TreeNode *data, auto &&search_sub_tree) -> bool {
      if (data == nullptr) return true;
      if (data->left != nullptr and (data->left->value > data->value))
        return false;
      if (data->right != nullptr and (data->right->value < data->value))
        return false;
      return search_sub_tree(data->left, search_sub_tree) and
             search_sub_tree(data->right, search_sub_tree);
    };

    auto impl = [&](TreeNode *data, auto &&impl) -> int {
      if (search_sub_tree(data, search_sub_tree)) {
        return count(data, count);
      }
      if (data != nullptr) {
        int left = 0, right = 0;
        if (search_sub_tree(data->left, search_sub_tree)) {
          left = count(data->left, count);
        }
        if (search_sub_tree(data->right, search_sub_tree)) {
          right = count(data->right, count);
        }
        return std::max(left, right);
      }
      return 0;
    };
    return impl(cur, impl);
  };

  struct BstNodeResult {
    int min;  // ???? ????С?? ?
    int max;  // ???? ?????? ?
    Node *bstNodeHead;
    int height;
    bool isBst;  //???????????? ???????????ж?
    BstNodeResult(int mi, int ma, Node *bst, int he, int isb)
        : min(mi), max(ma), bstNodeHead(bst), height(he), isBst(isb) {}
  };
  auto searchImpl = [](Node *root,
                       auto &&searchImpl) -> std::optional<BstNodeResult> {
    if (root == nullptr) {
      return {};
    }

    std::optional<BstNodeResult> leftValue = searchImpl(root->left, searchImpl);
    std::optional<BstNodeResult> rightValue =
        searchImpl(root->right, searchImpl);

    BstNodeResult bstNodeResult =
        BstNodeResult(INT_MAX, INT_MIN, nullptr, 1, false);

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
        if (left.max <= right.min and root->value >= left.max and
            root->value <= right.min) {
          bstNodeResult.bstNodeHead = root;  // ?????????????????????????
        }
      } else {
      }
    }

    // return;
  };
}

void TreeAlgo::connect() {  // 将完美二叉数据右侧节点进行链接
  class Node {
   public:
    int val;
    Node *left;
    Node *right;
    Node *next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node *_left, Node *_right, Node *_next)
        : val(_val), left(_left), right(_right), next(_next) {}
  };
  const auto dfs = [](Node *root) {
    if (root == nullptr) return root;

    const auto traverse = [](Node *first, Node *second, auto self) -> void {
      if (first == nullptr or second == nullptr) return;
      first->next = second;  // todo 没搞懂这个三叉树遍历是什么
      self(first->left, first->right, self);
      self(second->left, second->right, self);
      self(first->right, second->left, self);
    };

    // 遍历相关节点将当前的子节点链接完成 则可以完成所有的节点链接
    const auto impl = [](Node *cur, auto self) -> void {
      if (cur == nullptr || cur->left == nullptr || cur->right == nullptr)
        return;
      cur->left->next = cur->right;
      if (cur->next != nullptr) {
        cur->right->next = cur->next->left;
      }
      self(cur->left, self);
      self(cur->right, self);
    };
    traverse(root->left, root->right, traverse);
    return root;
  };
}

void TreeAlgo::constructMaximumBinaryTree() {
  // 最大二叉树

  folly::fbvector<int> nums{3, 2, 1, 6, 0, 5};
  auto maxIndex = std::max_element(nums.begin(), nums.end());
  using iter = decltype(nums.begin());

  using TreeNodePtr = TreeNode *;
  const auto dfs = [&nums](iter cur, iter left, iter right,
                           TreeNodePtr &curNode, auto dfs) -> void {
    // 将当前的转化为 left  转化为左子树
    curNode = new TreeNode{*cur};
    if (cur != left) {  // 有左子树
      dfs(std::max_element(left, cur), left, cur, curNode->left, dfs);
    }

    if (cur + 1 != right) {  // 有右子树
      dfs(std::max_element(cur + 1, right), cur + 1, right, curNode->right,
          dfs);
    }
  };
  TreeNodePtr root = nullptr;
  // dfs(maxIndex, nums.begin(), nums.end(), root, dfs);
}

void TreeAlgo::buildTree() {
  // 均无重复元素

  // 中左右
  fbvector<int> preorder{3, 9, 20, 15, 7};
  // 左中右
  fbvector<int> inorder{9, 3, 15, 20, 7};
  using iter = decltype(inorder.begin());

  std::unordered_map<int, int> map;
  map.reserve(inorder.size());
  int index = 0;
  for (int i : inorder) {
    map[i] = index++;
  }

  // 所有的右边界是闭的区间
  const auto dfs2 = [&](int preorderLeft, int preorderRight, int inorderLeft,
                        int inorderRight, auto dfs2) -> TreeNode * {
    if (preorderLeft > preorderRight) return nullptr;
    int curValue = preorder[preorderLeft];  // 当前root 的值
    auto root = new TreeNode{curValue};
    int inorderCur = map[curValue];
    int leftTreeLength = inorderCur - inorderLeft;  // 左子树的长度

    root->left = dfs2(preorderLeft + 1, preorderLeft + leftTreeLength,
                      inorderLeft, inorderCur - 1, dfs2);
    root->right = dfs2(preorder, preorderLeft + leftTreeLength + 1,
                       preorderRight, inorderCur + 1, inorderRight, dfs2);
    return root;
  };

  //  TreeNode *res = dfs(preorder.begin(), preorder.end(), inorder.begin(),
  //                      inorder.end(), dfs);
  //  return dfs2(preorder,0, preorder.size()-1,0,inorder.size()-1);
}
