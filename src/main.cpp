#include"ListAglo.h"
#include "Offer.h"
#include"LeetCode.h"
#include "ArrayAlgo.h"
#include "StringAglo.h"
#include<EASTL/vector.h>

using std::string;
using folly::fbvector;
using std::string;

struct Factorial {
    static string factorial(const size_t n) {
        auto start = std::to_string(n);
        string &result = factorialImpl(start, 2, n);
        std::reverse(result.begin(), result.end());
        std::cout << result;
        return result;
    }

    //大数乘法 将得到两者相乘的数据实现
    static string big_number_multiply(const string &first, const size_t second) {
        assert(not first.empty());
        size_t t = 0;
        const size_t first_len = first.size();
        string result;
        result.reserve(first_len + 10);
        for (int i = 0; i < first_len || t; i++) {
            if (i < first.size()) {
                t += (static_cast<size_t>(first.at(i) - '0')) * second;
            }
            char getChar = t % 10 + '0';
            result.push_back(getChar);
            t /= 10;
        }
        return result;
    }

    static string &factorialImpl(string &first, size_t second, size_t target) {
        if (second >= target) return first;
        first = big_number_multiply(first, second);
        return factorialImpl(first, second + 1, target);
    }
};


int main() {
    //	Dynamic::package();
    //    TreeAlgo::run();
    //    Dynamic::winner();
    //    Dynamic::minimum_manipulate();
    //ArrayAlgo::not_exists_num();
    //StringAglo::find_longest_not_repeat_sub();
    //StringAglo::string_replace();
    //StringAglo::boolean_expression();
    //ArrayAlgo::change_array_data();
    //ArrayAlgo::JosephProblem();
    /*ArrayAlgo::longestTotalArray();*/
    //ArrayAlgo::longestTotalArray();
    //LeetCode::medium_34();
    //LeetCode::medium_33();
    //LeetCode::findPeakElement();
    //LeetCode::medium_74();
    //LeetCode::findMin();
    //LeetCode::deleteDuplicatesFromList();
    //LeetCode::three_num();
    //LeetCode::backspaceCompare/*(*/);
    //    LeetCode::findAnagrams();

    //LeetCode::numSubarrayProductLessThanK();

    //LeetCode200::shortestPathBinaryMatrix();
//	LeetCode200::solveRound();

//	LeetCode200::shortestPathBinaryMatrix();
//    LeetCode200::letterCombinations();
//    LeetCode200::generateParenthesisByBrackets();
//    LeetCode200::existInMesh();
//    LeetCode200::robOnStreet();
//LeetCode200::jumpGame();
//LeetCode200::longestPalindrome();
//    Offer::addBinary();
//Offer::threeSum();
//Offer::numSubarrayProductLessThanK();
//Offer::findMaxLengthWithSameCount();
//Offer::pivotIndex();
//Offer::NumMatrix();
//Offer::checkInclusion();
//    Offer::maxPathSum();

//    Offer::setZero();
//    Offer::groupAnagrams();
//    Offer::wordBreak();
//    LeetCode200::maxNum();
    Offer::containsNearbyAlmostDuplicate();
//    for (int i = 3; i < 200; i++) {
//        bool suc=true;
//        for (int j = 2; j < i; ++j) {
//            if (i % j == 0) {suc=false; break; }
//        }
//        if(suc)cout<<i<<" \n";
//    }
//    LeetCode::remove_all_words();
//LeetCode::largestCombination();
//LeetCode::findTargetSumWays();
//LeetCode::countLatticePoints();
//	std::cin.get();
//    ArrayAlgo::findKthBit();
//    StringAglo::wordBreak();
//    ArrayAlgo::salesRange();
//    ArrayAlgo::containsNearbyDuplicate();
    StringAglo::findRepeatedDnaSequences();
}


//#include <iostream>
//#include<type_traits>
//#include <vector>
//#include <algorithm>
//
//template<class T>
//constexpr std::decay_t<T>
//decay_copy(T&& v)
//noexcept(std::is_nothrow_constructible_v<T, std::decay_t<T>>)           // exposition only
//{
//	return std::forward<T>(v);
//}
//
//int main() {
//	std::vector<int> v1{ 1, 2, 1, 1, 1 };
//	auto v2 = v1;
//	v1.erase(
//		std::remove(begin(v1), end(v1), *std::max_element(begin(v1), end(v1))),
//		v1.end());
//	v2.erase(std::remove(
//		begin(v2), end(v2),
//		decay_copy(*std::max_element(begin(v2), end(v2)))),
//1		v2.end());
//	std::cout << "v1.size()=" << v1.size()<< "v2.size()=" << v2.size();
//}

