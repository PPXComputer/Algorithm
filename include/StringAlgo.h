

#ifndef STRINGALGO_H
#define STRINGALGO_H

#include <folly/FBString.h>



class StringAlgo {
public:
    static folly::fbstring sub_string_range();

    static void all_sub();

    static size_t exp_n(int n);

    static void string_compress();

    static void string_expression();

    static void find_longest_not_repeat_sub();

    static void string_replace();

    static void boolean_expression();

    static void expression();

    static void wordBreak();

    static void searchWord();

    static void minWindows();

    // leetcode 187
    static void findRepeatedDnaSequences();

    static void Rabin_Karp(); // 从数组找到匹配的模式串的方法

private:
    static void printAll(const folly::fbstring &cur, size_t index, const folly::fbstring &data);
};


#endif // STRINGALGO_H
