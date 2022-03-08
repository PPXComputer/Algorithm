#include "../include/LeetCode200.h"
#include <array>
#include <vector>
#include <string>
#include <map>
#include <fmt/format.h>
#include <dbg.h>
#include <unordered_map>

using std::array;
using std::vector;
using std::string;
inline void LeetCode200::medium_33() {
	//旋转后的数组
	auto impl = []() {
		std::array<int, 7> nums{ 4, 5, 6, 7, 0, 1, 2 };
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
				}
				else {
					//向左边找
					right = mid - 1;
				}

			}
			else { //左侧有序
				if (target >= nums[left] and target < nums[mid]) {
					right = mid - 1;
				}
				else {
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

inline void LeetCode200::medium_34() {
	using std::vector;
	auto answer = [](vector<int>& nums, int target) -> vector<int> {
		if (nums.empty())return { -1, -1 };
		int left = 0;
		int right = static_cast<int>(nums.size() - 1);
		while (left < right) {
			//找到第一个出现target的地方
			int mid = left + ((right - left) >> 1);
			dbg(left, right, mid, nums[mid]);
			if (nums[mid] > target) {
				right = mid - 1;
			}
			else if (nums[mid] < target) {
				left = mid + 1;
			}
			else {
				right = mid; //等于则不动 可能他就是第一个
			}
		}
		if (nums[left] != target)return { -1, -1 };
		int left_result = left;
		left = 0;
		right = static_cast<int>(nums.size() - 1);

		while (left < right) {
			//找到最后一个出现target的地方
			int mid = left + ((right - left) >> 1) + 1; //向右侧偏移一格 向右边靠
			dbg(left, right, mid, nums[mid]);
			if (nums[mid] > target) {
				right = mid - 1;
			}
			else if (nums[mid] < target) {
				left = mid + 1;
			}
			else {
				left = mid;
			}

		}
		return { left_result, left };
	};
	vector<int> data{ 5, 7, 7, 8, 8, 10 };
	dbg(answer(data, 8));
}

//. 搜索二维矩阵

inline void LeetCode200::medium_74() {
	std::array<std::array<int, 4>, 3> matrix = {
		std::array<int, 4>{1, 3, 5, 7},
		{ 10, 11, 16, 20 },
		{ 23, 30, 34, 60 }
	};
	// 将当前的搜索 转换为二维坐标
	int left = 0;
	constexpr size_t matrix_column = matrix.front().size();
	constexpr size_t matrix_row = matrix.size();
	int right = static_cast<int> (matrix_row * matrix_column - 1);
	int target = 3;
	auto transform_really_pos = [](int pos, int row, int column) -> std::pair<int, int> {
		assert(pos >= 0 and pos < row* column);
		return { pos / column, pos % column };
	};
	auto find = [&]() {
		while (left < right) {
			int mid = ((right - left) >> 1) + left;
			dbg(fmt::format("{} {} {} ", left, right, mid));
			auto pos = transform_really_pos(mid, matrix_row, matrix_column);
			dbg(fmt::format("{}", matrix[pos.first][pos.second]));
			if (matrix[pos.first][pos.second] == target) {
				return true;
			}
			else if (matrix[pos.first][pos.second] > target) {
				right = mid - 1;
			}
			else {
				left = mid + 1;
			}
		}
		auto pos = transform_really_pos(left, matrix_row, matrix_column);
		return matrix[pos.first][pos.second] == target;

	};
	dbg(find());

}

// 25  k 个一组翻转链表

inline void LeetCode200::reverseKGroup() {
	constexpr int length = 10;
	std::unique_ptr<ListNode> root_ptr = LeetCode200::new_list(length);
	ListNode* root = root_ptr.get();
	//多个值相连
	//旋转当前中最近的数据
	int k = 4;
	int time = length / 4;
	int count = 0;


	// 翻转后的 头  尾 和后一个元素
	auto reverse_list = [](ListNode* start, int need) {
		ListNode* head = nullptr;
		ListNode* cur = nullptr;
		int repeat_time = 0;
		std::tuple<ListNode*, ListNode*, ListNode*> result{ nullptr, start, nullptr };
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

	ListNode* result = nullptr;
	ListNode* lastTail = nullptr;
	ListNode* lastStart = root;
	if (time > 0 and length != 1) {
		int start = 0;
		while (time != start) {
			auto result_tuple = reverse_list(lastStart, k);
			if (start == 0) {
				result = std::get<0>(result_tuple); //将结果保存
			}
			else {
				if (lastTail)lastTail->next = std::get<0>(result_tuple);

			}
			lastStart = std::get<2>(result_tuple);
			lastTail = std::get<1>(result_tuple);
			start++;
		}
	}


}

//162 寻找峰值

inline void LeetCode200::findPeakElement() { //爬坡 不断向旁边最高前进
	vector<int> data{ 1, 2, 1, 3, 5, 6, 4 };
	int left = 0;
	int right = data.size() - 1;
	while (left < right) {
		int mid = ((right - left) >> 1) + left;

		dbg(fmt::format("{} {} {} ", left, right, mid));
		dbg(fmt::format("{} {} {} ", data[left], data[right], data[mid]));

		if (data[mid] < data[static_cast<size_t>(mid + 1)]) {
			left = mid + 1;
		}
		else {
			right = mid; // 保留当前位置的点
		}
	}
	dbg(left);

}

// 153 找到旋转数组的的最小值

inline void LeetCode200::findMin() {
	std::vector<int> data = { 3, 4, 5, 1, 2 };
	//找到旋转数组的最小值
	// 找到当前每次中到达的数据点 找到一个数当前的 左边的数大于他 右边的数小于他
	auto ans = [](vector<int>& nums) {
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

//198. 打家劫舍

inline void LeetCode200::houseRobber() {
	/*
	* 你是一个专业的小偷，计划偷窃沿街的房屋。每间房内都藏有一定的现金，
	影响你偷窃的唯一制约因素就是相邻的房屋装有相互连通的防盗系统，如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警。

	给定一个代表每个房屋存放金额的非负整数数组，计算你 不触动警报装置的情况下 ，一夜之内能够偷窃到的最高金额。
	*/
	vector<int> data{ 2, 7, 9, 3, 1 };
	const auto answerEnum = [](std::vector<int>& nums) {

		const auto answerImpl = [](int cur, int money, std::vector<int>& nums, auto&& answerImpl) -> int {
			if (cur >= nums.size())return money;
			int result = money + nums[cur];

			std::max({ answerImpl(cur + 1, money, answerImpl),
				result,
				answerImpl(cur + 2, money, answerImpl) });
			return result;
		};

	};
	const auto answerDp = [](std::vector<int>& nums) {

	};
}

//11. 盛最多水的容器

inline void LeetCode200::maxArea() {
	vector data{ 1, 8, 6, 2, 5, 4, 8, 3, 7 };
	const auto answer = [](vector<int>& height) {
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
	const auto answerForward = [](vector<int>& height) {
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

//82. 删除排序链表中的重复元素 II

inline void LeetCode200::deleteDuplicatesFromList() {
	//给定一个已排序的链表的头 head ， 删除原始链表中所有重复数字的节点，只留下不同的数字 。返回 已排序的链表 。
	std::vector<int> data = { 1, 1, 2, 2 };
	std::unique_ptr<ListNode> ptr = LeetCode200::new_list(data);
	auto head = ptr.get();
	auto answer_forward = [&]() {
		auto root = head;
		if (root == nullptr)return head;
		int val;
		auto cur = root->next;
		ListNode* prev = root;
		bool isFirstTime = true;
		while (cur != nullptr) {
			val = root->val;

			if (val == cur->val) {
				while (cur != nullptr and cur->val == val) {
					cur = cur->next;
				}

				if (prev == root) {
					if (cur == nullptr)return static_cast<ListNode*>(nullptr);
					else {
						head = cur;
						prev = cur;
						root = cur;
					}
				}
				else {
					prev->next = cur;
					root = cur;
				}
				if (cur == nullptr)break;
				cur = cur->next;

			}
			else {
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
			}
			else {
				cur = cur->next;
			}
		}
		return dummy->next;
	};
}

//15. 三数之和

inline void LeetCode200::three_num() {
	// 找到所有和为 0的不重复的三元组
	std::vector nums = { -2, 0, 0, 2, 2 };

	auto answer = [&](const std::vector<int>& data) -> std::vector<std::vector<int>> {
		if (nums.size() < 3)return {};
		// 二元组问题
		std::unordered_map<int, int> map;
		for (auto i : data) {
			if (map.find(i) == map.end()) {
				map.insert({ i, 1 });
			}
			else {
				map[i] += 1;
			}
		}
		dbg(map);
		std::vector<std::vector<int>> result;
		for (auto first : data) {
			if (map[first] > 0) {
				//找到当前的元素为第一个元素

				int take_time = -1;
				int value = -first;
				map[first] -= 1;
				bool if_not_match = true;
				for (auto second : data) {
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
							}
							else {
								if_not_match = false;
							}
							map[third] -= 1;
							dbg(map[third], map[first], if_not_match ? map[first] : map[first] - 1);

							result.emplace_back(vector<int>{first, second, third});

						}
						else {
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

	auto sort_answer = [&](std::vector<int>& data) -> std::vector<std::vector<int>> {
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
				}
				else if (cur > 0) {
					right -= 1;
				}
				else {
					left += 1;
				}
			}
			start++;
		}
		return result;
	};
	auto parm = vector<int>{ -1, 0, 1, 2, -1, -4 };
	dbg(sort_answer(parm));
}

//70. 爬楼梯

inline void LeetCode200::climbStairs() {
	auto answer = [](int n) -> int {

		constexpr auto fib_impl = [] {
			std::array<int, 31> fib{ 0, 1 };
			for (int i = 2; i != 31; ++i) {
				fib[i] = fib[i - 1] + fib[i - 2];
			}
			return fib;
		}();
		return fib_impl[n];
	};
}

void LeetCode200::connectRight()
{
	//std::list<ListNode*> container;
	//std::unique_ptr<ListNode> first = LeetCode200::new_list(10);
	//auto root = first.get();
	//if (root == NULL)return NULL;
	//vector<Node*> container;
	//container.push_back(root);

	//while (not container.empty())
	//{
	//	int curLayer = container.size();
	//	Node* lastNode = nullptr;
	//	for (int i = 0; i < curLayer; i++)
	//	{
	//		Node* back = container.back();
	//		container.pop_back();
	//		if (lastNode != nullptr) {
	//			lastNode->next = back;
	//		}
	//		lastNode = back;
	//		// 处在不同行处且
	//		if (back->left) {
	//			container.push_back(back->left);
	//		}
	//		if (back->right) {
	//			container.push_back(back->right);
	//		}
	//	}
	//}
	//return root;

}
