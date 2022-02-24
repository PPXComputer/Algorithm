#include"../include/ListAglo.h"
#include"../include/ArrayAlgo.h"
#include "../include/Dynamic.h"
#include"../include/GreedyAlgo.h"
#include "../include/StringAglo.h"
#include"../include/TreeAlgo.h"
#include "dbg.h"
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

    //�����˷� ���õ�������˵�����ʵ��
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
    ArrayAlgo::longestTotalArray();
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
//		v2.end());
//	std::cout << "v1.size()=" << v1.size()<< "v2.size()=" << v2.size();
//}