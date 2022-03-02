#pragma once
#include <string>
#include <vector>
#include<memory>
#include <cassert>
using std::vector;

class LeetCode
{
public:
	static void medium_33();
	static void medium_34();

	//. 搜索二维矩阵
	static void medium_74();

	// 25  k 个一组翻转链表
	static void reverseKGroup();
	//162 寻找峰值
	static void findPeakElement();

	// 153 找到旋转数组的的最小值
	static void findMin();

	//82. 删除排序链表中的重复元素 II
	static void		deleteDuplicatesFromList();

	//15. 三数之和
	static void three_num();
private:

	struct ListNode
	{
		ListNode() :val(0), next{ nullptr }{}
		explicit ListNode(int x) :val(x), next(nullptr) {}
		ListNode(int x, ListNode* raw_ptr) :val(x), next(raw_ptr) {}
		ListNode(const ListNode&) = delete;
		ListNode* next;
		int val;



		static std::unique_ptr<ListNode> new_list(size_t length) {
			assert(length != 0);
			auto result = std::make_unique<ListNode>(0);
			result->node.reserve(length - 1);
			auto root = result.get();
			for (size_t i = 1; i < length; i++)
			{
				root->next = new ListNode(i);
				root = root->next;
				result->node.emplace_back(root);
			}
			return result;
		}

		static std::unique_ptr<ListNode> new_list(const std::vector<int>& data) {
			if (data.empty())return nullptr;
			auto result = std::make_unique< ListNode>(data[0]);
			auto root = result.get();
			result->node.reserve(data.size() - 1);
			size_t size = data.size();
			for (size_t i = 1; i < size; i++)
			{
				root->next = new ListNode(data[i]);
				root = root->next;
				result->node.emplace_back(root);
			}
			return result;
		}
		~ListNode() {

			for (auto data : node) {
				delete data;
			}
		}
	private:

		std::vector<ListNode*> node = {};
	};


};
