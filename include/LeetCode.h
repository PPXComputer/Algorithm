#pragma once
#include <string>
#include <vector>
#include<memory>
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
private:

	struct RawNode
	{
		RawNode() :val(0), next{ nullptr }{}
		explicit RawNode(int x) :val(x), next(nullptr) {}
		RawNode(int x, RawNode* raw_ptr) :val(x), next(raw_ptr) {}
		RawNode(const RawNode&) = delete;
		~RawNode() {
			while (next != nullptr)
			{
				auto last = next->next;
				delete next;
			}

		}
		static std::unique_ptr<RawNode> new_list(size_t length) {
			auto root = std::make_unique< RawNode>(0);
			for (size_t i = 1; i < length; i++)
			{
				root->next = new RawNode(i);
			}
			return root;
		}
		RawNode* next;
		int val;

	};

	struct ListNode
	{

		ListNode() :val(0), next{ nullptr }{}
		ListNode(int x) :val(x), next(nullptr) {}
		ListNode(int x, ListNode* raw_ptr) :val(x), next(raw_ptr) {}
		std::shared_ptr<ListNode> next;
		int val;

		static std::shared_ptr<ListNode> new_list(size_t length) {
			auto root = std::make_shared<ListNode>(0);
			for (size_t i = 1; i < length; i++)
			{
				root->next = std::make_shared<ListNode>(i);
			}
			return root;
		}
	};
};
