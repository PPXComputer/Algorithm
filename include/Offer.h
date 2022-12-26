//
// Created by Administrator on 2022/3/21.
//

#ifndef SSH_OFFER_H
#define SSH_OFFER_H

#include "folly/String.h"
#include <cassert>

#include<vector>
#include<string>
#include<folly/Conv.h>
#include<folly/FBString.h>
#include<folly/FBVector.h>
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

    // 二叉树的最大径和
    static void maxPathSum();

    static void setZero();

    static void groupAnagrams();

    static void toGoatLatin();

    static void wordBreak();

    static void containsNearbyAlmostDuplicate();

    static void mergeKLists();

    static void eightnum();

private:
    struct TreeNode {
        TreeNode();

        explicit TreeNode(int x);

        TreeNode(const TreeNode &) = delete;

        TreeNode &operator=(const TreeNode &) = delete;

        TreeNode *left;
        TreeNode *right;
        int val;

        // [1,2,-1,32,#]
        static std::unique_ptr<TreeNode> newTree(folly::fbstring &data);

        ~TreeNode();


        void setNode(std::vector<TreeNode *> &&container);

    private:
        static void decode(const folly::fbvector<folly::StringPiece> &data,
                           int pos, bool isLeft, TreeNode *preNode,
                           std::vector<TreeNode *> &container);

        // decode tree node
        static std::unique_ptr<TreeNode> newTree(int length);

        static void decode(const std::vector<int> &data, TreeNode *parent, int left, int right, bool isLeft,
                           std::vector<TreeNode *> &container);

        std::vector<TreeNode *> node = {};
    };

    struct ListNode {
        ListNode();

        explicit ListNode(int x);

        explicit ListNode(int x, ListNode *raw_ptr);

        ListNode(const ListNode &) = delete;

        ListNode &operator=(const ListNode &) = delete;

        ListNode *next;
        int val;


        static void printAll(ListNode *cur);

        static std::unique_ptr<ListNode> new_list(size_t length);

        static std::unique_ptr<ListNode> new_list(const std::vector<int> &data);

        ~ListNode();

    private:

        std::vector<ListNode *> node = {};
    };
};


#endif //SSH_OFFER_H
