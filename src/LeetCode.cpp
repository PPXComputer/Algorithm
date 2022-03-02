#include "../include/LeetCode.h"
#include <dbg.h>
#include <cassert>
#include <array>
#include <fmt/format.h>
void LeetCode::medium_33()
{
	//��ת������� 
	auto impl = []() {
		std::array<int, 7> nums{ 4,5,6,7,0,1,2 };
		int target = 0;
		int left = 0; int right = nums.size() - 1;
		while (left < right)
		{
			int mid = ((right - left) >> 1) + left;
			dbg(left, right, mid, nums[mid]);
			if (target == nums[mid]) return mid;
			if (nums[mid] <= nums[right]) // �Ҳ�����
			{
				if (target <= nums[right] and target > nums[mid]) {
					left = mid + 1;
				}
				else {
					//�������
					right = mid - 1;
				}

			}
			else { //�������
				if (target >= nums[left] and target < nums[mid]) {
					right = mid - 1;
				}
				else {
					//���ұ���
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
			//�ҵ���һ������target�ĵط�
			int mid = left + ((right - left) >> 1);
			dbg(left, right, mid, nums[mid]);
			if (nums[mid] > target) {
				right = mid - 1;
			}
			else if (nums[mid] < target) {
				left = mid + 1;
			}
			else {
				right = mid; //�����򲻶� ���������ǵ�һ��
			}
		}
		if (nums[left] != target)return { -1,-1 };
		int left_result = left;
		left = 0; right = static_cast<int>(nums.size() - 1);

		while (left < right) {
			//�ҵ����һ������target�ĵط�
			int mid = left + ((right - left) >> 1) + 1; //���Ҳ�ƫ��һ�� ���ұ߿�
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
	// ����ǰ������ ת��Ϊ��ά����
	int left = 0;
	constexpr size_t matrix_column = matrix.front().size();
	constexpr size_t matrix_row = matrix.size();
	int right = static_cast<int> (matrix_row * matrix_column - 1);
	int target = 3;
	auto transform_really_pos = [](int pos, int row, int column)->std::pair<int, int> {
		assert(pos >= 0 and pos < row* column);
		return { pos / column,pos % column };
	};
	auto find = [&]() {
		while (left < right)
		{
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
			else
			{
				left = mid + 1;
			}
		}
		auto pos = transform_really_pos(left, matrix_row, matrix_column);
		return matrix[pos.first][pos.second] == target;

	};
	dbg(find());

}

void LeetCode::reverseKGroup()
{
	constexpr int length = 10;
	std::unique_ptr<RawNode> root_ptr = LeetCode::RawNode::new_list(length);
	RawNode* root = root_ptr.get();
	//���ֵ����
	//��ת��ǰ�����������
	int k = 4;
	int time = length / 4;
	int count = 0;


	// ��ת��� ͷ  β �ͺ�һ��Ԫ��
	auto reverse_list = [](RawNode* start, int need) {
		RawNode* head = nullptr;
		RawNode* cur = nullptr;
		int repeat_time = 0;
		std::tuple<RawNode*, RawNode*, RawNode*> result{ nullptr, start,nullptr };
		while (repeat_time != need)
		{
			cur = start->next;
			start->next = head;
			head = start;
			start = cur;
			repeat_time++;

			bool isLastTime = repeat_time == need;
			if (isLastTime)
			{
				//����ǰ���һ����Ԫ�ر�������
				std::get<0>(result) = head;
				std::get<2>(result) = cur;
			}
		}
		return result;
	};

	RawNode* result = nullptr;
	RawNode* lastTail = nullptr;
	RawNode* lastStart = root;
	if (time > 0 and length != 1) {
		int start = 0;
		while (time != start) {
			auto result_tuple = reverse_list(lastStart, k);
			if (start == 0) {
				result = std::get<0>(result_tuple); //���������
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

void LeetCode::findPeakElement()
{
	vector<int> data{ 1,2,1,3,5,6,4 };
	int left = 0; int right = data.size() - 1;
	while (left < right) {
		int mid = ((right - left) >> 1) + left;

		dbg(fmt::format("{} {} {} ", left, right, mid));
		dbg(fmt::format("{} {} {} ", data[left], data[right], data[mid]));

		if (data[mid] < data[static_cast<size_t>(mid + 1)])
		{
			left = mid + 1;
		}
		else {
			right = mid;
		}
	}
	dbg(left);

}

void LeetCode::findMin()
{
	std::vector<int> data = { 3,4,5,1,2 };
	//�ҵ���ת�������Сֵ
	// �ҵ���ǰÿ���е�������ݵ� �ҵ�һ������ǰ�� ��ߵ��������� �ұߵ���С����
	auto ans = [](vector<int>& nums) {
		// һ�����������
		int left = 0;
		int right = static_cast<int>(nums.size() - 1);

		while (left < right)
		{
			int mid = ((right - left) >> 1) + left;
			dbg(fmt::format("{} {} {} ", left, right, mid));
			dbg(fmt::format("{} {} {} ", nums[left], nums[right], nums[mid]));

		}
		dbg(nums[left]);

	};
	ans(data);

}
