//
// Created by 破忆断回 on 2021/9/25.
//

#include "../include/StringAglo.h"
#include <dbg.h>

inline fbstring StringAglo::sub_string_range() {
    fbstring str = "364210432182613";
    fbstring target = "321";
    int need_match_num = static_cast<int>(target.length());// 需要匹配的数目
    if (need_match_num == 0) {
        return {};
    }
    std::unordered_map<char, int> map;
    for (char c : target) {
        map[c]++; //note 填入表格
    }

    int range_start = 0;
    int range_end = 0;
    std::pair<int, int> result = { 0, str.length() };
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
                }
                else {
                    if (iterator->second < 0) {
                        iterator->second += 1;
                        range_start += 1;
                    }
                    else break;
                }
            }
            if (range_end - range_start < result.second - result.first) {
                result.first = range_start;
                result.second = range_end;
            }
        }
    }
    // note 当前的最后一个元素也应该填入
    return { str.begin() + result.first, str.begin() + result.second + 1 };
}

inline void StringAglo::all_sub() {
    // 打印所有的子序列
    fbstring data = "12345";
    printAll("", 0, data);

}

inline size_t StringAglo::exp_n(int n) {
    const auto& imp = [](int cur, auto&& self)->size_t {
        if (cur == 1)return 1l;
        return cur * self(cur - 1, self);
    };
    return imp(n, imp);
}

void StringAglo::string_compress()
{
	fbstring data = "12001";
	fbstring::size_type len = data.size();
	std::array num = { 'w', 'q', 'b', 's' };
	fbstring result;
	result.append({ data.front(), num[0] });
	if (len > 2) {
		bool find_zero = false;
		for (int index = 1; index < len; index++) {
			fbstring::const_reference cur = data.at(index);
			if (cur != '0') {
				if (find_zero) {
					if (index == len - 1) {
						result.append({ 'L', cur });
					}
					else {
						result.append({ 'L', cur, num[index] });
					}
					find_zero = false;
				}
				else {
					if (index == len - 1) {
						result.append({ cur });
					}
					else
						result.append({ cur, num[index] });
				}
			}
			else
				find_zero = true;
		}

	}

	cout << fmt::format("result {}", result);
}

void StringAglo::string_expression()
{
	std::array data = { 1, 2, 2, 5, 8 };
	const auto& impl = [&data](const int index, auto&& impl) -> int {
		size_t len = data.size();
		if (index == len)
			return 1; //都选择完成了当前算一个情况
		if (data.at(index) == 0) //当前是一个零
			return 0;
		int result = impl(index + 1, impl);// 当前作为一个字符
		if (static_cast<unsigned long long>(index) + 1 == len) //已经是最后一个字符了
			return result;

		auto concat_value = data.at(index) * 10 + data.at(static_cast<std::array<std::_Enforce_same<int, int, int, int, int>::type, 5Ui64>::size_type>(index) + 1);
		if (static_cast<unsigned long long>(index) + 1 < len and concat_value < 27) {
			result += impl(index + 2, impl);
		}
		return result;
	};
	cout << impl(0, impl);
	const auto& dpImpl = [&data](int index) {
		if (data.at(index) == 0)return 0;
		size_t len = data.size();
		fbvector<int> dp(len + 1);
		dp[len] = 1;

	};
}

void StringAglo::find_longest_not_repeat_sub()
{
	// 找到最长未出现的连续子串
    std::array<int, 256> data{};
    std::fill(data.begin(), data.end(), -1);
    fbstring str = R"(assdgdhkasdgftyzxcyt)";
    int result_len = 0;
    int interval = 0;
    int pre = -1;// 判断当前可以判断的字符起始位置在哪里
    fbstring::size_type size = str.size();
    //如果以当前字符结尾的情况下 将获得最长的间隔为多少
    for (size_t i = 0; i < size; i++)
    {
        // 当前的起始位置 要不就是与上一次一致  要不然就是上一次出现当前字符的位置
		pre = std::max(pre, data[str[i]]);
        // 当前可以达到的最大长度为
        interval = i - pre;
		dbg(interval, 
			folly::StringPiece(str.begin() + i + 1 - interval
				, str.begin() + i+1),"\n");
        result_len = std::max(interval, result_len);
		data[str[i]] = i;
        
    }
    
    
}

void StringAglo::string_replace()
{
    // 从字符串str1 到 str2 提供 插入 删除 修改的代价为 ic dc rc 
    // 得到最小的代价
    fbstring first = "asd";
    fbstring second = "aad";
    auto dp= fbvector<fbvector<int>>(first.size() + 1, fbvector<int>(second.size() + 1));
    int ic = 5;
    int dc = 11;
    int rc = 7;
	size_t front_size = dp.front().size();
    for (size_t i = 0; i < front_size; i++)
    {
        dp[0][i] = i * ic; // 从空字符变成当前的字符串 需要多少个插入代价
    }
    size_t row_size = dp.size();
	for (size_t i = 0; i < row_size; i++)
	{
		dp[i][0] = i * dc; // 从当前的字符串变成空字符 需要多少个删除代价
	}
    fbstring::size_type first_size = first.size();
    fbstring::size_type second_size = second.size();
    for (size_t x = 1; x < first_size; x++)
    {
        for (size_t y = 1; y < second_size; y++)
        {
            if (first[x] == second[y]) {
                // 当前字符相等的情况下 情况与 dp[x-1][y-1]所耗费的代价相同
                dp[x][y] = dp[x - 1][y - 1];
            }
            else {
                dp[x][y] = dp[x - 1][y - 1]+rc;// 否则就是的改一个字符代价
            }
            dbg( dp[x - 1][y] + dc,dp[x][y - 1] + ic,dp[x][y] );
            
            dp[x][y] = std::min({ dp[x - 1][y] + dc,dp[x][y - 1] + ic,dp[x][y] });
        }
    }
}

void StringAglo::boolean_expression()
{
	// 有关当前的 布尔表达式的运算过程

    fbstring expression = "1^0|0|1";
	
	const auto impl = [&expression](auto&& impl, 
		bool desired, int left, int right)->int {
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
				for (int i = left + 1; i < right; i += 2)
				{
					dbg(desired);
					 dbg(expression[i],
						folly::StringPiece(expression.begin() 
							, expression.begin() + i));
                    dbg(folly::StringPiece(expression.begin() + i+1
                        , expression.begin() + right));
					switch (expression[i])
					{
					case '^':
						result += impl(impl, false, left, right - 1) * impl(impl, true, left + 1, right);
						result += impl(impl, true, left, right - 1) * impl(impl, false, left + 1, right);
						break;
					case '|':
						result += impl(impl, false, left, right - 1) * impl(impl, true, left + 1, right);
						result += impl(impl, true, left, right - 1) * impl(impl, false, left + 1, right);
						result += impl(impl, true, left, right - 1) * impl(impl, true, left + 1, right);
						break;
					case '&':
						result += impl(impl, true, left, right - 1) * impl(impl, true, left + 1, right);
						break;
					default:
						break;
					}
				}
			}
            else {
				// 偶数位才是当前的运算符 
				for (int i = left + 1; i < right; i += 2)
				{

					dbg(desired);
					dbg(expression[i],
						folly::StringPiece(expression.begin()
							, expression.begin() + i));
					dbg(folly::StringPiece(expression.begin() + i+1
						, expression.begin() + right));
					switch (expression[i])
					{
					case '^':
						result += impl(impl, true, left, right - 1) * impl(impl, true, left + 1, right);
						result += impl(impl, false, left, right - 1) * impl(impl, false, left + 1, right);
						break;
					case '|':
						result += impl(impl, false, left, right - 1) * impl(impl, false, left + 1, right);
						break;
					case '&':
						result += impl(impl, true, left, right - 1) * impl(impl, false, left + 1, right);
						result += impl(impl, false, left, right - 1) * impl(impl, true, left + 1, right);
						result += impl(impl, false, left, right - 1) * impl(impl, false, left + 1, right);
						break;
					default:
						break;
					}
				}
            }
        
            return result;
    };
	impl(impl, false, 0, expression.size() - 1);

}

void StringAglo::expression()
{
	fbstring str1 = "48*((70-65)-43)+8*1";
	fbstring str2 = "3+1*4";
	struct StrResult{
		int find_right_bracket; //遇到右括号 或者终止

	};


}

inline void StringAglo::printAll(const fbstring& cur, 
	size_t index, const fbstring& data) {
    if (index == data.size()) {
        cout << cur << '\n';
        return;
    }
    printAll(cur + data[index], index + 1, data);
    printAll(cur, index + 1, data);
}
