#include "LeetCode.h"
#include <dbg.h>
#include <cassert>
#include <array>
#include <stack>
#include <fmt/format.h>
#include <folly/Range.h>
#include <unordered_map>

using std::string;

void LeetCode::fib() {
    constexpr auto answer = [] {
        constexpr int n = 3;
        constexpr auto fib_impl = [] {
            std::array<int, 31> fib{0, 1};
            for (int i = 2; i != 31; ++i) {
                fib[i] = fib[i - 1] + fib[i - 2];
            }
            return fib;
        }();

        return fib_impl[n];
    };
}

void LeetCode::tribonacci() {
    //T0 = 0, T1 = 1, T2 = 1, 且在 n >= 0 的条件下 Tn+3 = Tn + Tn+1 + Tn+2
    constexpr auto fib_impl = [] {
        std::array<int, 37> fib{0, 1, 1};
        for (int i = 3; i != 31; ++i) {
            fib[i] = fib[i - 1] + fib[i - 2] + fib[i - 3];
        }
        return fib;
    }();
    auto answer = [&](int n) {
        return fib_impl[n];
    };
}

void LeetCode::minCostClimbingStairs() {
    std::vector<int> data = {1, 100, 1, 1, 1, 100, 1, 1, 100, 1};

    const auto minCostClimbingStairsImpl = [](vector<int> &cost) {
        std::unordered_map<int, int> cache;
        const auto impl = [&](int cur, int spend, auto &&self) -> int {
            if (cur == cost.size()) {
                return spend;
            }
            if (cur > cost.size()) {
                return INT_MAX;
            }
            int msg = cur * 1000 + spend;
            if (cache.find(msg) != cache.end()) {
                return cache[msg];
            }
            cache[msg] = std::min(self(cur + 2, spend + cost[cur], self),
                                  self(cur + 1, spend + cost[cur], self));
            return cache[msg];
        };
    };
    const auto dpAnswer = [](vector<int> &cost) {

        // 将不同的元素的对应起来
        // dp[i]=min(dp[i-1]+cost[i-1],dp[i-2]+cost[i-2])


        // dp[i] 为到达第i级阶梯的所需要的最小代价 接着向上走则需要花费当前的cost[i]
        // 同时 有两种方法到达 相关的 从i-1 或者i-2位置向上走
        // dp[i] = min(dp[i-1]+cost[i-1] ,dp[i-2]+cost[i-2])

        int first = 0;
        int second = 0; //dp[0]  dp[1]
        for (int i = 2; i <= cost.size(); i++) //最后到达 size()处 需要多少
        {
            //到达 i 位置则
            int tmp = std::min(first + cost[i - 2], second + cost[i - 1]);
            first = second;
            second = tmp;
        }
        return second;
    };
}

void LeetCode::findAnagrams() {
    //给定两个字符串 s 和 p，找到 s 中所有 p 的 异位词 的子串，返回这些子串的起始索引。不考虑答案输出的顺序。

    // 异位词 指由相同字母重排列形成的字符串（包括相同的字符串）。
    /*
    * 输入: s = "cbaebabacd", p = "abc"
    输出: [0,6]
    */


    //auto findAnagramsEnum = [](string s, string p)->vector<int> {
    //	//  直接暴力匹配当前出现的字符串
    //	string::size_type sSize = s.size();
    //	string::size_type pSize = p.size();
    //	if (sSize < pSize)return {};
    //	std::array<int, 26> count_p = { 0 };
    //	for (char pChar : p) {
    //		count_p[static_cast<int>(pChar)] += 1;
    //	}
    //	std::array<int, 26> check_count = { 0 };


    //	int first = 0;
    //	int second = 1;
    //	check_count[static_cast<int>(s[0])] += 1;
    //	string::size_type lastFirst = sSize - pSize;
    //
    //	auto compare = [&]()->std::pair<int, int> {
    //		for (int i = 0; i < 26; i++)
    //		{
    //			if (count_p[i] == check_count[i]) {
    //				continue;
    //			}
    //			else if (count_p[i] > check_count[i]) {
    //				return { -1,i };
    //			}
    //			else {
    //				return { 1, i };
    //			}
    //		}
    //		return { 0,0 };
    //	};

    //	vector<int> result;
    //	while (first <= lastFirst and second < s.size())
    //	{
    //		auto compareResult = compare();
    //		if (compareResult.first == 0) {
    //			result.push_back(first);
    //			check_count[s[first]] -= 1;
    //			first++;
    //		}
    //		else if (compareResult.first > 0) {
    //			check_count[s[first]] -= 1;
    //			first++;
    //			if (first <= lastFirst) {
    //				check_count[s[first]] += 1;
    //			}
    //		}
    //		else {
    //			if(s[second] ==)
    //		}
    //	}

    ///std::equal(count_p.begin(), count_p.end(), check_count.begin(), check_count.end());
    //};


    string first = "abacbabc";
    string second = "abc";
    auto findAnagramsEnum = [](string s, string p) -> vector<int> {
        string::size_type sSize = s.size();
        string::size_type pSize = p.size();
        if (sSize < pSize)return {};
        std::array<int, 26> firstCount{};
        std::array<int, 26> secondCount{};
        for (int i = 0; i < pSize; i++) {
            firstCount[static_cast<int>(p[i] - 'a')]++;
            secondCount[static_cast<int>(s[i] - 'a')]++;
        }
        vector<int> result;
        if (std::equal(firstCount.begin(), firstCount.end(), secondCount.begin(), secondCount.end())) {
            dbg(firstCount, secondCount);
            result.push_back(0);
        }
        for (int i = pSize; i < sSize; i++) {
            // 将当前的 pSize 添加进入
            secondCount[static_cast<int>(s[i - pSize] - 'a')]--;
            secondCount[static_cast<int>(s[i] - 'a')]++;
            dbg(secondCount);
            if (std::equal(firstCount.begin(), firstCount.end(), secondCount.begin(), secondCount.end())) {
                result.push_back(i - pSize + 1);
            }
        }
        return result;
    };
    //dbg(findAnagramsEnum(first, second));


    const auto answerslidingWindow = [](string const &s, string const &p) -> vector<int> {
        // 将当前存在的 range 标识为 滑动窗口的 range
        string::size_type sSize = s.size();
        string::size_type pSize = p.size();
        if (sSize < pSize)return {};
        std::array<int, 26> firstCount{};
        std::array<int, 26> secondCount{};
        for (int i = 0; i < pSize; i++) {
            firstCount[static_cast<int>(p[i] - 'a')]++;
        }
        int left = 0;
        vector<int> result;
        for (int right = 0; right < sSize; right++) {
            // 将其填入当前所匹配的子串中
            int curGet = static_cast<int>(s[right] - 'a');
            secondCount[curGet]++;
            auto range = folly::Range(s.begin() + left, s.begin() + right + 1);
            auto cur = fmt::format(" left {} right {} cur {}", left, right, s[left]);
            dbg(cur, range);
            while (secondCount[curGet] > firstCount[curGet]) {
                //当前的填入的字符 超过了当前的总数
                // left 一直回退 直到当前情况下的 secondCount[curGet] ==firstCount[curGet]
                // 最坏情况是 left 到达了 right 位置

                auto range = folly::Range(s.begin() + left + 1, s.begin() + right + 1);
                int curLeft = static_cast<int>(s[left] - 'a');
                secondCount[curLeft]--;
                left++;
                string cur = fmt::format(" left-1 {} right {} cur {}", left - 1, right, left);
                dbg(range, cur);
            }
            if (right - left + 1 == pSize) {
                result.push_back(left);
                dbg("result.push_back(left) " + std::to_string(left));

            }

        }
        return result;

    };
    dbg(answerslidingWindow("cbaebabacd", "abc"));
}

void LeetCode::numSubarrayProductLessThanK() {

    // 双指针 将当前的窗口缩小到合适位置
    const auto answerDp = [](vector<int> &nums, int k) -> int {
        int cur = 1;
        int left = 0;
        int result = 0;
        vector<int>::size_type numSize = nums.size();
        for (int right = 0; right < numSize; right++) {
            cur = cur * nums[right];
            if (cur < k) {
                if (right > left + 1) { //包含了多个元素的成绩证明可以添加多个进入
                    result += right - left + 1;
                    const auto &range = folly::Range(
                            nums.begin() + left, nums.begin() + right + 1);
                    dbg(range, left, right);
                } else {
                    result++;
                }
            }
            while (cur > k) {
                // 左侧指针前进到
                cur /= nums[left];
                left++;
            }

        }
        return result;
    };
    std::vector<int> data = {10, 5, 2, 6};
    answerDp(data, 100);
}

void LeetCode::allPathsSourceTarget() {
    auto answer = [](vector<vector<int>> &graph) -> vector<vector<int>> {
        size_t graphSize = graph.size();
        std::vector<std::vector<int>> result;
        std::vector<int> curResult;
        auto dfs = [&](int curPos, auto &&dfs) -> void {
            curResult.push_back(curPos);
            if (curPos == graphSize - 1) {
                result.push_back(curResult);
            } else {
                for (int nextPos: graph[curPos]) {
                    dfs(nextPos, dfs);
                    result.pop_back();
                }
            }
        };
        dfs(0, dfs);
        return result;
    };
}

void LeetCode::findTargetSumWays() {


    auto answer_ = [](vector<int> &nums, int target) {
        // 将重复的数字记录下来
        std::unordered_map<int, int> map;
        for (int i: nums) {
            ++map[i];
        }
        int result = 0;
        //  dfs
        auto answer_dfs = [&map](decltype(map.begin()) &iter, int cur, int tar, auto dfs) {
            if (tar == cur) return 1;
            if (iter == map.end())return 0;

            int maxElem = iter->first * iter->second;

            int result = 0;
            if (iter->first != 0) {
                ++iter;
                for (int i = -maxElem; i <= maxElem; i += iter->first) {
                    result += dfs(iter, cur + i, tar, dfs);
                }
            } else {
                ++iter;
                result += dfs(iter, cur, tar, dfs) * iter->second;
            }
            return result;
        };
        // dynamic
        auto size = map.size();
        std::vector<std::vector<int>> cache(size + 1, std::vector<int>(target + 1));
        auto answer_dyn = [&]() {
            // 将进入函数的内容改成 填充二维矩阵的值
            vector<int> &back = cache.back();
            std::fill(back.begin(), back.end(), 1);
            for (int row = target - 1; row > 0; --row) {
                auto iter = map.begin();
                auto mapEnd = map.end();
                for (int col = 0; col < size; ++col, ++iter) {
                    while (iter != mapEnd) {
                        if (iter->first != 0) {
                            int maxElem = iter->first * iter->second;
                            // 将相同值的部分叠加起来  注意需要叠加的值 不能越界
                            for (int i = -maxElem;
                                 i <= maxElem and col - i >= 0 and col - i < target;
                                 i += iter->first) {
                                cache[row][col] += cache[row + 1][col - i];
                            }
                        } else {
                            cache[row][col] = cache[row + 1][col] * iter->second;
                        }
                    }
                }
            }
            // 第0 行不需要全部填满 填第一个就行了

            auto iter = map.begin();
            auto mapEnd = map.end();
            int result = cache[1][0];
            if (iter != mapEnd) {
                int maxElem = iter->first * iter->second;
                // 将相同值的部分叠加起来  注意需要叠加的值 不能越界
                if (maxElem == 0) {
                    return result * iter->second;
                }
                for (int i = -maxElem; i <= 0; i += iter->first) {
                    result += cache[1][-i];
                }
            }
            return result;

        };


        // 压缩空间
        auto answer_depression = [&]() {
            //  [0 ,mapSize ] 代表map中的值
            int mapSize = map.size();
            dbg(mapSize);
            std::vector<int> val(mapSize, 1); //只使用一行作为当前的存储
            for (int row = 0; row < target; ++row) {
                auto iter = map.begin();
                auto mapEnd = map.end();
                for (int col = 0; col < mapSize; ++col, ++iter) {
                    int maxElem = iter->first * iter->second;
                    // 将相同值的部分叠加起来  注意需要叠加的值 不能越界
                    dbg(maxElem);
                    if (maxElem == 0) {
                        val[col] = val[col] * iter->second;
                        continue;
                    }
                    for (int i = -maxElem; i <= maxElem; i += iter->first * 2) {
                        dbg(i, col);
                        if (col - i >= 0 and col - i < mapSize) {
                            dbg(col - i);
                            val[col] += val[col - i];
                        }

                    }

                }
            }
            return val[0];
        };

        dbg(answer_depression());
    };
    std::vector<int> data{1, 1, 1, 1, 1};
    answer_(data, 3);
}

void LeetCode::flattenList() {
    class Node {
    public:
        int val;
        Node *prev;
        Node *next;
        Node *child;
    };
    auto root = Node{};
    auto head = std::addressof(root);
    if (head == nullptr)return;
    std::stack<Node *, std::vector<Node *>> mStack;
    while (head->next != nullptr or not mStack.empty()) {

        // 到达了当前的层的最后一个节点
        if (head->next == nullptr) {
            if (head->child != nullptr) {
                //  直接将当前节点转向一个下一个节点
                head->next = head->child;
                head = head->next;
            } else {
                // 寻找当前的栈中的所存在的元素
                while (not mStack.empty()) {
                    Node *i = mStack.top();
                    mStack.pop();
                    // 连线当前节点的数据
                    head->next = i->next;
                    while (head->next != nullptr) {
                        head = head->next;
                    }
                }
            }
        } else {
            // 当前的数据 需要考虑是否为一个 直接悬挂的链表节点
            if (head->child != nullptr) {
                mStack.push(head);
                head = head->child;
            } else {
                head = head->next;
            }
        }
    }

}

