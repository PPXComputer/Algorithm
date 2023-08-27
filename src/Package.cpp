//
// Created by Administrator on 2022/5/8.
//

#include "Package.h"
#include <array>
#include <dbg.h>
#include <fmt/format.h>
#include <functional>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#include <numeric>

using std::array;
using std::function;
using std::pair;
using std::string;
using std::unordered_map;
using std::vector;

void Package::pack01() {

    // 01 背包问题

    std::array values{2, 4, 4, 5, 2};
    std::array volumes{1, 2, 3, 4, 5};
    constexpr int packVolume = 10;
    {
        std::vector<std::vector<int>> dp(values.size() + 1,
                                         std::vector<int>(packVolume + 1));
        auto answer_enum = [&](int rest, int index, int count, auto answer_dfs) {
            if (rest <= 0 || index == values.size())
                return count;
            int get = 0;
            if (rest >= volumes[index]) {
                get = answer_dfs(rest - volumes[index], index + 1,
                                 count + values[index], answer_dfs);
            }
            return std::max(get, answer_dfs(rest, index + 1, count, answer_dfs));
        };
    }

    {
        // 暴力递归
        std::function<int(int, int, int)> impl
                = [&](int index, int value, int amount) {
                    if (index == volumes.size()) {
                        if (amount >= 0) {
                            return value;
                        }
                        return INT_MIN;
                    }

                    int get = impl(index + 1, value + values[index],
                                   amount - volumes[index]);
                    int not_get = impl(index + 1, value, amount);
                    return std::max(get, not_get);
                };

        impl(0, 0, packVolume);
    }
    {
        // 去除value 输入参数的暴力递归
        std::function<int(int, int)> impl = [&](int index, int bag) {
            if (bag < 0) {
                return -1;
            }
            if (index == volumes.size()) {
                return 0;
            }

            int res = impl(index + 1, bag - volumes[index]);
            if (res != -1) {
                res += values[index];
            }
            return std::max(impl(index + 1, bag), res == -1 ? 0 : res);
        };
        {
            vector<vector<int>> vt(volumes.size() + 1,
                                   vector<int>(packVolume + 1));

            for (int index = volumes.size() - 1; index >= 0; --index) {
                // std::for_each(vt[i].begin(), vt[i].begin() + volumes[i],
                // vt[i+1][]);
                for (int bag = 0; bag <= packVolume; ++bag) {
                    if (bag < volumes[index]) {
                        vt[index][bag] = vt[index + 1][bag];
                    } else {
                        vt[index][bag] = std::max(
                                values[index] + vt[index + 1][bag - volumes[index]],
                                vt[index + 1][bag]);
                    }
                }
            }
            dbg(vt[0][packVolume]);
        }

        // 只存在一层 依赖上一层
        {
            auto vt = vector<int>(packVolume + 1);
            auto vtDbg = vector<int>(packVolume + 1);
            vector<vector<int>> vtRes;
            vector<vector<int>> vtResDbg;
            for (int index = volumes.size() - 1; index >= 0; --index) {
                for (int bag = packVolume; bag >= volumes[index]; --bag) {
                    vt[bag] = std::max(values[index] + vt[bag - volumes[index]],
                                       vt[bag]);
                }
                // 依赖部分应该是没有被使用的部分  从小到大
                // 小的部分已经填上了最新的值了 所以被覆盖了 不能用
                for (int bag = volumes[index]; bag <= packVolume; ++bag) {
                    vtDbg[bag] = std::max(
                            values[index] + vtDbg[bag - volumes[index]], vtDbg[bag]);
                }
                vtRes.emplace_back(vt);
                vtResDbg.emplace_back(vtDbg);
            }
            dbg(vt[packVolume]);
            dbg(vtDbg[packVolume]);
            dbg(vtRes, vtResDbg);
        }
    }
    //
}

void Package::pack02() {

    // 选择当前的字符串
    string data = "111011"; //  转化为 A-1 B--2  Z--26

    {
        vector<string> res;

        function<void(int, const string &)> impl
                = [&](int index, const string &cur) {
                    if (index == data.size()) {
                        res.emplace_back(cur);
                        return;
                    }

                    if (index != data.size() - 1 && data[index] <= '2'
                        && data[index + 1] <= '6') {
                        char curChar
                                = (data[index] - '1') * 10 + (data[index + 1] - '1' + 'A');
                        impl(index + 2, cur + curChar);
                    }

                    char curChar = data[index] - '1' + 'A';
                    impl(index + 1, cur + curChar);
                };

        vector<int> help = vector<int>(data.size());
        help[0] = 1;
        if (data[1] == '0') {
            help[1] = 1;

            if (data[0] >= '3') {
                help[1] = 0;
            }
        } else {
            if (data[0] <= '2' && data[1] <= '6') {
                help[1] = 2;
            } else {
                help[1] = 1;
            }
        }

        size_t size = data.size();
        for (size_t i = 2; i < size; ++i) {
            if (data[i] == '0') {

                if (data[i - 1] == '2' || data[i - 1] == '1') {
                    help[i] = help[i - 2];
                } else {
                    help[i] = 0;
                }
            } else {
                if (data[i - 1] <= '2' && data[i] <= '6') {
                    help[i] = help[i - 2] + help[i - 1];
                } else {
                    help[i] = help[i - 1];
                }
            }
        }
        dbg(help);
    }
    // 结果是res的长度

    {
        function<int(int, const string &)> impl2
                = [&](int index, const string &cur) {
                    if (index == data.size()) {
                        return 1;
                    }
                    if (cur[index] == '0') {
                        return 0;
                    }

                    int way = impl2(index + 1, cur);

                    if (index + 1 < data.size()
                        && (cur[index] - '0') * 10 + cur[index + 1] - '0' < 27) {
                        way += impl2(index + 2, cur);
                    }
                    return way;
                };

        size_t dataSize = data.size();
        vector<int> help = vector<int>(dataSize + 1);
        help[dataSize] = 1;
        for (int i = dataSize - 1; i >= 0; i--) {
            char curChar = data[i];
            if (curChar == '0') {
                help[i] = 0;
            } else if (curChar == '1' || curChar == '2') {
                help[i] = help[i + 1];
                if (i + 1 < dataSize
                    && ((curChar - '0') * 10 + data[i + 1] - '0') < 27) {
                    help[i] += help[i + 2];
                }
            } else {
                help[i] = help[i + 1];
            }
        }
    }
}

void Package::pack03() {
    string str{"babac"};
    vector<string> arr{"ba", "c", "abcd"};

    array<int, 26> state{};
    for (char a: str) {
        ++state[a - 'a'];
    }
    auto minus = [](array<int, 26> preState, const string &curStr) {
        bool isMinus = false;
        for (char i: curStr) {
            int stateIndex = i - 'a';
            if (preState[stateIndex] > 0) {
                --preState[i - 'a'];
                isMinus = true;
            }
        }
        return std::make_pair(isMinus, preState);
    };
    auto equalTOZero = [](int a) { return a == 0; };
    // 最少需要多少张
    function<int(const array<int, 26> &)> impl
            = [&](const array<int, 26> &curState) {
                if (std::all_of(curState.begin(), curState.end(), equalTOZero)) {
                    return 0;
                }

                int res = INT_MAX;

                // 可以挑选无数张贴纸
                for (const string &arrStr: arr) {

                    auto [isMinus, newState] = minus(curState, arrStr);

                    if (isMinus) {
                        res = std::min(res, impl(newState));
                    }
                }
                return res + ((res == INT_MAX) ? 0 : 1);
            };

    size_t arrSize = arr.size();
    vector<array<int, 26>> stickers = vector<array<int, 26>>(arrSize);

    for (size_t i = 0; i < arrSize; i++) {
        for (char a: arr[i]) {
            ++stickers[i][a - 'a'];
        }
    }

    array<int, 26> curState{};
    unordered_map<string, int> cache;
    function<int(const string &)> impl2 = [&](const string &rest) {
        if (rest.empty()) {
            return 0;
        }
        if (auto findIter = cache.find(rest); findIter != cache.end()) {
            return findIter->second;
        }
        curState.fill(0);

        for (char a: rest) {
            ++curState[a - 'a'];
        }
        int minCount = INT_MAX;
        for (size_t i = 0; i < arrSize; i++) {

            char firstChar = rest.front();
            //  当前的i号贴纸 保护了第一个元素
            if (stickers[i][firstChar - 'a'] > 0) {
                string res;
                for (size_t j = 0; j < 26; ++j) {
                    if (curState[j] > 0) {
                        int countRes = curState[j] - stickers[i][j];
                        if (countRes > 0) {
                            res.append(countRes, 'a' + j);
                        }
                    }
                    minCount = std::min(minCount, impl2(res));
                }
            }
        }
        int lastAnwser = minCount + (minCount == INT_MAX ? 0 : 1);
        cache[rest] = lastAnwser;
        return lastAnwser;
    };
}

void Package::longestCommntSub() {
    /// 最长公共子序列

    string str1 = "assda1231asd";
    string str2 = "a43cw123asd";

    // str1 [0...i]
    // str2 [0...j]
    // 以 i j 结尾的最长公共子序列长度
    function<int(int, int)> impl = [&](int i, int j) {
        if (i == 0 && j == 0) {
            return str1[i] == str2[j] ? 1 : 0;
        } else if (j == 0) {
            if (str1[i] == str2[j]) {
                return 1;
            } else {
                return impl(i - 1, 0);
            }
        } else if (i == 0) {
            if (str1[i] == str2[j]) {
                return 1;
            } else {
                return impl(0, j - 1);
            }
        }

        int p1 = impl(i - 1, j); // 可能以i结尾在公共子序列部分
        int p2 = impl(i, j - 1); // 可能以j结尾在公共子序列部分
        int p3 = str1[i] == str2[j] ? 1 + impl(i - 1, j - 1) : 0;
        return std::max({p1, p2, p3});
    };
    {
        vector<vector<int>> help(str1.size(), vector<int>(str2.size()));
        help[0][0] = str1[0] == str2[0] ? 1 : 0;
        for (size_t i = 1; i < str1.size(); ++i) {
            help[i][0] = str1[i] == str2[0] ? 1 : help[i - 1][0];
        }
        for (size_t j = 1; j < str2.size(); ++j) {
            help[0][j] = str1[0] == str2[j] ? 1 : help[0][j - 1];
        }
        for (size_t i = 1; i < str1.size(); i++) {
            for (size_t j = 1; j < str2.size(); j++) {
                int endWithIJ = str1[i] == str2[j] ? 1 + help[i - 1][j - 1] : 0;
                help[i][j]
                        = std::max({endWithIJ, help[i - 1][j], help[i][j - 1]});
            }
        }
        int res = help[str1.size()][str2.size()];
        dbg(res);
    }
}

void Package::uniquePathsWithObstacles() {
    vector<vector<int>> obstacleGrid = {
            {0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0},
            {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1},
            {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
            {0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0},
            {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 1},
            {0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0},
            {1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0},
            {0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1},
            {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0},
            {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
            {0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
            {0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
            {0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
            {0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0},
            {0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}

    };
    int row = obstacleGrid.size();
    int col = obstacleGrid.front().size();
    auto help = vector<vector<int>>(row, vector<int>(col));
    help[row - 1][col - 1] = 1;
    for (int j = col - 2; j >= 0 && obstacleGrid[row - 1][j] == 0; --j) {
        help[row - 1][j] = 1;
    }
    for (int i = row - 2; i >= 0 && obstacleGrid[i][col - 1] == 0; --i) {
        help[i][col - 1] = 1;
    }
    for (int i = row - 2; i >= 0; --i) {
        for (int j = col - 2; j >= 0; --j) {
            if (obstacleGrid[i][j] == 0) {
                if (help[i + 1][j] == 601603968) {
                    dbg(help[i][j + 1]);
                }
                help[i][j] = help[i + 1][j] + help[i][j + 1];
            }
        }
    }
    dbg(help[0][0]);
}

void Package::jump() {
    // 象棋马在(0,0) 跳到(x,y)  k步下有多少中方法

    constexpr int targetX = 2;
    constexpr int targetY = 1;
    constexpr int targetK = 5;
    constexpr array<pair<int, int>, 8> forward{
            pair<int, int>{2, 1},
            {-2, 1},
            {-2, -1},
            {2, -1},
            {1, 2},
            {1, -2},
            {-1, -2},
            {-1, 2}
    };
    function<int(int, int, int)> impl = [&](int k, int x, int y) {
        if (k == 0) {
            return (targetX == x && targetY == y) ? 1 : 0;
        }

        if (y < 0 || x < 0 || x > 9 || y > 10) {
            return 0;
        }

        if (k * 2 + x < targetX || k + y < targetY || targetX + 2 * k < x || targetY + k < y) {
            return 0;
        }
        int res = 0;

        for (const auto a: forward) {
            res += impl(k - 1, x + a.first, y + a.second);
        }
        return res;
    };

    dbg(impl(targetK, 0, 0));
}

void Package::integerBreak() {

    function<int(int)> impl = [&](int cur) {
        if (cur == 1) {
            return 1;
        }
        int res = INT_MIN;
        for (int i = 1; i < cur; ++i) {
            res = std::max(res, impl(cur - i) * i);
        }
        return res;
    };
    vector<int> help = vector<int>(59);
    help[1] = 1;
    for (int cur = 2; cur <= 58; ++cur) {
        int res = INT_MIN;

        for (int i = 1; i < cur; ++i) {
            if (cur == 10) {
                dbg(i, cur - i, help[cur - i], res);
            }
            res = std::max(res, help[cur - i] * i);
        }
        help[cur] = res;
    }

    fmt::print("{}", fmt::join(help, ","));
    for (int i = 1; i < 12; i++) {
        dbg(i, impl(i)); // 1 1 2 3 4 6 9 12 18 27 36
    }
}

void Package::numTrees() {
    int n = 12;
    if (n == 1) {
        dbg(1);
    } else if (n == 2) {
        dbg(2);
    } else if (n == 3) {
        dbg(5);
    }
    vector<int> help(n);
    help[0] = 1;
    help[1] = 2;
    help[2] = 5;
    for (int i = 4; i <= n; ++i) {
        // 1 2 3 4
        // 1 (2 3 4 )
        // (1) 2 (3,4)
        // (1,2) 3 (4)
        // (1,2,3,)4
        int res = help[i - 2] * 2;
        for (int j = 2; j < i; ++j) {
            res += help[j - 2] * help[i - 1 - j];
        }
        help[i - 1] = res;
    }
    dbg(help[n - 1]);
}

void Package::findMaxForm() {
    std::array<string, 5> strs{"10", "0001", "111001", "1", "0"};
    constexpr int m = 5;
    constexpr int n = 3;

    vector<vector<vector<int>>> memo(strs.size() + 1, vector<vector<int>>(m + 1, vector<int>(n + 1, -1)));
    std::function<int(int, int, int)> max_len = [&](int size, int i, int j) -> int {
        if (size == strs.size()) {
            dbg(fmt::format("size: {} i: {} j: {}", size, i, j));
            memo[size][i][j] = 0;
            return 0;
        }
        const auto curStr = strs[size];
        int curM = 0;
        int curN = 0;
        for (char a: strs[size]) {
            if (a == '0') {
                ++curM;
            } else {
                ++curN;
            }
        }

        if (i + curM > m || j + curN > n) {
            dbg(fmt::format("size: {} i: {} j: {}", size + 1, i, j));
            memo[size][i][j] = max_len(size + 1, i, j);
        } else {
            dbg(fmt::format("size: {} i: {} j: {}  size+1:{} i+curM:{} j+curN:{}",
                            size + 1, i, j, size + 1, i + curM, j + curN));
            memo[size][i][j] = std::max(max_len(size + 1, i, j), max_len(size + 1, i + curM, j + curN) + 1);
        }

        return memo[size][i][j];
    };
    max_len(0, 0, 0);
    for (size_t i = 0; i < memo.size(); i++) {
        dbg(i);
        for (const auto &vec: memo[i]) {
            dbg(vec);
        }
    }

    vector<vector<int>> help(m + 1, vector<int>(n + 1));
    for (int size = strs.size() - 1; size >= 0; --size) {
        // f(size-1 , i,j)= max(f(size ,i+strs[c],n+strs[c],f(size,i,j)));
        int curM = 0;
        int curN = 0;
        for (char a: strs[size]) {
            if (a == '0') {
                ++curM;
            } else {
                ++curN;
            }
        }
        for (int i = m - curM; i >= 0; --i) {
            for (int j = n - curN; j >= 0; --j) {

                help[i][j] = std::max(help[i + curM][j + curN] + 1, help[i][j]);
            }
        }
    }
}

void Package::pack_416() {
    vector<int> data{1, 5, 11, 12, 123};
    auto impl = [&data]() {

        int sum = std::accumulate(data.begin(), data.end(), 0);
        if (sum % 2 == 1) {
            return false;
        }
        int target = sum / 2;

        std::function<bool(int, int)> dfs_impl = [&](int index, int curSum) -> bool {
            if (curSum == target) {
                return true;
            }
            if (index == data.size() or curSum > target) {
                return false;
            }
            return dfs_impl(index + 1, curSum + data[index]) or dfs_impl(index + 1, curSum);
        };

        auto first_ans = dfs_impl(0, 0);
        vector<vector<int>> dp(data.size(), vector<int>(target + 1));
        for (int i = 0; i < data.size(); ++i) {
            dp[i][target] = 1;
        }
        // 下列循环有可能会溢出size_t 修改为int
        for (int row = static_cast<int>(data.size()) - 2; row >= 0; --row) {
            for (int col = 0; col < target; ++col) {
                if (col + data[row] > target) {
                    dp[row][col] = dp[row + 1][col];
                } else {
                    dp[row][col] = dp[row + 1][col] or dp[row + 1][col + data[row]];
                }
            }
        }
        auto second_ans = dp[0][0];
        //  修改成一维数组
        vector<int> dp2(target + 1);
        dp2[target] = 1;
        for (int row = static_cast<int>(data.size()) - 2; row >= 0; --row) {
            for (int col = 0; col < target; ++col) {
                if (col + data[row] <= target) {
                    dp2[col] = std::max(dp2[col], dp2[col + data[row]]);
                }
            }
        }

        auto third_ans = dp2[0];
        // 如果需要三者都相等要不然debug打印
        if (third_ans != second_ans or second_ans != first_ans or first_ans != third_ans) {
            dbg(third_ans, second_ans, first_ans);
        }
        return first_ans;
    };
    impl();

}

void Package::pack_1049() {
    // 能组成不超过给定值的最大数
    vector<int> data{1, 2, 3, 4};
    auto impl = [&] {
        if (data.size() == 1) {
            return data.front();
        }
        int sum = std::accumulate(data.begin(), data.end(), 0);
        int target = sum / 2;

        std::function<int(int, int)> dfs_impl = [&](int index, int value) -> int {
            if (value > target) {
                return INT_MIN;
            }
            if (index == data.size()) {
                return value;
            }

            return std::max(dfs_impl(index + 1, value), dfs_impl(index + 1, value + data[index]));
        };

        auto first_ans = sum - 2 * dfs_impl(0, 0);

        vector<vector<int>> dp2(data.size(), vector<int>(target + 1));
        vector<int> &back = dp2.back();
        for (int j = 1; j <= target; ++j) {
            back[j] = j;
        }

        for (int row = static_cast<int>(data.size()) - 2; row >= 0; --row) {
            for (int col = 0; col <= target; ++col) {
                if (col + data[row] > target) {
                    dp2[row][col] = dp2[row + 1][col];
                } else {
                    dp2[row][col] = std::max(dp2[row + 1][col], dp2[row + 1][col + data[row]]);
                }
            }
        }
        dbg(dp2);
        auto second_ans = sum - 2 * dp2[0][0];
        //  修改成一维数组
        vector<int> dp3(target + 1);
        vector<int> &back2 = dp3;
        for (int j = 1; j <= target; ++j) {
            back2[j] = j;
        }
        for (int row = static_cast<int>(data.size()) - 2; row >= 0; --row) {
            dbg(dp3);

            for (int col = 0; col <= target; ++col) {
                if (col + data[row] <= target) {
                    dp3[col] = std::max(dp3[col], dp3[col + data[row]]);
                }
            }

        }
        auto third_ans = sum - 2 * dp3[0];
        // 如果需要三者都相等要不然debug打印
        if (third_ans != second_ans or second_ans != first_ans or first_ans != third_ans) {
            dbg(third_ans, second_ans, first_ans);
        }
        return first_ans;
    };
    impl();
}

void Package::pack_494() {
    vector<int> data{1, 1, 1, 1, 1};
    int target = 3;
    //  有多少种方法使得和为target
    auto impl = [&] {
        auto size = static_cast<int>(data.size());
        std::function<int(int, int)> dfs_impl = [&](int index, int curSum) -> int {
            if (index == size) {
                return curSum == target ? 1 : 0;
            }
            return dfs_impl(index + 1, curSum + data[index]) + dfs_impl(index + 1, curSum - data[index]);
        };
        int first_ans = dfs_impl(0, 0);
        int sum = std::accumulate(data.cbegin(), data.cend(), 0);
        int target_len = 2 * sum;
        auto dp2 = vector<vector<int>>(size + 1, vector<int>(target_len + 1));
        dp2.back()[target + sum] = 1;
        int dataSize = static_cast<int>(size);
        for (int row = dataSize - 1; row >= 0; --row) {
            for (int col = 0; col <= target_len; ++col) {
                int rightPos = col + data[row];
                int right = rightPos <= target_len ? dp2[row + 1][rightPos] : 0;
                int leftPos = col - data[row];
                int left = leftPos >= 0 ? dp2[row + 1][leftPos] : 0;
                dp2[row][col] = left + right;
            }
        }
        dbg(dp2);
        auto second_ans = dp2[0][sum];
        //  修改成一维数组
        vector<int> dp3(2 * sum + 1);
        dp3[target + sum] = 1;
        vector<int> dp3_copy = dp3;

        for (int row = dataSize - 1; row >= 0; --row) {
            for (int col = 0; col <= 2 * sum; ++col) {
                int left = col - data[row] >= 0 ? dp3_copy[col - data[row]] : 0;
                int right = col + data[row] <= 2 * sum ? dp3_copy[col + data[row]] : 0;
                dp3[col] = left + right;
            }
            dbg(dp3, dp3_copy);
            swap(dp3, dp3_copy);
        }
        auto third_ans = dp3_copy[sum];
        // 如果需要三者都相等要不然debug打印
        if (third_ans != second_ans or second_ans != first_ans or first_ans != third_ans) {
            dbg(third_ans, second_ans, first_ans);
        }

        int origin_all = target + sum;
        if (origin_all % 2 == 1) {
            auto fourth_ans = 0;
        }
        int postivate = origin_all / 2;
        std::function<int(int, int)> dfs_pos = [&](int index, int curSum) {
            if (index == size) {
                return curSum == postivate ? 1 : 0;
            }
            return dfs_pos(index + 1, curSum) + dfs_pos(index + 1, curSum + data[index]);
        };
        auto fourth_ans = dfs_pos(0, 0);
        auto dp_pos = vector<int>(postivate + 1);
        dp_pos[postivate] = 1;
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j <= postivate; ++postivate) {
                int right = j + data[i] <= postivate ? dp_pos[j + data[i]] : 0;
                dp_pos[j] += right;
            }
        }
        auto five_ans = dp_pos[0];
        // 如果需要五者都相等要不然debug打印
        if (five_ans != fourth_ans or fourth_ans != third_ans
            or third_ans != second_ans or second_ans != first_ans or first_ans != five_ans) {
            dbg(five_ans, fourth_ans, third_ans, second_ans, first_ans);
        }
    };
    impl();

}

