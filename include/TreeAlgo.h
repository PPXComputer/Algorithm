//
// Created by ppx on 2022/1/16.
//

#ifndef SSH_TREEALGO_H
#define SSH_TREEALGO_H

#include <memory>

struct TreeNode
{
    explicit TreeNode(int data) : value(data) {}

    ~TreeNode() = default;

    TreeNode *left = nullptr;
    TreeNode *right = nullptr;
    int value = 0;
};

class TreeAlgo
{
public:
    using node = TreeNode;

    static std::unique_ptr<TreeNode> createTree();

    static void calNodeDistance();

    static void findNonExistNum();

    static void run();

    static void findMostSearchSubtree();

    static void connect(); // LeetCode 116

    static void constructMaximumBinaryTree(); // leetcode 654

    // 105. 从前序与中序遍历序列构造二叉树
    static void buildTree();

    static void serialize();

    static void deserialize();

    static void findDuplicateSubtrees();

    // 230.
    static void kthSmallest();

    //
    static void bstToGst();

    ////235. 二叉搜索树的最近公共祖先     std::function<TreeNode*()> imp=[]
    static void lowestCommonAncestor();

    // 236. 二叉树的最近公共祖先
    static void lowestCommonAncestor2();

    // 剑指 Offer II 110. 所有路径
    static void allPathsSourceTarget();

    // 785. 判断二分图
    static void isBipartite();

    // 886. 可能的二分法
    static void possibleBipartition();

    // 1584. 连接所有点的最小费用
    static void minCostConnectPoints();

    static void treeSerializeAndDeserialize();
private:
};

#endif // SSH_TREEALGO_H
