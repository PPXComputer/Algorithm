#include "../include/LeetCode.h"
#include <dbg.h>
#include <cassert>
#include <array>
#include <optional>
#include <fmt/format.h>
#include <folly/Range.h>
#include<folly/Traits.h>
#include <unordered_map>

using std::string;

void LeetCode::medium_33() {
    //旋转后的数组
    auto impl = []() {
        std::array<int, 7> nums{4, 5, 6, 7, 0, 1, 2};
        int target = 0;
        int left = 0;
        int right = nums.size() - 1;
        while (left < right) {
            int mid = ((right - left) >> 1) + left;
            dbg(left, right, mid, nums[mid]);
            if (target == nums[mid]) return mid;
            if (nums[mid] <= nums[right]) // 右侧有序
            {
                if (target <= nums[right] and target > nums[mid]) {
                    left = mid + 1;
                } else {
                    //向左边找
                    right = mid - 1;
                }

            } else { //左侧有序
                if (target >= nums[left] and target < nums[mid]) {
                    right = mid - 1;
                } else {
                    //向右边找
                    left = mid + 1;
                }
            }
        }
        if (nums[left] == target)return left;
        return -1;
    };
    dbg(impl());
}

void LeetCode::medium_34() {
    using std::vector;
    auto answer = [](vector<int> &nums, int target) -> vector<int> {
        if (nums.empty())return {-1, -1};
        int left = 0;
        int right = static_cast<int>(nums.size() - 1);
        while (left < right) {
            //找到第一个出现target的地方
            int mid = left + ((right - left) >> 1);
            dbg(left, right, mid, nums[mid]);
            if (nums[mid] > target) {
                right = mid - 1;
            } else if (nums[mid] < target) {
                left = mid + 1;
            } else {
                right = mid; //等于则不动 可能他就是第一个
            }
        }
        if (nums[left] != target)return {-1, -1};
        int left_result = left;
        left = 0;
        right = static_cast<int>(nums.size() - 1);

        while (left < right) {
            //找到最后一个出现target的地方
            int mid = left + ((right - left) >> 1) + 1; //向右侧偏移一格 向右边靠
            dbg(left, right, mid, nums[mid]);
            if (nums[mid] > target) {
                right = mid - 1;
            } else if (nums[mid] < target) {
                left = mid + 1;
            } else {
                left = mid;
            }

        }
        return {left_result, left};
    };
    vector<int> data{5, 7, 7, 8, 8, 10};
    dbg(answer(data, 8));
}

void LeetCode::medium_74() {
    std::array<std::array<int, 4>, 3> matrix = {
            std::array<int, 4>{1, 3, 5, 7},
            {10, 11, 16, 20},
            {23, 30, 34, 60}
    };
    // 将当前的搜索 转换为二维坐标
    int left = 0;
    constexpr size_t matrix_column = matrix.front().size();
    constexpr size_t matrix_row = matrix.size();
    int right = static_cast<int> (matrix_row * matrix_column - 1);
    int target = 3;
    auto transform_really_pos = [](int pos, int row, int column) -> std::pair<int, int> {
        assert(pos >= 0 and pos < row * column);
        return {pos / column, pos % column};
    };
    auto find = [&]() {
        while (left < right) {
            int mid = ((right - left) >> 1) + left;
            dbg(fmt::format("{} {} {} ", left, right, mid));
            auto pos = transform_really_pos(mid, matrix_row, matrix_column);
            dbg(fmt::format("{}", matrix[pos.first][pos.second]));
            if (matrix[pos.first][pos.second] == target) {
                return true;
            } else if (matrix[pos.first][pos.second] > target) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        auto pos = transform_really_pos(left, matrix_row, matrix_column);
        return matrix[pos.first][pos.second] == target;

    };
    dbg(find());

}

void LeetCode::reverseKGroup() {
    constexpr int length = 10;
    std::unique_ptr<ListNode> root_ptr = LeetCode::ListNode::new_list(length);
    ListNode *root = root_ptr.get();
    //多个值相连
    //旋转当前中最近的数据
    int k = 4;
    int time = length / 4;
    int count = 0;


    // 翻转后的 头  尾 和后一个元素
    auto reverse_list = [](ListNode *start, int need) {
        ListNode *head = nullptr;
        ListNode *cur = nullptr;
        int repeat_time = 0;
        std::tuple<ListNode *, ListNode *, ListNode *> result{nullptr, start, nullptr};
        while (repeat_time != need) {
            cur = start->next;
            start->next = head;
            head = start;
            start = cur;
            repeat_time++;

            bool isLastTime = repeat_time == need;
            if (isLastTime) {
                //将当前最后一个的元素保留下来
                std::get<0>(result) = head;
                std::get<2>(result) = cur;
            }
        }
        return result;
    };

    ListNode *result = nullptr;
    ListNode *lastTail = nullptr;
    ListNode *lastStart = root;
    if (time > 0 and length != 1) {
        int start = 0;
        while (time != start) {
            auto result_tuple = reverse_list(lastStart, k);
            if (start == 0) {
                result = std::get<0>(result_tuple); //将结果保存
            } else {
                if (lastTail)lastTail->next = std::get<0>(result_tuple);

            }
            lastStart = std::get<2>(result_tuple);
            lastTail = std::get<1>(result_tuple);
            start++;
        }
    }


}

void LeetCode::findPeakElement() { //爬坡 不断向旁边最高前进
    vector<int> data{1, 2, 1, 3, 5, 6, 4};
    int left = 0;
    int right = data.size() - 1;
    while (left < right) {
        int mid = ((right - left) >> 1) + left;

        dbg(fmt::format("{} {} {} ", left, right, mid));
        dbg(fmt::format("{} {} {} ", data[left], data[right], data[mid]));

        if (data[mid] < data[static_cast<size_t>(mid + 1)]) {
            left = mid + 1;
        } else {
            right = mid; // 保留当前位置的点
        }
    }
    dbg(left);

}

void LeetCode::findMin() {
    std::vector<int> data = {3, 4, 5, 1, 2};
    //找到旋转数组的最小值
    // 找到当前每次中到达的数据点 找到一个数当前的 左边的数大于他 右边的数小于他
    auto ans = [](vector<int> &nums) {
        // 一边有序的数组
        int left = 0;
        int right = static_cast<int>(nums.size() - 1);

        while (left < right) {
            int mid = ((right - left) >> 1) + left;
            dbg(fmt::format("{} {} {} ", left, right, mid));
            dbg(fmt::format("{} {} {} ", nums[left], nums[right], nums[mid]));
            if (nums[mid] < nums[right])
                right = mid;
            else
                left = mid + 1;

        }
        dbg(nums[left]);

    };
    ans(data);

}

void LeetCode::deleteDuplicatesFromList() {
    //给定一个已排序的链表的头 head ， 删除原始链表中所有重复数字的节点，只留下不同的数字 。返回 已排序的链表 。
    std::vector<int> data = {1, 1, 2, 2};
    std::unique_ptr<ListNode> ptr = ListNode::new_list(data);
    auto head = ptr.get();
    auto answer_forward = [&]() {
        auto root = head;
        if (root == nullptr)return head;
        int val;
        auto cur = root->next;
        ListNode *prev = root;
        bool isFirstTime = true;
        while (cur != nullptr) {
            val = root->val;

            if (val == cur->val) {
                while (cur != nullptr and cur->val == val) {
                    cur = cur->next;
                }

                if (prev == root) {
                    if (cur == nullptr)return static_cast<ListNode *>(nullptr);
                    else {
                        head = cur;
                        prev = cur;
                        root = cur;
                    }
                } else {
                    prev->next = cur;
                    root = cur;
                }
                if (cur == nullptr)break;
                cur = cur->next;

            } else {
                prev = root;
                root = cur;
                cur = cur->next;
            }

        }
        return head;
    };
    //answer_forward();
    auto answer_dummpy_head = [&]() {
        auto root = head;
        if (root == nullptr)return head;
        auto dummy = std::make_unique<ListNode>(0, head);
        auto cur = dummy.get();
        while (cur->next != nullptr and cur->next->next != nullptr) {
            if (cur->next->val == cur->next->next->val) {
                auto forward = cur->next->next;
                do { forward = forward->next; } while (forward != nullptr and forward->val != cur->next->val);
                cur->next = forward;
            } else {
                cur = cur->next;
            }
        }
        return dummy->next;
    };
}

void LeetCode::three_num() {
    // 找到所有和为 0的不重复的三元组
    std::vector nums = {-2, 0, 0, 2, 2};

    auto answer = [&](const std::vector<int> &data) -> std::vector<std::vector<int>> {
        if (nums.size() < 3)return {};
        // 二元组问题
        std::unordered_map<int, int> map;
        for (auto i: data) {
            if (map.find(i) == map.end()) {
                map.insert({i, 1});
            } else {
                map[i] += 1;
            }
        }
        dbg(map);
        std::vector<std::vector<int>> result;
        for (auto first: data) {
            if (map[first] > 0) {
                //找到当前的元素为第一个元素

                int take_time = -1;
                int value = -first;
                map[first] -= 1;
                bool if_not_match = true;
                for (auto second: data) {
                    if (map[second] > 0) {
                        //找到对称的数据
                        map[second] -= 1;
                        int third = value - second;
                        if (map.find(third) != map.end() and map[third] > 0) {
                            if (not if_not_match) {
                                if (map[first] <= 0) {
                                    map[second] += 1;
                                    continue;
                                }
                                map[first] -= 1;
                            } else {
                                if_not_match = false;
                            }
                            map[third] -= 1;
                            dbg(map[third], map[first], if_not_match ? map[first] : map[first] - 1);

                            result.emplace_back(vector<int>{first, second, third});

                        } else {
                            map[second] += 1;
                        }
                    }
                }
                if (if_not_match) {
                    map[first] += 1;
                }

            }
        }
        dbg(map);
        dbg(result);
        return result;

    };
    //answer(nums);

    auto sort_answer = [&](std::vector<int> &data) -> std::vector<std::vector<int>> {
        std::vector<int>::size_type size = data.size();
        if (size < 3)return {};
        std::sort(data.begin(), data.end());
        int start = 0;

        std::vector<std::vector<int>> result;
        while (start < size - 2 and data[start] <= 0) {
            if (start > 0 and data[start] == data[static_cast<size_t>(start) - 1]) {
                start++;
                continue;
            } // 相同直接跳答案处
            //data 已经排序完成了 如果大于零则没必要再继续下去了
            int left = start + 1;
            int right = static_cast<int>(size - 1);
            while (left < right) {
                int cur = data[left] + data[start] + data[right];
                //auto str = fmt::format("left{} right{} start{}", left, right, start);
                //dbg(str, cur);
                if (cur == 0) {
                    //dbg(data[start], data[left], data[right]);
                    result.emplace_back(std::vector<int>{data[start], data[left], data[right]});
                    // 跳过相同的left 到达了最后一个相同的位置
                    while (left < right and data[left] == data[static_cast<size_t>(left) + 1])left++;
                    while (left < right and data[right] == data[static_cast<size_t>(right) - 1])right--;
                    left++;
                    right--; //到达两者都不重复上上一解的地方
                } else if (cur > 0) {
                    right -= 1;
                } else {
                    left += 1;
                }
            }
            start++;
        }
        return result;
    };
    auto parm = vector<int>{-1, 0, 1, 2, -1, -4};
    dbg(sort_answer(parm));
}

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

void LeetCode::climbStairs() {
    auto answer = [](int n) -> int {

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

void LeetCode::houseRobber() {
    /*
    * 你是一个专业的小偷，计划偷窃沿街的房屋。每间房内都藏有一定的现金，
     影响你偷窃的唯一制约因素就是相邻的房屋装有相互连通的防盗系统，如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警。

    给定一个代表每个房屋存放金额的非负整数数组，计算你 不触动警报装置的情况下 ，一夜之内能够偷窃到的最高金额。
    */
    vector<int> data{2, 7, 9, 3, 1};
    const auto answerEnum = [](std::vector<int> &nums) {

        const auto answerImpl = [](int cur, int money, std::vector<int> &nums, auto &&answerImpl) -> int {
            if (cur >= nums.size())return money;
            int result = money + nums[cur];

            std::max({answerImpl(cur + 1, money, answerImpl),
                      result,
                      answerImpl(cur + 2, money, answerImpl)});
            return result;
        };

    };
    const auto answerDp = [](std::vector<int> &nums) {

    };
}

void LeetCode::maxArea() {
    vector data{1, 8, 6, 2, 5, 4, 8, 3, 7};
    const auto answer = [](vector<int> &height) {
        int j = static_cast<int> (height.size() - 1);
        int i = 0;
        int result = (j - i) * std::min(height[i], height[j]);
        while (i != j) {
            result = std::max((j - i) * (std::min(height[i], height[j])), result);
            if (height[i] < height[j])i++;
            else j++;
        }
        return result;
    };
    const auto answerForward = [](vector<int> &height) {
        int j = static_cast<int> (height.size() - 1);
        int i = 0;
        int result = (j - i) * std::min(height[i], height[j]);
        int n = 0;

        while (i != j) {
            if (height[i] < height[j])n = height[i];
            else n = height[j];
            result = std::max(result, n * (j - i));
            while (i != j and height[i] <= n) {
                i++;
            }
            while (i != j and height[j] <= n) {
                j--;
            }
        }
        return result;
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
