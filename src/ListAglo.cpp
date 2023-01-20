//
// Created by 破忆断回 on 2021/9/24.
//

#include "ListAglo.h"
#include<iostream>
#include<fmt/format.h>
#include<cassert>
#include<utility>
#include<array>
#include<algorithm>
#include <functional>

using std::cout;
using std::array;
using std::addressof;

inline void ListAlgo::get_node_counter() {

    using ptr = BinaryTreeNode::UniquePtr;
    ptr root = BinaryTreeNode::New(0);
    int result = 0;
    std::function<void(const ptr &)> impl = [&result, &impl](const ptr &root) -> void {
        if (root) {
            result += 1;
            impl(root->left);
            impl(root->right);
        }
    };
    impl(root);
    cout << fmt::format("result {}", result);


    const auto &notRecusive = [&root] {
        // 找到最有
    };


}

inline void ListAlgo::create_tree() {
    array pre = {1, 2, 4, 5, 3, 6, 7};
    array in = {4, 2, 5, 1, 6, 3, 7};//给定后续
    array<int, 7> pos{};

    std::function<void(int, int, int, int, int, int)> impl;
    impl = [&pre, &in, &pos, &impl]
            (int A, int B, int C, int D, int E, int F) {
        if (A > B)return;// 越界
        if (A == B)// 只有一个元素
        {
            pos[B] = pre[A];
            return;
        }

        int cur_root = pre[A];
        int root = 0;
        for (int i = C; i <= D; i++) {
            if (in[i] == cur_root) {
                root = i;
                break;
            }
        }
        pos[F] = pre[A];
        impl(A + 1, A + root - C,
             C, root - 1,
             E, E + root - C - 1
        );
        impl(A + root - C + 1, B,
             root + 1, D,
             E + root - C, F - 1
        );
    };
    impl(0, 6, 0, 6, 0, 6);
    std::for_each(pos.begin(), pos.end(), [](int data) {
        cout << data << " ";
    });
}

[[maybe_unused]] void ListAlgo::partition_list_by_value() {
    Node root;
    root.value = 1;
    Node node1;
    node1.value = 4;
    root.next = addressof(node1);
    Node node2;
    node2.value = 2;
    node1.next = addressof(node2);
    Node node3;
    node3.value = 3;
    node2.next = addressof(node3);
    Node node4;
    node4.value = 5;
    node3.next = addressof(node4);
    int target = 2;
    Node *cur = addressof(root);
    while (cur->value != target) {
        cur = cur->next;
    }

    Node *tail_node = get_tail_node(cur);
    Node *head = deal_front(addressof(root), cur, tail_node);
    deal_back(cur, tail_node, head);
    while (head) {
        std::cout << head->value << '\n';
        head = head->next;
    }
}

[[maybe_unused]] void ListAlgo::deal_three_list(ListAlgo::Node *root, int target) {
    assert(root);
    Node *less = nullptr;
    Node *lessStart = nullptr;
    Node *eqStart = nullptr;
    Node *eq = nullptr;
    Node *more = nullptr;
    Node *moreStart = nullptr;
    Node *cur = root;
    Node *next = nullptr;
    while (cur) {
        // 不断删除节点 将不同的节点下的数据作为的一个新的分类归总
        next = cur->next;
        if (cur->value < target) {
            if (not less) {
                less = cur;
                lessStart = cur;
            } else {
                less->next = cur;
                less = less->next;
            }

        } else if (cur->value > target) {
            if (not more) {
                more = cur;
                moreStart = cur;
            } else {
                more->next = cur;
                more = more->next;
            }

        } else {
            if (not eq) {
                eq = cur;
                eqStart = cur;
            } else {
                eq->next = cur;
                eq = eq->next;
            }

        }
        cur->next = nullptr;
        cur = next;
    }
    if (less) {
        less->next = eqStart;
        if (eq)eq->next = moreStart;
    }
    while (lessStart) {
        std::cout << lessStart->value << '\n';
        lessStart = lessStart->next;
    }

}

void ListAlgo::partition_other() {

    Node root;
    root.value = 1;
    Node node1;
    node1.value = 4;
    root.next = addressof(node1);
    Node node2;
    node2.value = 2;
    node1.next = addressof(node2);
    Node node3;
    node3.value = 3;
    node2.next = addressof(node3);
    Node node4;
    node4.value = 5;
    node3.next = addressof(node4);
    int target = 3;
    deal_three_list(addressof(root), target);

}

[[maybe_unused]] void ListAlgo::deal_back(ListAlgo::Node *cur, ListAlgo::Node *tail_node, ListAlgo::Node *head) {
    // 当前的元素并不为最后一个
    assert(cur);
    int target = cur->value;
    Node *pro = cur;
    cur = cur->next;
    while (cur != tail_node->next) {
        if (cur->value < target) {
            pro->next = pro->next->next;
            cur->next = head->next;
            head->next = cur;
            cur = pro->next;
        } else {
            pro = cur;
            cur = cur->next;
        }
    }
}

[[maybe_unused]] ListAlgo::Node *
ListAlgo::deal_front(ListAlgo::Node *root, ListAlgo::Node *cur, ListAlgo::Node *tail_node) {
    assert(root);
    Node *result_head = root;
    Node *pro = nullptr;
    while (root != cur) {
        if (root->value > cur->value) {
            if (pro != nullptr) {
                pro->next = pro->next->next;
                tail_node->next = root;
                root->next = nullptr;
                root = pro->next;
            } else {
                pro = root->next;
                tail_node->next = root;
                root->next = nullptr;
                root = pro;
                pro = nullptr;
                result_head = root; // 只有最前的数据需要移动的时候 result_head需要移动
            }
        } else {
            pro = root;
            root = root->next;
        }
    }
    return result_head;
}

[[maybe_unused]] ListAlgo::Node *ListAlgo::get_tail_node(ListAlgo::Node *pNode) {
    while (pNode->next != nullptr) {
        pNode = pNode->next;
    }
    return pNode;
}
