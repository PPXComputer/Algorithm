//
// Created by 破忆断回 on 2021/9/25.
//

#include "StringAlgo.h"
#include <dbg.h>
#include <folly/FBString.h>
#include <folly/FBVector.h>
#include<folly/String.h>
#include <folly/container/F14Set.h>
#include<iostream>
#include<unordered_map>
#include<utility>

using std::cout;
using folly::StringPiece;
using folly::F14FastSet;
using folly::fbstring;
using folly::fbvector;

inline fbstring StringAlgo::sub_string_range() {
    fbstring str = "364210432182613";
    fbstring target = "321";
    int need_match_num = static_cast<int>(target.length());// 需要匹配的数目
    if (need_match_num == 0) {
        return {};
    }
    std::unordered_map<char, int> map;
    for (char c: target) {
        map[c]++; //note 填入表格
    }

    int range_start = 0;
    int range_end = 0;
    std::pair<int, int> result = {0, str.length()};
    size_t str_length = str.size();
    for (size_t index = 0; index < str_length; index++) {
        char cur = str[index];
        if (bool match_char = map.find(cur) != map.end(); match_char) {
            map[cur] -= 1; //遇到则直接消除
            need_match_num -= 1;
        }
        //此次将匹配到所有字符 将确定右侧位置
        if (bool get_all_chars = need_match_num <= 0; get_all_chars) {
            range_end = static_cast<int> (index);
            // 移动 左侧 将填入相关值
            while (range_start < range_end) {
                auto iterator = map.find(str[range_start]);
                // note 当前的数据并不是需要匹配的数据 或者 虽说匹配但之后 当前的数据仍有多余
                if (iterator == map.end()) {
                    range_start += 1;
                } else {
                    if (iterator->second < 0) {
                        iterator->second += 1;
                        range_start += 1;
                    } else break;
                }
            }
            if (range_end - range_start < result.second - result.first) {
                result.first = range_start;
                result.second = range_end;
            }
        }
    }
    // note 当前的最后一个元素也应该填入
    return {str.begin() + result.first, str.begin() + result.second + 1};
}

inline void StringAlgo::all_sub() {
    // 打印所有的子序列
    fbstring data = "12345";
    printAll("", 0, data);

}

inline size_t StringAlgo::exp_n(int n) {
    std::function<size_t(int)> imp = [&](int cur) -> size_t {
        if (cur == 1)return 1l;
        return cur * imp(cur - 1);
    };
    return imp(n);
}

void StringAlgo::string_compress() {
    fbstring data = "12001";
    fbstring::size_type len = data.size();
    std::array num = {'w', 'q', 'b', 's'};
    fbstring result;
    result.append({data.front(), num[0]});
    if (len > 2) {
        bool find_zero = false;
        for (int index = 1; index < len; index++) {
            fbstring::const_reference cur = data.at(index);
            if (cur != '0') {
                if (find_zero) {
                    if (index == len - 1) {
                        result.append({'L', cur});
                    } else {
                        result.append({'L', cur, num[index]});
                    }
                    find_zero = false;
                } else {
                    if (index == len - 1) {
                        result.append({cur});
                    } else
                        result.append({cur, num[index]});
                }
            } else
                find_zero = true;
        }

    }

    cout << fmt::format("result {}", result);
}

void StringAlgo::string_expression() {
    std::array data = {1, 2, 2, 5, 8};
    std::function<int(const int)> impl = [&](const int index) -> int {
        size_t len = data.size();
        if (index == len)
            return 1; //都选择完成了当前算一个情况
        if (data.at(index) == 0) //当前是一个零
            return 0;
        int result = impl(index + 1);// 当前作为一个字符
        if (index + 1 == len) //已经是最后一个字符了
            return result;

        auto concat_value = data.at(index) * 10 + data.at(index + 1);
        if (index + 1 < len && concat_value < 27) {
            result += impl(index + 2);
        }
        return result;
    };
    cout << impl(0);
    const auto &dpImpl = [&data](int index) {
        if (data.at(index) == 0)return 0;
        size_t len = data.size();
        fbvector<int> dp(len + 1);
        dp[len] = 1;
        return dp[data.size()];
    };

}

void StringAlgo::find_longest_not_repeat_sub() {
    // 找到最长未出现的连续子串
    std::array<int, 256> data{};
    std::fill(data.begin(), data.end(), -1);
    fbstring str = R"(assdgdhkasdgftyzxcyt)";

    int result_len = 0;
    int interval = 0;
    int pre = -1;// 判断当前可以判断的字符起始位置在哪里
    fbstring::size_type size = str.size();
    //如果以当前字符结尾的情况下 将获得最长的间隔为多少
    for (size_t i = 0; i < size; i++) {
        // 当前的起始位置 要不就是与上一次一致  要不然就是上一次出现当前字符的位置
        pre = std::max(pre, data[static_cast<size_t>(str[i])]);
        // 当前可以达到的最大长度为
        interval = i - pre;
        dbg(interval,
            folly::StringPiece(str.begin() + i + 1 - interval, str.begin() + i + 1), "\n");
        result_len = std::max(interval, result_len);
        data[str[i]] = i;

    }


}

void StringAlgo::string_replace() {
    // 从字符串str1 到 str2 提供 插入 删除 修改的代价为 ic dc rc 
    // 得到最小的代价
    fbstring first = "asd";
    fbstring second = "aad";
    auto dp = fbvector<fbvector<int>>(first.size() + 1, fbvector<int>(second.size() + 1));
    int ic = 5;
    int dc = 11;
    int rc = 7;
    size_t front_size = dp.front().size();
    for (size_t i = 0; i < front_size; i++) {
        dp[0][i] = i * ic; // 从空字符变成当前的字符串 需要多少个插入代价
    }
    size_t row_size = dp.size();
    for (size_t i = 0; i < row_size; i++) {
        dp[i][0] = i * dc; // 从当前的字符串变成空字符 需要多少个删除代价
    }
    fbstring::size_type first_size = first.size();
    fbstring::size_type second_size = second.size();
    for (size_t x = 1; x < first_size; x++) {
        for (size_t y = 1; y < second_size; y++) {
            if (first[x] == second[y]) {
                // 当前字符相等的情况下 情况与 dp[x-1][y-1]所耗费的代价相同
                dp[x][y] = dp[x - 1][y - 1];
            } else {
                dp[x][y] = dp[x - 1][y - 1] + rc;// 否则就是的改一个字符代价
            }
            dbg(dp[x - 1][y] + dc, dp[x][y - 1] + ic, dp[x][y]);

            dp[x][y] = std::min({dp[x - 1][y] + dc, dp[x][y - 1] + ic, dp[x][y]});
        }
    }
}

void StringAlgo::boolean_expression() {
    // 有关当前的 布尔表达式的运算过程

    fbstring expression = "1^0|0|1";

    std::function<int(bool, int, int)> impl = [&](
            bool desired, int left, int right) -> int {
        if (left == right) {
            if (expression[left] == '1')
                return desired ? 1 : 0;
            else
                return desired ? 0 : 1;
        }
        int result = 0;
        if (desired)
            // 偶数位才是当前的运算符
        {
            for (int i = left + 1; i < right; i += 2) {
                dbg(desired);
                dbg(expression[i],
                    folly::StringPiece(expression.begin(), expression.begin() + i));
                dbg(folly::StringPiece(expression.begin() + i + 1, expression.begin() + right));
                switch (expression[i]) {
                    case '^':
                        result += impl(false, left, right - 1) *
                                  impl(true, left + 1, right);
                        result += impl(true, left, right - 1) *
                                  impl(false, left + 1, right);
                        break;
                    case '|':
                        result += impl(false, left, right - 1) *
                                  impl(true, left + 1, right);
                        result += impl(true, left, right - 1) *
                                  impl(false, left + 1, right);
                        result += impl(true, left, right - 1) *
                                  impl(true, left + 1, right);
                        break;
                    case '&':
                        result += impl(true, left, right - 1) *
                                  impl(true, left + 1, right);
                        break;
                    default:
                        break;
                }
            }
        } else {
            // 偶数位才是当前的运算符
            for (int i = left + 1; i < right; i += 2) {
                dbg(desired);
                dbg(expression[i],
                    folly::StringPiece(expression.begin(), expression.begin() + i));
                dbg(folly::StringPiece(expression.begin() + i + 1, expression.begin() + right));
                switch (expression[i]) {
                    case '^':
                        result += impl(true, left, right - 1) *
                                  impl(true, left + 1, right);
                        result += impl(false, left, right - 1) *
                                  impl(false, left + 1, right);
                        break;
                    case '|':
                        result += impl(false, left, right - 1) *
                                  impl(false, left + 1, right);
                        break;
                    case '&':
                        result += impl(true, left, right - 1) *
                                  impl(false, left + 1, right);
                        result += impl(false, left, right - 1) *
                                  impl(true, left + 1, right);
                        result += impl(false, left, right - 1) *
                                  impl(false, left + 1, right);
                        break;
                    default:
                        break;
                }
            }
        }

        return result;
    };
    impl(false, 0, expression.size() - 1);

}

void StringAlgo::expression() {
    fbstring str1 = "48*((70-65)-43)+8*1";
    fbstring str2 = "3+1*4";
    struct StrResult {
        int find_right_bracket; //遇到右括号 或者终止
        int end_position;
    };

    auto dfs = [&str1](int start, int cur, auto &&dfs) -> StrResult {
        fbvector<int> stack(str1.size()); //stack 存储当前的表达式
        // 按照当前的进栈规则行进

        while (start != str1.size() && str1[start] != '}') {
        }

        // stack  Manipulate



    };


}

inline void StringAlgo::printAll(const folly::fbstring &cur,
                                 size_t index, const folly::fbstring &data) {
    if (index == data.size()) {
        cout << cur << '\n';
        return;
    }
    printAll(cur + data[index], index + 1, data);
    printAll(cur, index + 1, data);
}

void StringAlgo::wordBreak() {

    std::string cur = "pineapplepenapple";
    std::unordered_set<std::string> wordDict{"apple", "pen", "applepen", "pine", "pineapple"};

    folly::fbvector<folly::fbstring> rst;
    std::function<void(StringPiece, std::string &)> can
            = [&](StringPiece piece, std::string &t) {
                if (piece.empty()) {
                    rst.emplace_back(t);
                    dbg(t);
                    return;
                }
                for (const auto &str: wordDict) {
                    if (piece.startsWith(str)) {
                        t += " " + str;
                        dbg(piece.size(), str.size(), folly::join("", piece), str);
                        can(piece.subpiece(str.length()), t);
                    }
                }
            };
    std::string tmp;
    can(cur, tmp);
    dbg(folly::join("---", rst));
}

void StringAlgo::searchWord() {
    std::array<std::array<char, 4>, 4> board = {std::array<char, 4>
                                                        {'o', 'a', 'a', 'n'},
                                                {'e', 't', 'a', 'e'},
                                                {'i', 'h', 'k', 'r'},
                                                {'i', 'f', 'l', 'v'}};
    std::array<fbstring, 4> words{"oath", "pea", "eat", "rain"};
    std::array<std::tuple<int, int>, 4> pos = {std::tuple<int, int>{0, 1},
                                               {1, 0},
                                               {-1, 0},
                                               {0, -1}};
    folly::F14ValueSet<int> rst;
    int size = board.size();
    const auto impl = [&](int x, int y, int count, int wordIndex, auto &&impl) -> void {
        if (x < 0 || x >= size || y < 0 || y >= size) {
            return;
        }
        if (wordIndex == -1) {
            for (int i = 0, wordSize = words.size(); i < wordSize; ++i) {
                const auto &ref = words[i];
                if (ref[0] == board[x][y]) {
                    for (auto [xInc, yInc]: pos) {
                        impl(x + xInc, y + yInc, count + 1, i, impl);
                    }
                }
            }
        } else {
            if (count == words[wordIndex].size()) {
                rst.insert(wordIndex);
            } else {

            }
        }
    };

}

void StringAlgo::minWindows() {
    // 76最小覆盖子串

    fbstring str{"aa"};
    fbstring pattern{"aa"};
    int resLen = INT_MAX;
    int resStart = 0;
    int left = 0;
    int right = 0;

    auto patternSize = pattern.size();
    std::unordered_map<char, int> need;
    need.reserve(patternSize);

    for (char a: pattern) {
        need[a]++;
    }

    std::unordered_map<char, int> windows;
    windows.reserve(patternSize);
    auto originSize = str.size();
    auto needSize = need.size();
    int vailEleCount = 0; //来计算当前有多少个字符匹配成功
    while (right < originSize) {

        char curRightEle = str[right];
        right++;
        if (need.count(curRightEle)) {
            windows[curRightEle]++;
            // 如果重复元素进行添加则可能出现 aa  +1  +2的情况
            // 我们只认定当前 need['a']=2   == windows['a']=2 的情况
            if (need[curRightEle] == windows[curRightEle]) {
                ++vailEleCount;
            }
        }
        while (vailEleCount == needSize) {
            if (right - left < resLen) {
                resLen = right - left;
                resStart = left;
            }
            char curLeftEle = str[left];
            ++left;
            if (need.count(curLeftEle)) {
                if (need[curLeftEle] == windows[curLeftEle]) {
                    --vailEleCount;
                }
                windows[curLeftEle]--;
            }
        }
    }
    auto res = resLen != INT_MAX ? str.substr(resStart, resLen) : fbstring{};

}

void StringAlgo::findRepeatedDnaSequences() {
    fbstring s{"AAAAAAAAAAAAA"};
    int sSize = s.size();

    std::unordered_set<int> mSet;
    mSet.reserve(sSize);
    int cur = 0;
    const auto curCharNumber = [](char a) {
        switch (a) {
            case 'A':
                return 3;
            case 'C':
                return 1;
            case 'G':
                return 2;
            default:
                return 0;
        }
    };
    for (int i = 0; i < 10; ++i) {
        cur = cur * 4 + curCharNumber(s[i]);

    }

    mSet.insert(cur);
    int pow1 = std::pow(4, 9);
    std::vector<std::string> res; //这个结构需要去重吗?
    for (int i = 1; i + 10 <= sSize; ++i) {
        // 向前一步 则高位去掉一个位 低位添加一位

        cur = cur - (curCharNumber(s[i - 1]) * pow1);
        dbg(cur);
        cur = cur * 4 + curCharNumber(s[i + 9]);
        dbg(cur);
        dbg(mSet);
        if (! mSet.insert(cur).second) {
            res.emplace_back(s.substr(i, 10));
        }
    }
    dbg(res);

}

void StringAlgo::Rabin_Karp() {

    fbstring txt;
    fbstring pattern;
    auto patternSize = pattern.size();
    if (txt.size() < patternSize)return;
    // 取一个比较大的素数作为求模的除数
    int Q = 1658598167;  //设计的余数   %Q 作为hash 函数 用于处理可能溢出的结果
    int base = 256;// 进制数
    long RL = 1;
    for (int i = 1; i <= patternSize - 1; i++) {  // note 这里是 patterSize -1  因为三位数则 需要减掉 二位^base
        // 计算过程中不断求模，避免溢出
        RL = (RL * 256) % Q;
    }
    int windowsHash = 0;
    int left = 0;
    int right = 0;


    int patterHash = 0;  // 获得模式串的hash值
    for (int i = 0; i < patternSize; ++i) {
        patterHash = ((patterHash * base) % Q + pattern[i]) % Q;
    }
    std::unordered_set<int> res;
    while (right < txt.size()) {
        windowsHash = ((windowsHash * base) % Q + txt[right]) % Q;  //cur*base 后进行加的操作可能会出现溢出的操作所以先处理溢出数
        right++;
        if (right - left == patternSize) {
            if (windowsHash == patterHash) {
                // 出现重复的hash 值

                //需要进一步判断当前是否发生了 一个hash 值对应多个的情况
                if (! std::equal(pattern.begin(), pattern.end(), txt.begin() + left, txt.begin() + right)) {
                    // 没有重复记录当前位置
                    res.insert(left);
                }

            }
            // X % Q == (X + Q) % Q 是一个模运算法则
            // 因为 windowHash - (txt[left] * RL) % Q 可能是负数
            // 所以额外再加一个 Q，保证 windowHash 不会是负数
            windowsHash = ((windowsHash - txt[left] * RL) % Q + Q) % Q;
        }
        left++;

    }
    //res;

}
