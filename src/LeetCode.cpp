#include "../include/LeetCode.h"
#include <dbg.h>
#include <cassert>
#include <array>
void LeetCode::medium_33()
{
	//旋转后的数组 
	auto impl = []() {
		std::array<int, 7> nums{ 4,5,6,7,0,1,2 };
		int target = 0;
		int left = 0; int right = nums.size() - 1;
		while (left < right)
		{
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
void LeetCode::medium_34()
{
	using std::vector;
	auto answer = [](vector<int>& nums, int target)->vector<int> {
		if (nums.empty())return { -1,-1 };
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
		if (nums[left] != target)return { -1,-1 };
		int left_result = left;
		left = 0; right = static_cast<int>(nums.size() - 1);

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
		return { left_result,left };
	};
	vector<int>data{ 5, 7, 7, 8, 8, 10 };
	dbg(answer(data, 8));
}

void LeetCode::medium_74()
{
	std::array<std::array<int, 4>, 3> matrix = {
		std::array<int,4>{1,3,5,7},
		{10,11,16,20},
		{23,30,34,60}
	};
	// 将当前的搜索 转换为二维坐标
	int left = 0;
	constexpr size_t matrix_column = matrix.front().size();
	constexpr size_t matrix_row = matrix.size();
	int right = static_cast<int> (matrix_row * matrix_column);
	int target = 3;
	auto transform_really_pos = [](int pos, int row, int column)->std::pair<int, int> {
		assert(pos >= 0 and pos < row* column);
		return { pos / column,pos % column };
	};
	auto find = [&]() {
		while (left < right)
		{
			int mid = ((right - left) >> 1) + left;

			auto pos = transform_really_pos(mid, matrix_row, matrix_column);
			if (matrix[pos.first][pos.second] == target) {
				return true;
			}
			else if (matrix[pos.first][pos.second] > target) {
				left = mid + 1;
			}
			else
			{
				right = mid - 1;
			}

		}
		auto pos = transform_really_pos(left, matrix_row, matrix_column);
		return matrix[pos.first][pos.second] == target;

	};
	find();

}

void LeetCode::reverseKGroup()
{
	constexpr int length = 10;
	std::unique_ptr<RawNode> root_ptr = LeetCode::RawNode::new_list(length);
	RawNode* head = nullptr;
	RawNode* cur = nullptr;
	RawNode* first_head = nullptr;
	RawNode* root = root_ptr.get();
	//多个值相连
	//旋转当前中最近的数据
	int k = 4;
	int time = length / 4;
	int count = 0;
	RawNode* result = nullptr;

	auto reverse_list = [](RawNode* start, int need) {
		RawNode* head = nullptr;
		RawNode* cur = nullptr;
		int repeat_time = 0;
		// 翻转后的 头  尾 和后一个元素
		std::tuple<RawNode*, RawNode*, RawNode*> result{nullptr, start,nullptr };
		while (repeat_time != need)
		{
			bool isFirstTime = repeat_time == 0; //第一次记录
			if (isFirstTime) {
				std::get<1>(result) = start;
			}

			cur = start->next;
			start->next = head;
			head = start;
			start = cur;
			repeat_time++;

			bool isLastTime = repeat_time == need;
			if (isLastTime)
			{
				//将当前最后一个的元素保留下来
				result[0] = nullptr;
			}
		}
	};
	if (time > 0 and length != 1) {
		vector<RawNode*> last_container; //将每次最后一个的链表给链接上
		last_container.reserve(time);
		while (time != 0) {
			//翻转
			if (count == k) {
				bool isFirstFlip = time == length - 4;
				if (isFirstFlip) { //第一次翻转
					result = head;
				}
				root = cur;
				first_head->next = root;
				count = 0; time -= 1;
			}
			if (count == 0) {
				first_head = root;
			}
			cur = root->next;
			root->next = head;
			head = head->next;
			count++;
		}
	}


}
