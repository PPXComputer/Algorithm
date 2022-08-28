// Created by Administrator on 2022/3/21.
//

#include <cmath>
#include <string>
#include <random>
#include <set>
#include <numeric>
#include <vector>
#include <dbg.h>
#include <fmt/core.h>

#include<unordered_map>
#include <queue>
#include "Offer.h"

using std::vector;
using std::set;
using std::string;
using std::unordered_map;


int Offer::divide() {
    int a = 15;
    int b = 2;
    bool negative = true;
    if (a < 0 and b < 0) negative = false;
    a = std::abs(a);
    b = std::abs(b);

    int answer = a / b;
    return 0;
}

int Offer::addBinary() {
    string first = "10";
    string second = "101111";
    size_t secondSize = second.size();
    size_t firstSize = first.size();
    std::string result;
    if (firstSize >= secondSize) {
        std::swap(first, second);
        std::swap(firstSize, secondSize);
    }

    bool isMetric = false;
    result.reserve(secondSize + 1);
    int firstIndex = firstSize - 1;
    int secondIndex = secondSize - 1;
    while (firstIndex >= 0) {
        int addNum = 0;
        if (isMetric) {
            addNum = first[firstIndex] + second[secondIndex] - '0' * 2 + 1;

        } else {
            addNum = first[firstIndex] + second[secondIndex] - '0' * 2;

        }
        dbg(addNum);
        if (addNum >= 2) {
            result.push_back(addNum + '0' - 2);
            isMetric = true;
        } else {
            result.push_back('0' + addNum);
            isMetric = false;
        }
        --firstIndex;
        --secondIndex;
    }

    dbg(result);
    while (secondIndex >= 0) {
        if (isMetric) {
            char addNum = 0;
            addNum = static_cast<char>(second[secondIndex] - '0' + 1);
            if (addNum == 2) {
                isMetric = true;
                result.push_back('0');
            } else {
                result.push_back('1');
                --secondIndex;
                while (secondIndex >= 0) {
                    result.push_back(second[secondIndex]);
                    --secondIndex;
                }
                isMetric = false;
            }
        } else {
            result.push_back(second[secondIndex]);
        }
        --secondIndex;
    }
    if (isMetric) {
        result.push_back('1');
    }


    std::reverse(result.begin(), result.end());
    dbg(result);


    vector<int> resultA;
    int newCapacity = 80;
    resultA.reserve(newCapacity);

    resultA.push_back(0);
    for (int i = 1; i < newCapacity; ++i) {
        if ((i & 1) == 1) { //奇数则 将当前的 存在的 转换为
            resultA.push_back(resultA[i >> 1] + 1);
        } else {
            resultA.push_back(resultA[i >> 1]);
        }
    }


    return 0;
}

void Offer::singleNum() {
    std::vector<int> nums{0, 1, 0, 1, 0, 1, 99};
    std::sort(nums.begin(), nums.end());
    int count = 1;
    int last = nums[0];
    for (auto start = nums.begin() + 1; start != nums.end(); ++start) {
        if (*start == last) {
            count++;
        } else {
            if (count == 1) {
                dbg(last);
                break;
            }
            count = 1;
            last = *start;
        }
    }
    //    dbg(nums.back());
    std::vector<std::string> words = {"abcw", "baz", "foo", "bar", "xtfn", "abcdef"};
    size_t n = words.size();
    auto masks = std::vector<int>(n);
    for (int i = 0; i < n; ++i) {
        dbg(masks[i]);
    }
    int res = 0;
    for (int i = 0; i < n; i++) {
        int bitMask = 0;
        for (char c: words[i]) {
            bitMask |= (1 << (c - 'a'));
        }
        masks[i] = bitMask;
        dbg(masks[i]);
    }

}

void Offer::threeSum() {
    //    std::unordered_map<int, int> mMap;
    //    for (int i: data) {
    //        mMap[i]++;
    //    }
    //    size_t size = data.size();
    //    vector<vector<int>> result;
    //    for (int i = 0; i + 2 < size; ++i) {
    //        int first = data[i];
    //        if (mMap[first] > 0) {
    //            --mMap[first];
    //            bool isSuccess = false;
    //            for (int j = i + 1; j + 1 < size; ++j) {
    //
    //                int second = data[j];
    //                if (mMap[second] > 0) {
    //                    --mMap[second];
    //                    int third = -i - j;
    //                    if (mMap[third] > 0) {
    //                        --mMap[third];
    //                        isSuccess = true;
    //                        result.emplace_back(std::vector<int>{first, second, third});
    //                    } else {
    //                        ++mMap[second];
    //                    }
    //                }
    //
    //            }
    //            if (not isSuccess) {
    //                ++mMap[first];
    //            }
    //        }
    //    }
    //threeSumFirstAnswer(data);


    std::vector<int> data{-2, 0, 1, 1, 2};
    // threeSumSecondAnswer(data);
    // 使用  sort 的方法找到的当前的 需要的 
    auto answer = [&data]()mutable {
        std::sort(data.begin(), data.end());
        auto size = std::size(data);
        dbg(data);
        std::vector<std::vector<int>> results;
        int left = 1;
        int right = size - 1;
        for (int i = 0; i < size;) {
            int cur = data[i];

            dbg(i, left, right);
            bool isFind = false;
            while (left < right) {

                const string &basicString = fmt::format("{} {} {}", cur, data[left], data[right]);
                dbg(basicString);
                //找到当前符合的两个位置的
                int curResult = data[left] + data[right] + cur;

                if (curResult > 0) {
                    --right;
                } else if (curResult < 0) {
                    ++left;
                } else {
                    results.emplace_back(std::vector<int>{cur, data[left], data[right]});
                    isFind = true;
                    break;
                }
            }
            if (i + 1 < size and data[i + 1] == data[i]) {
                while (i + 1 < size and data[i + 1] == data[i])
                    ++i;
            } else {
                ++i;
            }
            if (isFind)
                right = right - 1;
            left = i + 1;
        }
        dbg(results);
    };

    auto otherAnswer = [&data]()mutable {
        std::vector<std::vector<int>> result;
        std::sort(data.begin(), data.end());
        auto size = std::size(data);

        // 有两种情况
        //1. 数字重复了   比如 -1,-1,0,0,1,1   -1,0,1 成功后 left从0 要到一个不等于0的地方
        //2. 当前数字匹配多次 -2,-1,0,2,3    -2 0 2   -2  -1  3 所以匹配成功后left 要转到下一个地方 不能直接打破循环

        for (int i = 0; i < size; ++i) {
            if (i > 0 and data[i - 1] == data[i]) continue;
            int left = i + 1;
            int right = size - 1;
            while (left < right) {
                int curResult = data[left] + data[i] + data[right];
                if (curResult == 0) {
                    result.emplace_back(std::vector<int>{data[i], data[left], data[right]});
                    while (left < right and data[left] == data[1 + left])++left;
                    ++left; //到达下一个 left 不相同的地方
                    continue;
                } else if (curResult < 0) {
                    ++left;
                } else {
                    --right;
                }
            }
        }
        dbg(result);
    };
    otherAnswer();
}

void Offer::threeSumSecondAnswer(vector<int> &data) {
    std::unordered_map<int, int> mMap;
    for (int i: data) {
        mMap[i]++;
    }
    std::vector<std::vector<int>> results;
    auto size = data.size();
    for (int i = 0; i < size; ++i) {
        int cur = data[i];
        if (mMap[cur] > 0) {
            --mMap[cur];
            bool isSuccess = false;
            for (int j = i + 1; j < size; ++j) {
                int first = data[j];
                if (mMap[first] > 0) {
                    --mMap[first];
                    const auto &iterator = mMap.find(-cur - first);
                    if (iterator != mMap.end() and ((*iterator).second > 0)) {
                        dbg(*iterator);
                        results.emplace_back(std::vector<int>{cur, first, (*iterator).first});
                        isSuccess = true;
                        continue;
                    }
                    ++mMap[first];
                }
            }

            if (not isSuccess) {
                ++mMap[cur];
            }
        }
        // 跳过重复的数据


    }
    dbg(results);
}

void Offer::threeSumFirstAnswer(std::vector<int> &data) {
    std::vector<std::vector<int>> result;
    std::sort(data.begin(), data.end());
    int size = data.size();
    for (int i = 0; i < size; ++i) {

        while (i + 1 < size and data[i] == data[i + 1]) {
            ++i;
        }
        int left = i + 1;
        int right = size - 1;
        while (left < right) {
            if (data[i] + data[left] + data[right] == 0) {
                dbg(data[i], data[left], data[right]);
                result.emplace_back(std::vector<int>{data[i], data[left], data[right]});
                left++;
                right--;
                continue;
            } else if (data[i] + data[left] + data[right] > 0) {
                --right;
            } else {
                ++left;
            }
        }
    }
}

void Offer::minSubArrayLen() {
    // 滑动窗口
    std::vector<int> data{2, 3, 1, 2, 4, 3};
    int target = 7;
    auto size = data.size();
    int right = 0;
    int curResult = data[0];
    int result = INT_MAX;
    int left = 0;
    while (left <= right and right < size) {
        if (curResult < target) {
            ++right;
            if (right < size)curResult += data[right];
        } else if (curResult >= target) {
            int curRange = right - left + 1;
            if (result > curRange) {
                result = curRange;
            }
            curResult -= data[left];
            ++left;
        }
    }
    dbg(result);

}

void Offer::numSubarrayProductLessThanK() {
    //给定一个正整数数组 nums和整数 k ，请找出该数组内乘积小于 k 的连续的子数组的个数。
    // 给定一个长度 1850 长度为4 数组的个数相当于 1+2+3+4   不断进行[fast-slow+1]
    auto answer = [] {
        std::vector<int> data{10, 5, 2, 6};
        int k = 100;
        int fast = 0;
        int slow = 0;
        auto size = data.size();
        int tmp = 1;
        int result = 0;
        //如果当前要加入的fast 节点越界 证明没啥需要加的了 直接退出
        while (fast < size) {
            // 结果为 result += fast  -slow+1  (fast 已经自增了)
            if (data[fast] * tmp < k) {
                tmp *= data[fast];
                ++fast;
                result += fast - slow;
            } else {
                // tmp 除去 slow的部分 slow移动到  slow+1
                // 如果 当前的只有一个元素都不行的话 fast和 slow需要一起+1
                tmp /= data[slow];
                if (fast == slow) {
                    ++fast;
                }
                ++slow;
            }
        }

        return result;
    };
//    dbg(answer());
    auto answerSumk = [] {
        vector<int> data{1, 1, 1};
        int k = 2;
        int size = data.size();
        // 当数组元素存在负数的情况时  则滑动窗口可能存在失效的问题
        // 当前的 大于当前元素的时候 无法前进 或者回溯
        // 构建 辅助前缀和的数据
        int preSum = 0;

        // 问题就转化成 前缀和中相差 为k的数据对数有多个了
        std::unordered_map<int, int> map;
        map.reserve(size + 1);
        map[0] = 1;
        int result = 0;
        for (int i = 0; i < size; ++i) {
            preSum += data[i];
            dbg(map, preSum);
            const auto &findIterator = map.find(preSum - k);
            if (findIterator != map.end()) {
                result += findIterator->second;
            }
            ++map[preSum];
        }
        return result;
    };
    dbg(answerSumk());
}

void Offer::findMaxLengthWithSameCount() {
    //给定一个二进制数组 nums , 找到含有相同数量的 0 和 1 的最长连续子数组，并返回该子数组的长度。
    // 不能使用滑动窗口 因为你不知道当前的 前进会增加0 还是后退会增加零
    // 0,1 相同数量 进行前缀的异或和
    std::vector<int> data{0, 1};
    auto size = data.size();
    {

        int countSum = data[0];
        std::vector<int> countCache;
        countCache.reserve(size + 1);
        countCache.push_back(0);
        int result = 0;
        for (int i = 0; i < size; ++i) {
            int cur = data[i] ? 1 : -1;
            countCache.push_back(cur + countCache[i]);
        }
        dbg(countCache);
    }

    {
        std::unordered_map<int, int> mMap;
        mMap.reserve(size + 1);
        mMap.insert({0, 0});
        int count = 0;
        int result = 0;
        for (int i = 0; i < size; ++i) {
            count += data[i] ? 1 : -1;

            auto iterator = mMap.find(count);
            if (iterator != mMap.end()) {
                result = std::max(result, i - iterator->second + 1);
            } else {
                // 插入当前元素 第一次遇到则 赋值为 i
                mMap[count] = i;
            }

        }
        dbg(result);
    }
}

int Offer::pivotIndex() {
    /*
     * 给你一个整数数组 nums ，请计算数组的 中心下标 。

    数组 中心下标 是数组的一个下标，其左侧所有元素相加的和等于右侧所有元素相加的和。

     */
    auto a = [] {
        std::vector<int> data{1, 7, 3, 6, 5, 6};
        dbg(data);
        auto size = data.size();

        if (size == 1) return -1;

        std::vector<int> sumCache;
        sumCache.reserve(size);
        int sum = 0;
        for (int i = 0; i < size; ++i) {
            sum += data[i];
            sumCache.emplace_back(sum);
        }
        if (sum - data[0] == 0) {
            return 0;
        }
        dbg(data);
        // 将当前的 下标中索引求出
        dbg(sumCache);
        for (int i = 1; i < size; ++i) {
            dbg(sum - sumCache[i], sumCache[i - 1]);
            if (sum - sumCache[i] == sumCache[i - 1])return i;
        }
        return -1;
    };
    auto b = [] {
        std::vector<int> data{1, 7, 3, 6, 5, 6};
        auto size = data.size();
        int total = std::accumulate(data.begin(), data.end(), 0);
        int sum = 0;
        for (int i = 0; i < size; ++i) {
            sum += data[i];
            if (total - sum == sum - data[i]) {
                return i;
            }
        }
        return -1;
    };
//    return a();

    std::vector<std::vector<int>> sumCache{};
    sumCache.emplace_back(std::vector<int>{-4});
    sumCache.emplace_back(std::vector<int>{-5});
    int row = sumCache.size();
    int col = sumCache[0].size();
    for (int i = 0; i < row; ++i) {
        for (int j = 1; j < col; ++j) {
            sumCache[i][j] += sumCache[i][j - 1];
        }
    }
    int result = 0;
    int row1 = 0;
    std::random_device device; //输出机器级别的随机数
    std::default_random_engine e{device()}; //固定好种子后
    // 将当前的 随机数发生器传给 分布实现去
    std::binomial_distribution<int> distribution(3, 2);
    int col1 = distribution(e) % 2 ? 0 : 1;
    int row2 = 0;
    int col2 = 1;
    for (int i = row1; i <= row2; ++i) {
        if (col1 != 0) {
            result += sumCache[i][col2] - sumCache[i][col1 - 1];
        } else {
            result += sumCache[i][col2];
        }
    }
    dbg(result);
    return 0;
}

int Offer::NumMatrix() {
    vector<vector<int>> matrix{{-4, -5},
                               {1,  2}};
    int row = matrix.size();
    int col = matrix[0].size();
    auto answer = [&matrix, row, col] {

        std::vector<std::vector<int>> preSum(row + 1, std::vector<int>(col + 1));
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                preSum[i + 1][j + 1] = preSum[i][j + 1] + preSum[i + 1][j] - preSum[i][j] + matrix[i][j];
            }
        }

        auto sumRegion = [&](int row1, int col1, int row2, int col2) {
            ++row1;
            ++col1;
            ++row2;
            ++col2;
            return preSum[row2][col2] + preSum[row1 - 1][col1 - 1] - preSum[row1 - 1][col2] - preSum[row2][col1 - 1];
        };
        dbg(preSum);

        dbg(sumRegion(0, 0, 1, 1));
        int row1 = 1;
        int col1 = 1;
        int row2 = 2;
        int col2 = 2;
        dbg(preSum[row2][col2], preSum[row1 - 1][col1 - 1], preSum[row1 - 1][col2], preSum[row2][col - 1]);
    };


    auto inPlaceAnswer = [&matrix, row, col] {

        for (int i = 1; i < row; ++i) {
            matrix[i][0] += matrix[i - 1][0];
        }
        for (int j = 1; j < col; ++j) {
            matrix[0][j] += matrix[0][j - 1];
        }
        for (int i = 1; i < row; ++i) {
            for (int j = 1; j < col; ++j) {
                matrix[i][j] += matrix[i - 1][j] + matrix[i][j - 1] - matrix[i - 1][j - 1];
            }
        }
        dbg(matrix);

    };
    inPlaceAnswer();
    return 0;
}

void Offer::checkInclusion() {
    //给定两个字符串 pattern 和 text，写一个函数来判断 text 是否包含 pattern 的某个变位词。
    //换句话说，第一个字符串的排列之一是第二个字符串的 子串 。
    //pattern = "ab" text = "eidbaooo" true

    auto answer = [] {
        string pattern = "ab";

        string text = "eidboaoo";
        const int patternLen = pattern.size();
        const int textLen = text.size();

        std::vector<int> data(26);
        for (int i = 0; i < patternLen; ++i) {
            ++data[pattern[i] - 'a'];
        }
        int left = 0;

        int right = left;
        while (right < textLen) {
            dbg(data);
            int curPos = text[right] - 'a';
            --data[curPos];
            while (data[curPos] < 0) {
                int leftPos = text[left] - 'a';
                ++data[leftPos];
                ++left;
            }

            //到达匹配的位置处
            // 如果是部分匹配则 可知当前的 right-left+1 < patternLen
            if (patternLen == right - left + 1) {
                return true;
            }
            ++right;
        }
        return false;
    };
    dbg(answer());
}

int Offer::lengthOfLongestSubstring(string &s) {
    std::array<int, 256> cache{};
    const int length = s.length();
    int left = 0;
    int right = 0;
    int result = 0;
    while (right < length) {
        const char cur = s[right];
        ++cache[cur];
        while (cache[cur] > 1) {
            const char leftPos = s[left];
            --cache[leftPos];
            ++left;
        }
        result = std::max(right - left + 1, result);
        ++right;
    }
    return result;
}

int Offer::countSubstrings() {
    // 回文子串的个数
    string varString = "abababaadhqjqqq";
    const int len = varString.length();
    int result = 0;
    // 中心点为 一时 有 len 个
    // 中心点 为二时 有 len-1 个 故为  2*len-1
    for (int cur = 0; cur < 2 * len - 1; ++cur) {
        int left = cur / 2;
        // right 可能为 中心点为两个元素
        // right 应该字符串的 长度相关 可能为 偶数 或者奇数
        int right = left + cur % 2;
        while (right < len and left >= 0 and varString[left] == varString[right]) {
            --left;
            ++right;
            ++result;
        }
    }
    return result;
}

void Offer::removeNthFromEnd() {
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
    // dummy->left;
}

void Offer::maxPathSum() {
    // 二叉树的最大路径和
    // 分为当前的两种情况 将通过根节点的 和 不同通过根节点的

    int maximum = INT_MIN;


    fbstring str{"[1,-2,-3,1,3,-2,#,-1]"};
    auto a = TreeNode::newTree(str);
    int result = INT_MIN;
    auto answer = [&result](TreeNode *root, auto &&answer) {


        if (root == nullptr)return 0;

        int maxLeft = std::max(0, answer(root->left, answer));
        int maxRight = std::max(0, answer(root->right, answer));
        int curResult = std::max({root->val, root->val + maxLeft, root->val + maxRight});

        // 因为是选择 一条路径 所以 子答案中的  root+left+right不能直接作为结果返回
        result = std::max({maxLeft + maxRight + root->val, curResult, result});
        return curResult;
    };
    dbg(answer(a.get(), answer));
}

void Offer::setZero() {
    //给定一个 m x n 的矩阵，如果一个元素为 0 ，则将其所在行和列的所有元素都设为 0 。请使用 原地 算法。
    vector<vector<int>> matrix{{0, 1, 2, 0},
                               {3, 4, 5, 2},
                               {1, 3, 1, 5}};


    auto answer = [&matrix]() mutable {
        auto row = matrix.size();
        auto col = matrix[0].size();
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                if (matrix[i][j] == 0) {
                    matrix[i][j] = INT_MIN;
                    // search in different row and col
                    for (int next = 0; next < col; ++next) {
                        if (next == j) continue;
                        if (matrix[i][next] != 0)
                            matrix[i][next] = 0;
                        else
                            matrix[i][next] = INT_MIN;
                    }
                    break;
                }
            }
        }
        dbg(matrix);
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                if (matrix[i][j] == INT_MIN) {
                    for (int k = 0; k < row; ++k) {
                        matrix[k][j] = 0;
                    }
                }

            }
        }

    };


//    answer();
//    dbg(matrix);
    dbg(matrix);
    auto answer_without_space = [&]() {
        auto row = matrix.size();
        auto col = matrix[0].size();
        // 使用数组的 第一行 第一列 作为存储
        auto iterator = std::find(matrix.front().begin(), matrix.front().end(), 0);
        bool findZeroInFirstRow = iterator != matrix.front().end();

        bool findZeroInFirstCol = std::find_if(matrix.begin(),
                                               matrix.end(),
                                               [](const std::vector<int> &data) { return data[0] == 0; }) !=
                                  matrix.end();

        // 从第二行进行 搜索出来   找到了  0则 从 0的对应的  第一行 第一列 做标记
        for (int i = 1; i < row; ++i) {
            for (int j = 1; j < col; ++j) {
                if (matrix[i][j] == 0) {
                    matrix[i][0] = 0;
                    matrix[0][j] = 0;
                }
            }
        }
        dbg(matrix);
        // 填列
        for (int j = 1; j < col; ++j) {
            if (matrix[0][j] == 0) {
                for (int i = 1; i < row; ++i) {
                    matrix[i][j] = 0;
                }
            }
        }
        // 填充对应的零元素  填行
        for (int i = 1; i < row; ++i) {
            if (matrix[i][0] == 0) {
                for (int j = 1; j < col; ++j) {
                    matrix[i][j] = 0;
                }
            }
        }


        if (findZeroInFirstRow) {
            for (int j = 0; j < col; ++j) matrix[0][j] = 0;
        }
        if (findZeroInFirstCol) {
            for (int i = 0; i < row; ++i) matrix[i][0] = 0;
        }

        dbg(matrix);

    };

    answer_without_space();

    dbg(matrix);
}

void Offer::groupAnagrams() {
    // ["eat", "tea", "tan", "ate", "nat", "bat"]
    //vector<string> data = {"eat", "tea", "tan", "ate", "nat", "bat"};
    auto answer_ = [](std::vector<string> &data) -> std::vector<std::vector<string>> {
        if (data.empty()) return {};
        auto size = data.size();
        std::unordered_map<int, std::vector<int>> map;
        for (int i = 0; i < size; ++i) {
            int count = 0;
            for (char ch: data[i]) {
                count = count | (1 << (ch - 'a'));
            }
            if (map.find(count) == map.end()) {
                map[count] = std::vector<int>{i};
            } else {
                map[count].emplace_back(i);
            }
        }
        dbg(map);
        std::vector<std::vector<std::string >> result;
        result.resize(map.size());
        int curIndex = 0;
        for (const auto &cur: map) {
            const auto &ele = cur.second;
            for (const int index: ele) {
                result[curIndex].emplace_back(std::move(data[index]));
            }
            ++curIndex;
        }
        dbg(result);
        return result;

    };
//    answer_(data);
    auto answer_other = [](std::vector<string> &data) -> std::vector<std::vector<string>> {
        if (data.empty()) return {};
        auto size = data.size();

        std::unordered_map<string, std::vector<std::string>> map;
        for (int i = 0; i < size; ++i) {
            string basicString{};
            basicString.resize(26);
            for (char ch: data[i]) {
                ++basicString[ch - 'a'];
            }
            if (map.find(basicString) != map.end()) {
                map[basicString].emplace_back(std::move(data[i]));
            } else {
                map[basicString] = std::vector<string>{std::move(data[i])};
            }
        }
        std::vector<std::vector<std::string >> result;
        result.reserve(map.size());
        for (auto &&sd: map) {
            result.emplace_back(std::move(sd.second));
        }
        return result;
    };
//    std::hash<int> fn{};
//    dbg(fn(10));
//    //
    auto answer_hashmap = [](std::vector<string> data) -> std::vector<std::vector<string>> {
        std::unordered_map<std::string, std::vector<std::string >> container;
        for (std::string &cur: data) {
            auto copy = cur;
            std::sort(cur.begin(), cur.end());
            container[cur].emplace_back(std::move(copy));
        }
        std::vector<std::vector<string>> result;
        result.reserve(container.size());
        for (auto &&item: container) {
            result.emplace_back(std::move(item.second));
        }
        return result;
    };
    // 使用质数实现  设计 hash 值使得 拥有相同各个数据的数量 字符串 是一致的
    auto answer_order = [](std::vector<std::string> &data1) {
        std::vector<int> result;
        result.reserve(data1.size());
        std::array<int, 26> order = {2, 3, 5, 7, 11, 13,
                                     17, 19, 23, 29, 31, 37,
                                     41, 43, 47, 53, 59, 61,
                                     67, 71, 73, 79, 83, 89,
                                     97, 101};
        for (const auto &item: data1) {
            int t = 1;
            for (const char ch: item) {
                t *= order[ch - 'a'];
            }
            result.emplace_back(t);
        }
    };

}

void Offer::toGoatLatin() {
    //824 拉丁山羊文
    auto answer_latin = [](std::string &data) {

        std::stringstream stream(data);
        std::string word;
        int idx = 1;
        std::string result;
        while (stream >> word) {
            if (word[0] == 'a' || word[0] == 'e' || word[0] == 'i' || word[0] == 'o' || word[0] == 'u') {

            }
        }

    };
}

void Offer::wordBreak() {

    /*
     * 给你一个字符串 s 和一个字符串列表 wordDict 作为字典(包含的字符串各不相同)。请你判断是否可以利用字典中出现的单词拼接出 s 。
        注意：不要求字典中出现的单词全部都使用，并且字典中的单词可以重复使用。
        输入: s = "leetcode", wordDict = ["leet", "code"]
        输出: true
        解释: 返回 true 因为 "leetcode" 可以由 "leet" 和 "code" 拼接成。
     */

    vector<string> wordDict1 = {"leet", "code"};
    std::string cur1 = "leetcode";
    // 使用暴力递归
    auto answer_word = [](const std::vector<string> &data, std::string &word) {
        auto answer_impl = [&](int dataIndex, int wordIndex, auto answer_impl) {
            int wordSize = word.size();
            if (wordIndex == wordSize)return true;
            if (dataIndex >= data.size())return false;
            // 还有单词的长度并未匹配到
            int howManyLeft = wordSize - wordIndex;
            int curWordSize = data[dataIndex].size();
            int matchTime = howManyLeft / curWordSize;
            if (word.compare(wordIndex, curWordSize, data[dataIndex]) == 0) {
                return false;
            }
            for (int i = 0; i < matchTime; ++i) {
                if (answer_impl(dataIndex + 1, wordIndex + curWordSize * (i + 1), answer_impl))return true;
            }
            return false;
        };


    };

    // 使用字典数

    struct TrieNode {
        std::unique_ptr<TrieNode> next[26]{};
        bool isEnd = false;
    };

    // 建树
    TrieNode root;
    {
        for (const string &word: wordDict1) {
            TrieNode *p = std::addressof(root);
            for (char ch: word) {
                int curPos = ch - 'a';
                if (p->next[curPos] == nullptr) {
                    p->next[curPos] = std::make_unique<TrieNode>();
                }
                p = p->next[curPos].get();

            }
            p->isEnd = true;
        }
    }
    bool failMemo[301]{false}; //// 记录dfs中失败时对应的s中的index
    auto answer_dfs = [&failMemo](std::string &word, int startPos, const TrieNode &root, auto answer_dfs) {
        if (failMemo[startPos])return false;
        int wordSize = word.size();
        if (startPos == wordSize)return true;
        const TrieNode *p = std::addressof(root);
        for (int i = startPos; i < wordSize; ++i) {
            int curWordIndex = word[i] - 'a';
            if (p->next[curWordIndex] != nullptr) {
                p = p->next[curWordIndex].get();
                if (p->isEnd and answer_dfs(word, i + 1, root, answer_dfs))return true;
            } else break;
        }
        failMemo[startPos] = true; // 记录当前的失败的前缀
        return false;
    };

}

void Offer::containsNearbyAlmostDuplicate() {
    auto answer_ = [](vector<int> &nums, int k, int t) {
        if (nums.size() <= 1)return false;
        int left = 0;
        int right = 1;
        while (left != right and right < nums.size()) {
            if (abs(nums[left] - nums[right]) <= t) {
                return true;
            }
            if (right - left != k) { ++right; }
            else { ++left; }
        }
        return false;
    };
    vector<int> data{1, 2, 1, 1, 1};
    dbg(answer_(data, 3, 1));
}

void Offer::mergeKLists() {
    // 合并升序排序

    auto answer_ = [](vector<ListNode *> lists) {

        ListNode *result = nullptr;
        if (lists.empty()) { return result; }
        // for_each
        ListNode *cur = nullptr;
        do {
            cur = nullptr;
            int index = -1;
            int curIndex = 0;
            std::for_each(lists.begin(), lists.end(), [&](ListNode *item) {
                if (item != nullptr) {
                    if (cur == nullptr or cur->val > item->val) {
                        cur = item;
                        index = curIndex;
                    }
                    ++curIndex;

                }
            });
            if (result == nullptr) { result = cur; }
            else {
                result->next = cur;
                result = result->next;
            }
            if (curIndex != -1) { cur = cur->next; }
        } while (cur != nullptr);
        return result;
    };
}

void Offer::eightnum() {
    //  八数码

    auto impl = []() {
        string cur{"123x46758"};

        std::queue<string> queue;
        string end = "12345678x";
        std::unordered_map<string, int> result_distance;
        result_distance[cur] = 0;
        queue.push(cur);
        int x_four[4] = {-1, 0, 1, 0};
        int y_four[4] = {0, 1, 0, -1};
        while (not queue.empty()) {
            auto cur_data = queue.front();
            queue.pop();
            int dist = result_distance[cur_data];
            if (cur_data == end) return dist;
            int k = static_cast<int>(cur_data.find('x'));
            int x = k / 3;
            int y = k % 3;
            for (int i : x_four) {
                for (int j : y_four) {
                    int a = x + i;
                    int b = y + j;
                    if (x >= 0 && x <= 3 && y >= 0 && y <= 3) {
                        std::swap(cur_data[k], cur_data[a * 3 + b]);
                        if( not result_distance.count(cur_data)){
                            result_distance[cur_data] = dist + 1;
                            queue.push(cur_data);
                        }
                         std::swap(cur_data[k], cur_data[a * 3 + b]);
                    }
                }
            }
        }
        return -1;
    };

}





