#include "../include/LeetCode.h"
#include <dbg.h>
#include <cassert>
#include <array>
#include <fmt/format.h>
#include <unordered_map>
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
	std::unique_ptr<ListNode> root_ptr = LeetCode::ListNode::new_list(length);
	ListNode* root = root_ptr.get();
	//���ֵ����
	//��ת��ǰ�����������
	int k = 4;
	int time = length / 4;
	int count = 0;


	// ��ת��� ͷ  β �ͺ�һ��Ԫ��
	auto reverse_list = [](ListNode* start, int need) {
		ListNode* head = nullptr;
		ListNode* cur = nullptr;
		int repeat_time = 0;
		std::tuple<ListNode*, ListNode*, ListNode*> result{ nullptr, start,nullptr };
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

	ListNode* result = nullptr;
	ListNode* lastTail = nullptr;
	ListNode* lastStart = root;
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
{ //���� �������Ա����ǰ��
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
			right = mid; // ������ǰλ�õĵ�
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
			if (nums[mid] < nums[right])
				right = mid;
			else
				left = mid + 1;

		}
		dbg(nums[left]);

	};
	ans(data);

}

void LeetCode::deleteDuplicatesFromList()
{
	//����һ��������������ͷ head �� ɾ��ԭʼ�����������ظ����ֵĽڵ㣬ֻ���²�ͬ������ ������ ����������� ��
	std::vector<int> data = { 1,1,2,2 };
	std::unique_ptr<ListNode> ptr = ListNode::new_list(data);
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
					if (cur == nullptr)return  static_cast<ListNode*>(nullptr);
					else {
						head = cur;
						prev = cur;
						root = cur;
					}
				}
				else
				{
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
		while (cur->next != nullptr and cur->next->next != nullptr)
		{
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

void LeetCode::three_num()
{
	// �ҵ����к�Ϊ 0�Ĳ��ظ�����Ԫ��
	std::vector nums = { -2,0,0,2,2 };

	auto answer = [&](const std::vector<int>& data)->std::vector<std::vector<int>> {
		if (nums.size() < 3)return {};
		// ��Ԫ������
		std::unordered_map<int, int> map;
		for (auto i : data) {
			if (map.find(i) == map.end())
			{
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
				//�ҵ���ǰ��Ԫ��Ϊ��һ��Ԫ��

				int take_time = -1;
				int value = -first;
				map[first] -= 1;
				bool if_not_match = true;
				for (auto second : data)
				{
					if (map[second] > 0) {
						//�ҵ��ԳƵ�����
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
				if (if_not_match)
				{
					map[first] += 1;
				}

			}
		}
		dbg(map);
		dbg(result);
		return result;

	};
	//answer(nums);

	auto sort_answer = [&](std::vector<int>& data)->std::vector<std::vector<int>> {
		std::vector<int>::size_type size = data.size();
		if (size < 3)return {};
		std::sort(data.begin(), data.end());
		int start = 0;

		std::vector<std::vector<int>> result;
		while (start < size - 2 and data[start] <= 0) {
			if (start > 0 and data[start] == data[static_cast<size_t>(start) - 1]) {
				start++;
				continue;
			} // ��ֱͬ�����𰸴�
			//data �Ѿ���������� �����������û��Ҫ�ټ�����ȥ��
			int left = start + 1;
			int right = static_cast<int>(size - 1);
			while (left < right)
			{
				int cur = data[left] + data[start] + data[right];
				//auto str = fmt::format("left{} right{} start{}", left, right, start);
				//dbg(str, cur);
				if (cur == 0) {
					//dbg(data[start], data[left], data[right]);
					result.emplace_back(std::vector<int>{data[start], data[left], data[right]});
					// ������ͬ��left ���������һ����ͬ��λ��
					while (left < right and data[left] == data[static_cast<size_t>(left) + 1])left++;
					while (left < right and data[right] == data[static_cast<size_t>(right) - 1])right--;
					left++;
					right--; //�������߶����ظ�����һ��ĵط�
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
	auto parm = vector<int>{ -1,0,1,2,-1,-4 };
	dbg(sort_answer(parm));
}

void LeetCode::fib()
{
	constexpr auto answer = [] {
		constexpr int n = 3;
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
