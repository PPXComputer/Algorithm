//
// Created by ppx on 2022/1/16.
//
#include "TreeAlgo.h"  
#include "UnionFindSet.h"

#include <dbg.h>
#include <fmt/core.h>
#include <folly/FBVector.h>
#include <folly/String.h>

#include <algorithm>
#include <array>
#include <cstddef>
#include <optional>
#include <string>
#include <unordered_map>
#include <stack>
#include <queue>

using folly::fbvector;
using std::vector;

void TreeAlgo::cal_node_distance() {
    // ????????????
    const std::unique_ptr<TreeNode> &tree = create_tree();

    std::function<std::pair<int, int>(TreeNode *)> impl = [&](TreeNode *root) -> std::pair<int, int> {
        // ??????? root ??????
        if (root == nullptr) {
            return {0, 0};  //??????????
        } else {
            std::pair<int, int> left = impl(root->left);
            std::pair<int, int> right = impl(root->right);
            int cur_height = std::max(left.first, right.first) + 1;
            int result = std::max(std::max(left.second, right.second), cur_height);
            return {cur_height, result};
        }
    };
    fmt::print("impl(tree, impl) {}", impl(tree.get()).second);
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
    // ???????????????д????m_count???
    //        constexpr int length = 1 << 16;
    //        std::array<int, length> data{};
}

void TreeAlgo::run() { TreeAlgo::cal_node_distance(); }

void TreeAlgo::find_most_search_subtree() {  // ????????????? ????????????

    std::unique_ptr<TreeNode> root = TreeAlgo::create_tree();

    auto fn = [](TreeNode *cur) {
        std::function<int(TreeNode *)> count = [&](TreeNode *subTree) -> int {
            if (subTree != nullptr) {
                int left = count(subTree->left);
                int right = count(subTree->right);
                return left + right + 1;
            } else {
                return 0;
            }
        };

        std::function<bool(TreeNode *)> search_sub_tree = [&](TreeNode *data) -> bool {
            if (data == nullptr) return true;
            if (data->left != nullptr && (data->left->value > data->value))
                return false;
            if (data->right != nullptr && (data->right->value < data->value))
                return false;
            return search_sub_tree(data->left) &&
                   search_sub_tree(data->right);
        };

        auto impl = [&](TreeNode *data) -> int {
            if (search_sub_tree(data)) {
                return count(data);
            }
            if (data != nullptr) {
                int left = 0, right = 0;
                if (search_sub_tree(data->left)) {
                    left = count(data->left);
                }
                if (search_sub_tree(data->right)) {
                    right = count(data->right);
                }
                return std::max(left, right);
            }
            return 0;
        };
        return impl(cur);
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

        if (leftValue && rightValue) {
            auto &left = leftValue.value();
            auto &right = rightValue.value();
            if (left.isBst && right.isBst) {
                if (left.max <= right.min && root->value >= left.max &&
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

        std::function<void(Node *, Node *)> traverse = [&](Node *first, Node *second) -> void {
            if (first == nullptr || second == nullptr) return;
            first->next = second;  // todo 没搞懂这个三叉树遍历是什么
            traverse(first->left, first->right);
            traverse(second->left, second->right);
            traverse(first->right, second->left);
        };

        // 遍历相关节点将当前的子节点链接完成 则可以完成所有的节点链接
        const auto impl = [](Node *cur, auto self) -> void {
            if (cur == nullptr || cur->left == nullptr || cur->right == nullptr)
                return;
            cur->left->next = cur->right;
            if (cur->next != nullptr) {
                cur->right->next = cur->next->left;
            }
            self(cur->left);
            self(cur->right);
        };
        traverse(root->left, root->right);
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
    for (int i: inorder) {
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

void TreeAlgo::serialize() {
    auto *root = new TreeNode(1);
    root->left = new TreeNode(2);

    root->right = new TreeNode(3);
    root->right->left = new TreeNode(4);
    root->right->right = new TreeNode(5);

    std::function<void(std::string &, TreeNode *)> serImpl = [&](std::string &str, TreeNode *root) -> void {
        if (str.empty()) {
            str.push_back(root->value + '0');
            serImpl(str, root->left);
            serImpl(str, root->right);
        } else {
            if (root == nullptr) {
                str.append(",#");
            } else {
                char a = '0' + root->value;
                str.append({',', a});
                serImpl(str, root->left);
                serImpl(str, root->right);
            }
        }
    };
    auto serialize = [serImpl](TreeNode *root) -> std::string {
        if (root == nullptr) return {};
        std::string a;
        serImpl(a, root);
        return a;
    };

    std::function<std::string(TreeNode *)> serOtherImpl = [&](TreeNode *root) -> std::string {
        if (root == nullptr) return {"#,"};
        auto left = serOtherImpl(root->left);
        auto right = serOtherImpl(root->right);
        return std::to_string(root->value) + "," + left + right;
    };
    dbg(serialize(root));  //[ 1, 2, 3, null, null, 4, 5 ]
    dbg(serOtherImpl(root));
}

void TreeAlgo::deserialize() {
    std::string str{"2,1,#,6,#,#,3,#,#"};
    std::vector<char> res;
    folly::split(",", str, res);
    const auto impl = [&res](int cur, auto impl) -> TreeNode * {
        if (cur >= res.size() || res[cur] == '#') return nullptr;

        auto *root = new TreeNode(res[cur]);
        root->left = impl(2 * cur + 1, impl);
        root->right = impl(2 * cur + 2, impl);
        return root;
    };
    // return impl(0,impl)
}

void TreeAlgo::findDuplicateSubtrees() {

    std::unordered_set<int> res;
    std::unordered_set<std::string> set;
    std::function<std::string(TreeNode *)> impl = [&](TreeNode *root) -> std::string {
        if (root == nullptr)return "#";
        auto left = impl(root);
        auto right = impl(root);
        auto subTree = std::to_string(root->value) + left + right;
        if (! set.insert(subTree).second) {
            res.insert(root->value);
        }
        return subTree;

    };
    std::vector<int> vec(res.size());
    std::transform(res.begin(), res.end(), std::back_inserter(vec), [](int a) { return a; });

}

void TreeAlgo::kthSmallest() {
    const std::unique_ptr<TreeNode> &ptr = TreeAlgo::create_tree();
    TreeNode *root = ptr.get();
    int a = 10e4 + 1;
    int cnt = 1;
    int k = 1;
    std::function<void(TreeNode *)> mid = [&](TreeNode *r) {
        if (r != nullptr) {
            mid(r->left);
            if (cnt++ == k) {
                a = r->value;
                return;
            }

            mid(r->right);
        }
    };

    mid(root);
    dbg(a, cnt, k);
}

void TreeAlgo::bstToGst() {


}

void TreeAlgo::lowestCommonAncestor() {
    //
    TreeNode *p = nullptr;
    TreeNode *q = nullptr;
    std::function<TreeNode *(TreeNode *)> impl = [&](TreeNode *root) {
        bool rootIsNull = root == nullptr;
        bool rootIsQ = root->value == q->value;
        bool rootIsP = root->value == p->value;
        bool pLeft_QRight = root->value > p->value && root->value < q->value;
        bool qLeft_PRight = root->value > q->value && root->value < p->value;
        if (rootIsNull || rootIsP || rootIsQ || pLeft_QRight || qLeft_PRight)return root;


        if (root->value < std::min(q->value, p->value))
            return impl(root->right);

        return impl(root->left);
    };

    decltype(impl) otherImpl = [&](TreeNode *root) {
        if (root->value > p->value && root->value > q->value) {
            return otherImpl(root->left);
        } else if (root->value < p->value && root->value < q->value) {
            return otherImpl(root->right);
        } else return root;
    };
}

void TreeAlgo::lowestCommonAncestor2() {

}

void TreeAlgo::allPathsSourceTarget() {
    using std::vector;
    vector<vector<int>> graph = {{0, 1, 1, 0},
                                 {0, 0, 0, 1},
                                 {0, 0, 0, 1},
                                 {0, 0, 0, 0}};
    int graphSize = graph.size();
    vector<int> tmp{0};
    vector<vector<int>> res;
    std::function<void(int)> traverse = [&](int next) {

        const auto &ref = graph[next];

        if (std::find_if(ref.begin(),
                         ref.end(),
                         [](int a) {
                             return a != 0;
                         }) == ref.end()) {
            res.emplace_back(tmp);

        } else {
            for (int i = 0; i < graphSize; ++i) {

                if (i != next && graph[next][i] != 0) {
                    tmp.emplace_back(i);
                    traverse(i);
                    tmp.pop_back();
                };

            }
        }
    };
    traverse(0);
    dbg(res);
}

void TreeAlgo::isBipartite() {
    using std::vector;
    vector<vector<int>> graph = {
            {1, 3},
            {0, 2},
            {1, 3},
            {0, 2}
    };
    const auto impl = [&]() {
        int graphSize = static_cast<int>(graph.size());
        vector<int> color(graphSize); //0 没色 1 2
        vector<int> q;
        q.reserve(graphSize);
        for (int i = 0; i < graphSize; i++) {
            if (color[i] == 0) {
                color[i] = 1;
                q.push_back(i);
            }
            while (!q.empty()) {

                int parent_node = q.back();
                q.pop_back();
                dbg(parent_node, graph[parent_node]);
                for (int next_node: graph[parent_node]) {
                    dbg(color);
                    // 只有没被访问的数据才能作为parent_node进入下一个
                    if (color[next_node] == 0) {
                        color[next_node] = color[parent_node] == 2 ? 1 : 2;
                        q.push_back(next_node);

                    } else {
                        if (color[next_node] == color[parent_node])
                            return false;
                    }
                    dbg(color);
                }
            }

        }
        return true;
    };
    dbg(impl());
}

void TreeAlgo::possibleBipartition() {
    using std::vector;
    vector<vector<int>> dislikes = {{1, 2},
                                    {1, 3},
                                    {2, 4}};
    int n = 4;
    const auto s = [&]() {

        vector<int> vist(n);
        std::unordered_map<int, std::unordered_set<int>> graph;
        for (const auto &a: dislikes) {
            graph[a[0]].insert(a[1]);
            graph[a[1]].insert(a[0]);
        }

        std::stack<int> q;
        for (int i = 0; i < n; ++i) {
            if (vist[i] == 0) {
                vist[i] = 1;
                q.push(i);
            }

            while (!q.empty()) {
                int parent_node = q.top();
                q.pop();
                if (graph.count(parent_node - 1))
                    for (int b: graph[parent_node - 1]) {
                        int j = b - 1;
                        if (vist[j] == 0) {
                            vist[j] = vist[parent_node] == 1 ? 2 : 1;
                            q.push(j); //  这只能凑一对 找到则下家
                        } else if (vist[j] == vist[parent_node])return false;
                    }

            }
           
        }
        return true;
    };
    s();
}

void TreeAlgo::minCostConnectPoints() {
    vector<vector<int>> origin{{0, 0},
                               {2, 2},
                               {3, 10},
                               {5, 2},
                               {7, 0}};
    const auto curSize = origin.size();
    size_t graphSize = curSize * curSize;
    vector<vector<int>> graph(curSize, vector<int>(curSize));
    const auto calDistance = [](const vector<int> &a, const vector<int> &b) {
        assert(a.size() == 2);
        assert(b.size() == 2);
        return std::abs(a[0] - b[0]) + std::abs(b[1] - a[1]);
    };

    // build graph
    for (int i = 0; i < curSize; ++i) {
        for (int j = i + 1; j < curSize; ++j) {
            graph[i][j] = calDistance(origin[i], origin[j]);
            graph[j][i] = origin[i][j];
        }
    }

    //最短生成树
    // 每次选择最短的路径
    const auto otherImpl = [curSize, &graph] {
        struct IndexAndDistance {
            int start;
            int end;
            int distance;
        };
        // 默认是 大顶堆
        const auto cmp =
                [](const IndexAndDistance &a, const IndexAndDistance &b) {
                    return a.distance < b.distance;
                };
        std::priority_queue<IndexAndDistance, vector<IndexAndDistance>, decltype(cmp)> queue(cmp);
        std::unordered_set<int> graphJointSet{0};
        graphJointSet.reserve(curSize);
        std::stack<int, vector<int>> jointStack;
        jointStack.push(0);
        int result = 0; //结果 用于累加路径和
        while (! jointStack.empty()) {
            int curIndex = jointStack.top();
            for (int start: graphJointSet) {
                for (int end = 1; end < curSize; ++end) {
                    if (graphJointSet.count(end) == 0) {
                        queue.push(IndexAndDistance{start, end, graph[start][end]});
                    }
                }
            }
            if (queue.empty()) {
                break;
            }
            IndexAndDistance cur = queue.top();
            jointStack.push(cur.end);
            result += cur.distance;
        }
    };


    // prim 算法
    const auto prim = [&](int start) {
        vector<int> distanceCost(curSize, INT_MAX);

        std::unordered_set<int> jointSet{start};
        jointSet.reserve(curSize);
        int res = 0;
        for (int i = 0; i < curSize; ++i) {
            if (i == start) continue;
            distanceCost[i] = graph[i][start];
        }
        while (jointSet.size() != curSize) {
            int minDistance = INT_MAX;
            int nextIndex = -1;
            for (int i = 0; i < curSize; ++i) {
                if (jointSet.count(i) == 0
                    && distanceCost[i] < minDistance) {
                    nextIndex = i;
                    minDistance = distanceCost[i];
                }
            }
            //加入到新的节点
            jointSet.insert(nextIndex);
            res += minDistance;
            for (int i = 0; i < curSize; ++i) {
                if (i == nextIndex) continue;
                int newDistance = graph[i][nextIndex];
                if (distanceCost[i] > newDistance) {
                    distanceCost[i] = newDistance;
                }
            }
        }


    };


    const auto Kruskal = [&]() {
        struct IndexAndDistance {
            int start;
            int end;
            int distance;
        };
        const auto cmp =
                [](const IndexAndDistance &a, const IndexAndDistance &b) {
                    return a.distance < b.distance;
                };
        std::priority_queue<IndexAndDistance, vector<IndexAndDistance>, decltype(cmp)> heap(cmp);
        for (int i = 0; i < curSize; ++i) {
            for (int j = i + 1; j < curSize; ++j) {
                heap.push(IndexAndDistance{i, j, graph[i][j]});
            }
        }
        UnionFindSet mSet{static_cast<int>(curSize)};
        while (! heap.empty()) {
            IndexAndDistance indexAndDistance = heap.top();
            heap.pop();
            int startFather = mSet.find_head(indexAndDistance.start);
            int endFather = mSet.find_head(indexAndDistance.end);
            if (startFather != endFather) {
                mSet.merge(indexAndDistance.start, indexAndDistance.end);
            }
        }
    };
}
