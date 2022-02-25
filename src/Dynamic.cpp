#include "../include/Dynamic.h"
#include "../include/GreedyAlgo.h"
#include <initializer_list>
#include <iostream>
#include <optional>
#include <cassert>
#include <random>
#include <array>
#include <memory>

#include<cassert>
using std::cout;
using std::initializer_list;
using std::make_unique;
using std::unique_ptr;
using std::array;
using std::addressof;
using folly::fbstring;
using folly::fbvector;
using std::vector;
using std::optional;

void Dynamic::binary_tree_counter() {
	struct Node {
		Node* left = nullptr;
		Node* right = nullptr;
		int value = 0;
	};
	int counter = -1;
	const auto& impl = [&counter](Node* root, int cur, auto&& impl) -> void {
		if (root) {
			cur += root->value;
			// 只有根节点才算路径
			if (not root->left and not root->right and cur > counter)counter = cur;
			impl(root->left, cur, impl);
			impl(root->right, cur, impl);
		}
	};
}

void Dynamic::minimum_manipulate() {

	const auto& impl = [](const fbstring& s, const fbstring& m, int counter, int target, auto&& impl) -> int {
		if (s.size() == target) {
			return counter;
		}
		else if (s.size() > target) {
			return INT_MAX;
		}
		// first  manipulate
		int first = impl(s + s, s, counter + 1, target, impl);

		// second manipulate
		int second = impl(s + m, m, counter + 1, target, impl);
		return std::min(first, second);
	};
	for (int i = 1; i < 100; i++) {
		cout << fmt::format("cur: {} result: {} \n", i, impl("1", "1", 0, i, impl));
	}
}

void Dynamic::triangle() {
	const auto& impl = [] {
		fbvector<fbvector<int>> data;
		constexpr int n = 1000;
		data.reserve(n);
		data.push_back({ 1 });
		int cur = 2;
		for (int i = 1; i < n; i++) {
			data.push_back({});
			// 处理每一层
			fbvector<int>& curLayer = data.at(i);
			curLayer.emplace_back(1);
			fbvector<int>& proLayer = data.at(i - 1);
			for (int j = 1; j < i; j++) {
				int curValue = proLayer[j - 1] + proLayer[j];
				if (curValue == cur) {
					int site = (1 + i) * i / 2 + j + 1;
					fmt::print("value: {} site: {} \n", cur, site);
					cur++;
				}
				curLayer.emplace_back(curValue);
			}
			curLayer.emplace_back(1);
		}
	};
	const auto& mathImpl = [](int value) {
		assert(value);
		if (value == 2)return 5;
		return 5 + (3 + value) * (value - 2) / 2;

	};
	for (int i = 1; i < 100; i++) {
		fmt::print("value :{} site:{}\n", i, mathImpl(i));
	}
}

void Dynamic::binaryTree() {
	const auto& impl = [](const int rest, auto&& impl) -> size_t {
		if (rest == 0)return 0;
		else if (rest == 1)return 1;
		else if (rest == 2)return 2;
		else if (rest == 3)return 5;
		size_t result = 0;
		for (int i = 1; i < rest; i++) {
			size_t right = impl(rest - i - 1, impl);
			size_t left = impl(i, impl);
			result += left * right;
		}
		return result;
	};
	const auto& dpImpl = [](size_t rest) -> size_t {
		if (rest == 0) return 0;
		fbvector<size_t> dp = { 1, 1, 2, 5 };// rest 长度的表
		dp.reserve(rest + 1);
		for (int i = 4; i <= rest; i++) {
			size_t result = 0;
			for (int j = 0; j < i; j++) {
				result += dp[i - 1 - j] * dp[j];
			}
			dp.emplace_back(result);
		}
		return dp[rest];
	};
	for (int i = 5; i < 10; i++)
		cout << fmt::format("value: {} result: {} \n", i, dpImpl(i));
}

void Dynamic::three_num_counter() {
	fbvector<int> data{ -1, 0, 1, 2, -1, -4 };
	std::sort(data.begin(), data.end());
	data.erase(std::unique(data.begin(), data.end()), data.end());
	fbvector<int>::size_type len = data.size();
	int counter = 0;
	for (int i = 0; i < len; i++) {
		for (size_t j = len - 1; j >= i + 2; j--) {
			if (std::binary_search(
				data.begin() + i + 1, data.begin() + j - 1, -(data[i] + data[j])
			)) {
				counter++;

			}
		}
	}
	cout << counter;
}

void Dynamic::maze_compression() {
	// 迷宫问题的压缩

	const auto& dfs = [](int x, int y, auto&& dp) {
		if (x == 3 and y == 5) {
			return 1;
		}
		if (x > 3 or y > 5) return 0;
		return dp(x + 1, y, dp) + dp(x, y + 1, dp);
	};

	auto result = dfs(0, 0, dfs);
	cout << fmt::format(" result :{} \n", result);

	const auto& dp = [] {
		array<array<int, 5>, 3> table = {
				array<int, 5>{1, 1, 1, 1, 1},
				{1, 0, 0, 0, 0},
				{1, 0, 0, 0, 0}
		};
		for (int row = 1; row < 3; row++) {
			for (int col = 1; col < 5; col++) {
				table[row][col] = table[row][col - 1] + table[row - 1][col];
			}
		}
		return table[2][4];
	};

	cout << fmt::format(" result :{} \n", dp());
	const auto& dpCompression = [] {
		// 数据压缩只放一部分的数据
		array<int, 5> data = { 1, 1, 1, 1, 1 };

		constexpr int layer = 3;
		constexpr int table_len = 5;
		for (size_t i = 1; i < layer; i++) {
			data[1] = data[1] + 1;
			for (size_t pos = 2; pos < table_len; pos++) {

				data[pos] = data[pos - 1] + data[pos];
			}
		}
		return data[4];
	};

	cout << fmt::format(" result :{} \n", dpCompression());
}

void Dynamic::container() {
	//    array<int, 5> data = {3, 1, 5, 2, 4};
	//    int max_left = data.front();
	//    int max_right = data.back();
	//    int pos_left = 0;
	//    int pos_right = data.size() - 1;
	//    int result = 0;
	//    while (pos_right > pos_left) {
	//        // 结算当前的数据使用情况
	//
	//
	//    }
}

void Dynamic::partition() {
	array data = { 123, 231, 52, 742, 31, 67, 9, 687, 12578 };
	int result = INT_MIN;

	for (int i = 1; i < data.size() - 1; i++) {
		auto begin = data.begin();
		long long cur = std::abs(*std::max_element(begin, begin + i) - *std::max_element(begin + i, data.end()));
		if (cur > result) {
			result = static_cast<int>(cur);
		}
	}
	cout << fmt::format("result {} \n", result);
}

void Dynamic::rotate() {
	fbstring data = "1234";
	fbstring::size_type len = data.size();
	auto double_data = data + data;
	do {

		cout << fmt::format("data {} \n", data);
		for (size_t i = 0; i < len - 1; i++) {
			fbstring::iterator begin = data.begin();
			std::rotate(begin, data.begin() + 1, data.end());
			//cout << fmt::format("\n {} \n", data);
		}
		if (double_data.find(data) != fbstring::npos) {
			cout << data << '\n';
		}

	} while (std::next_permutation(data.begin(), data.end()));
}

void Dynamic::multiply_4() {
	fbvector<int> data = GreedyAlgo::geRandomArray();
	int counter_odd = 0;
	int counter_even = 0;
	int counter_even_2 = 0;
	for (const auto& a : data) {
		if (a % 2)
			counter_odd++;
		else if (a % 4)
			counter_even_2++;
		else
			counter_even++;
	}
	if (not counter_odd or counter_odd + 1 <= counter_even)
		cout << fmt::format("result :{}", true);
	else

		cout << fmt::format("result :{}", false);
}

void Dynamic::achive() {
	const auto& impl = [](int num, int cur, int len, int pre, auto&& impl) -> int {

		if (not cur and not pre) { return 0; }
		if (len == num) { return 1; }
		auto fill_zero = impl(num, 0, len + 1, cur, impl);
		auto fill_one = impl(num, 1, len + 1, cur, impl);
		return fill_zero + fill_one;
	};
	/*for (int i = 3; i < 10; i++)
	{
		cout << fmt::format("result: {}\n", impl(i, 1, 1, 0,"1", impl));
	}*/
	int data[] = { 1, 2 };
	for (int i = 3; i < 100; i++) {
		int result = data[0] + data[1];
		if (result != impl(i, 1, 1, 0, impl)) {
			cout << "???";
			break;
		}
		data[0] = data[1];
		data[1] = result;
	}
	// 快速 斐波那契数列实现 当前依赖之前项的情况下将获得全部的实现
	// f(n )=f(n-1) +f(n-2)
	//当前的斐波那契数列 将获得全部的子项
}

void Dynamic::quick_multiply() {
	int data = 45;
	size_t result = 1;
	size_t temp = 2;
	while (data) {

		if (data & 1) {
			result *= temp;
			cout << temp << " \n";
		}
		temp *= temp;
		data >>= 1;
	}
	cout << result;

	//矩阵相乘
}

inline void Dynamic::package() {
	int target = 30;
	fbvector<int> data = GreedyAlgo::geRandomArray(10, 2, 20);
	const auto& dfsImpl = [&data](int cur, int res, auto&& dfsImpl) {
		if (res < 0)return 0;
		if (cur == data.size())return 1;
		auto get = dfsImpl(cur + 1, res - data[cur], dfsImpl);
		auto not_get = dfsImpl(cur + 1, res, dfsImpl);
		return get + not_get; // 这部分 是递归程序 将的 多次触发
	};
	auto result = dfsImpl(0, target, dfsImpl);
	for (auto sd : data) {
		cout << sd << " ";
	}
	cout << fmt::format("\n result:{}", result);

	const auto& dpImpl = [&data](int target) {
		assert(not data.empty());
		fbvector<fbvector<int>> table(data.size() + 1, fbvector<int>(target + 1));
		// f(cur,res) =f(cur+1,res-data[cur])+f(cur+1,res)
		fbvector<fbvector<int >>::reference
			last_array = table.back();
		std::fill(last_array.begin(), last_array.end(), 1);//默认全部填零 所以填入1
		for (size_t row = data.size() - 1; row >= 1; row--) {
			for (size_t rest = 0; rest <= target; rest++) {
				if (rest - data[row] >= 0)
					table[row][rest] = table[row + 1][rest - data[row]] + table[row + 1][rest];
				else
					table[row][rest] = table[row + 1][rest];
			}
		}
		if (target - data[0] >= 0)
			table[0][target] = table[1][target - data[0]] + table[1][target];
		else
			table[0][target] = table[1][target];
		return table[0][target];
	};


	cout << fmt::format("\n result:{}", dpImpl(target));

	// 压缩空间存储
	const auto& dpCompressImpl = [&data](int target) {
		fbvector<int> pre_layer(target + 1, 1);
		fbvector<int> cur_layer(target + 1);
		[[maybe_unused]] fbvector<int>::size_type second_layer = pre_layer.size() - 1;
		[[maybe_unused]] int len = target + 1;
		for (size_t row = data.size() - 1; row >= 1; row--) {
			for (size_t rest = 0; rest <= target; rest++) {
				if (rest - data[row] >= 0)
					cur_layer[rest] = pre_layer[rest - data[row]] + pre_layer[rest];
				else
					cur_layer[rest] = pre_layer[rest];
			}
			std::swap(pre_layer, cur_layer);
		}
		if (target - data[0] >= 0)
			cur_layer[target] = pre_layer[target - data[0]] + pre_layer[target];
		else
			cur_layer[target] = pre_layer[target];
		return cur_layer[target];
	};
	cout << fmt::format("\n result:{}", dpCompressImpl(target));

	// 备忘录记录路径
	fbvector<fbvector<int>> cache(data.size() + 1, fbvector<int>(target + 1, -1));
	const auto& dfsCacheImpl = [&data, &cache](int cur, int res, auto&& dfsCacheImpl) {
		if (res < 0)return 0;
		if (cur == data.size()) {
			cache[cur][res] = 1;
			return 1;
		}
		int get = 0;
		int rest_money = res - data[cur];
		if (rest_money >= 0) {
			int cache_value = cache[cur + 1][rest_money];
			if (cache_value != -1)
				get = cache_value;
			else {
				get = dfsCacheImpl(cur + 1, rest_money, dfsCacheImpl);
				cache[cur + 1][rest_money] = get;
			}
		}
		int not_get = 0;
		if (cache[cur + 1][res] != -1) {
			not_get = cache[cur + 1][res];
		}
		else {
			not_get = dfsCacheImpl(cur + 1, res, dfsCacheImpl);
			cache[cur + 1][res] = not_get;
		}
		cache[cur][res] = get + not_get;
		return cache[cur][res];
	};

	cout << fmt::format("\n result:{}", dfsCacheImpl(0, target, dfsCacheImpl));
}


void Dynamic::sub_matrix() {
	array<array<int, 4>, 3> data = {
			array{-5, 3, 6, 4},
			{-7, 9, -5, -3},
			{-10, 1, -200, 4}
	};
	using Result = std::optional<std::pair<int, int>>;
	const auto& long_counter = [](const array<int, 4>& ref) -> Result {
		if (ref.empty()) return {};
		auto max_data = *std::max_element(ref.begin(), ref.end());
		auto cur_data = ref.front();
		int start = 0;
		auto result = std::make_pair(0, 1);
		for (int i = 1; i < ref.size(); i++) {
			auto cur = ref.at(i);
			if (cur_data + cur > 0) {
				if (cur_data > max_data) {
					max_data = cur_data;
					result = { start, i + 1 };
				}
			}
			else {
				cur_data = cur;
				start = i;
			}
		}
		return { result };
	};
	constexpr size_t len = data.size();
	constexpr size_t first_len = data.front().size();
	for (int i = 0; i < len; i++) {
		long_counter(data[i]);
		for (int j = 0; j < first_len; j++) {
			data[0][j] += data[i][j];
		}
	}
}

void Dynamic::bit_count() {
	// bit 文件的使用

	constexpr auto is2pow = [](const int data) {
		return (data != 0) and (data & data - 1) == 0;
	};
	is2pow(1);
	// 判断是否
	constexpr auto is4pow = [](const int data) {
		return data != 0 and (data & data - 1) == 0 and (data & 0x55555555) == 0;
	};
	is4pow(32);

}

void Dynamic::different_way() {
	// 总共 n 个方格 起始位置 第s个方格  要走k步 有多少方案
	constexpr int total = 5;
	constexpr int start = 2;
	constexpr int end = 4;
	constexpr int k = 5;
	std::function<int(int, int)> fn;
	fn = [&](int cur_pos, int rest_k) -> int {
		if (cur_pos == 0 or cur_pos > total)return 0;
		if (rest_k == 0) {
			if (cur_pos == end) return 1;
			else return 0;
		}
		return fn(cur_pos + 1, rest_k - 1)
			+ fn(cur_pos - 1, rest_k - 1);

	};
	fmt::print("result:{}", fn(start, k));
	// f[end,0]=1  f[x,0]=0  f[0,k]=0 f[total+1,k]=0
	// f[start,k]= f[start-1,k-1] +f[start+1,k-1]

	auto dynamic_array = [&] {
		folly::fbvector<folly::fbvector<int>> data{};
		data.reserve(total + 2);
		data.assign(total + 2, folly::fbvector<int>(k + 1));
		//f[end,0]=1  f[x,0]=0
		//f[total+1,k]=0
		data.at(end).at(0) = 1;

		//其他位置填充-1
		size_t row = data.size();
		size_t column = data.front().size();
		for (size_t x = 1; x < row; x++)
			for (size_t y = 1; y < column; y++)
				data.at(x).at(y) = -1;

		// f[start,k]= f[start-1,k-1] +f[start+1,k-1]
		std::function<int(int, int)> impl;
		impl = [&](int cur_pos, int cur_k) -> int {
			if (cur_pos < 0 or cur_pos > total + 1)return 0;
			// 避免重复计算
			if (data.at(cur_pos).at(cur_k) != -1) {
				return data.at(cur_pos).at(cur_k);
			}
			else {
				// 将当前结果填入到数据中去
				data.at(cur_pos).at(cur_k) = impl(cur_pos - 1, cur_k - 1)
					+ impl(cur_pos + 1, cur_k - 1);
				return data.at(cur_pos).at(cur_k);
			}
		};
		return impl(start, k);
	};
	fmt::print("result :{}", dynamic_array());

}

void Dynamic::rope_range() {
	fbvector<int> randomArray = GreedyAlgo::geRandomArray(10, 0, 30, true);
	std::sort(randomArray.begin(), randomArray.end());
	fmt::print("data:{} \n", fmt::join(randomArray, ","));

	constexpr int span = 5;
	const size_t size = randomArray.size();
	{
		int result = INT_MIN;
		for (size_t i = 0; i < size; ++i) {
			int cur = 1;
			const int& cur_data = randomArray.at(i);
			for (size_t start = i + 1; start < size; start++) {
				if (randomArray.at(start) - cur_data < span) {
					cur++;
					result = std::max(cur, result);
				}
			}
		}
		fmt::print("result:{}\n", result);

	}

	{
		const auto binary_search = [&randomArray](int start, int end, const int target) -> int {
			while (start < end) {
				// 找到当前的 第一个大等于 target
				//当前的数据实现
				int pos = (start + end) >> 1;
				if (randomArray.at(pos) == target) { return pos; }
				else if (randomArray.at(pos) < target) { start = pos + 1; }
				else { end = pos; }
			}
			return start;
		};
		int result = 1; // 最少也是一个
		for (size_t i = 1; i < size; ++i) {
			// 从 0到 i 的范围中二分查找当前的节点
			int search = binary_search(0, static_cast<int>(i), randomArray.at(i) - span);
			result = std::max(result, static_cast<int>(i) + 1 - search);
		}
		fmt::print("result:{} \n", result);

	}

	{
		//滑动窗口
		int start = 0;
		int end = start + 1;
		int result = 1;
		for (; end < size; end++) {
			if (randomArray.at(end) - randomArray.at(start) <= span) {
				result = std::max(end - start + 1, result);
				continue;
			}
			for (; start < end; start++) {
				if (randomArray.at(end) - randomArray.at(start) <= span) {
					break;
				}
			}
		}
		fmt::print("result:{} \n", result);
	}

}

void Dynamic::apple() {

	// 6,8
	for (int i = 2; i < 100; i += 2) {
		int result = INT_MAX;
		if ((i & 1) == 0) { //是偶数
			for (int j = 0; j <= i / 6; j++) {
				for (int n = 0; n <= (i - j * 6) / 8; n++) {
					if (j * 6 + n * 8 == i) {
						result = std::min(j + n, result);
					}
				}
			}

		}
		if (result != INT_MAX) {
			fmt::print("target {} result {}\n", i, result);
		}
		else {
			fmt::print("target {} boom!!\n", i);
		}
	}
	// 6 8
	// 12 14 16
	// 18 20 22 24
	// 26 28 30 32
	// 34
	[[maybe_unused]] auto fn = [](int target) {
		if ((target & 1) == 0) {
			if (target == 6 or target == 8)return 1;
			else if (target == 12 or target == 14 or target == 16)return 2;
			else {
				return (target - 18) / 8 + 3;
			}
		}
		else {
			return -1;
		}
	};

}

void Dynamic::winner() {
	// 牛
	enum class Winner {
		first, second
	};
	[[maybe_unused]] auto fn = [&](int n, auto&& self) -> Winner {
		if (n < 5) {
			return (n == 0) or (n == 2) ? Winner::second : Winner::first;
		}
		int base = 1;
		while (base <= n) {
			// 这里一直尝试第二个人拿的步骤 如果不成功则是第一个人赢
			// 判断第一个人成不成功是这个while 循环干的事
			if (self(n - base, self) == Winner::second) {
				return Winner::first;
			}
			if (base > n / 4)break; // 防止溢出
			base *= 4;
		}
		return Winner::second;
	};
	//    for (int i = 0; i < 100; ++i) {
	//        fmt::print("i {} result {} \n", i, fn(i, fn) == Winner::first ? "first" : "second");
	//    }
	auto enumerate = [](int n) -> Winner {
		return (n % 5 == 0) or (n % 5 == 2) ? Winner::second : Winner::first;
	};
	for (int i = 0; i < 100; ++i) {
		fmt::print("i {} result {} \n", i, enumerate(i) == Winner::first ? "first" : "second");
	}
}

void Dynamic::color() {
	// RGGRRGG
	const char str[] = "RGGRRGG";

	int left_range = 1;
	constexpr size_t size = std::size(str);
	size_t result = INT_MAX;
	for (; left_range < size - 1; left_range++) {
		size_t cur = 0;
		// 左侧从范围减一开始
		if (left_range >= 2) {
			cur = std::count(str, str + left_range - 1, 'R');
		}
		// 右侧有多少个G
		cur += std::count(str + left_range + 1, str + size, 'G');
		result = std::min(result, cur);
	}
	std::vector<int> help(size);

	// 判断当前位置的上不合理的数目

}

void Dynamic::snake()
{

	std::array<std::array<int, 5>, 5> data{
		{3,1,-1,4,-7},
		{1,1,-1,7,-1},
		{5,-6,-7,8,5},
		{6,-1,-10,1,3},
		{0,-9,-2,2,-7},
	};

	// 递归暴力解法
	const auto& enumDfs = [&data](int x, int y, int cur, int minimum = INT_MAX, auto&& dfs)->int {
		if (cur < 0)return INT_MIN;
		if (x >= 5 or x < 0 or y >= 5 or y < 0)return cur;
		if (minimum > data[x][y]) minimum = data[x][y];
		cur = cur + data[x][y];
		return  std::max(dfs(x + 1, y, cur, minimum, dfs),
			dfs(x - 1, y + 1, cur, minimum, dfs),
			dfs(x, y + 1, cur, minimum, dfs));
	};
	int result = INT_MIN;
	for (const auto& item : data) {
		for (int& i : data) {

			if (i < 0) {
				int a = dfs(0, 0, 0, INT_MAX, dfs);
				i = -i;
				int b = dfs(0, 0, 0, INT_MAX, dfs);
				result = std::max({ result,a,b });
			}
			else {
				result = std::max(result, dfs(0, 0, 0, INT_MAX, dfs));
			}
		}
	}


	struct MazeResult {
		int cur_value;
		int find_minimum;
		bool used_flip;
	};


	// 添加到当前的 最小值判断中将当前 可能遇到的值中变化一次常数
	// 当前的值和过程中遇到的最小的数
	const auto& cacheMinimum = [&data](int x, int y, MazeResult cur, auto&& dfs)->MazeResult {
		//越界返回
		if (x >= 5 or x < 0 or y >= 5 or y < 0)return cur;

		// 记录路上碰到的最小值
		if (cur.find_minimum > data[x][y]) cur.find_minimum = data[x][y];

		//走到当前的步骤时进行记录
		cur.cur_value += data[x][y];

		//如果记录当前值后为负数 则可能直接返回
		if (cur.cur_value < 0) {
			if (cur.used_flip == false and cur.cur_value - cur.find_minimum >= 0) {
				//当前为负数 并未使用过翻转所以 将最后一个元素转换为的正数
				cur.used_flip = true;
				cur.cur_value -= cur.find_minimum;
			}
			else {
				return cur; //如果为负值 且路径上通过翻转也不可能变成正数 则返回
			}
		}
		MazeResult left = dfs(x + 1, y, cur, dfs);
		MazeResult rightUp = dfs(x - 1, y + 1, cur, dfs);
		MazeResult right = dfs(x, y + 1, cur, dfs);

		auto get_potential = [left, right, rightUp]() {
			if (left.used_flip == false and left.find_minimum < 0) {
				left.used_flip = true;
				left.cur_value -= left.find_minimum;
			}
			if (right.used_flip == false and right.find_minimum < 0) {
				right.used_flip = true;
				right.cur_value -= right.find_minimum;
			}
			if (rightUp.used_flip == false and rightUp.find_minimum < 0) {
				rightUp.used_flip = true;
				rightUp.cur_value -= rightUp.find_minimum;
			}
			return std::max({ left,rightUp,right }, [](MazeResult& lhs, MazeResult& rhs) {
				return lhs.cur_value < rhs.cur_value});
		};
		return get_potential();
	};

}
