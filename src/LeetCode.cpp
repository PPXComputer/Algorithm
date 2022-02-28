#include "../include/LeetCode.h"
#include <dbg.h>
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
				if (target <= nums[right]) {

					while (mid != nums.size())
					{
						if (target == nums[mid])return mid;
						mid++;
					}
				}
				else {
					//向左边找
					right = mid - 1;
				}

			}
			else { //左侧有序
				if (target >= nums[left]) {

					while (mid > 0)
					{
						if (target == nums[mid])return mid;
						mid--;
					}
					
				}
				else {
					//向右边找
					left = mid + 1;
				}
			}
		}
		if (nums[left] != target)return -1;
		return left;
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
				right = mid;
			}
		}
		if (nums[left] != target)return { -1,-1 };
		int left_result = left;
		left = 0; right = static_cast<int>(nums.size() - 1);

		while (left < right) {
			//找到最后一个出现target的地方
			int mid = left + ((right - left) >> 1) + 1; //向右侧偏移一格
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
