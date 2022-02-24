

#ifndef SSH_STRINGAGLO_H
#define SSH_STRINGAGLO_H

#include <iostream>
#include <string_view>
#include <utility>
#include "folly/FBString.h"
#include "folly/FBVector.h"
#include "folly/String.h"
#include <folly/Format.h>

using folly::fbstring;
using folly::fbvector;
using folly::Optional;
using std::string_view;
using std::addressof;
using std::cout;
using std::pair;

class StringAglo {
public:
    static fbstring sub_string_range();

    static void all_sub();

    static size_t exp_n(int n);

    static void string_compress();

    static void string_expression();

    static void find_longest_not_repeat_sub();

    static void string_replace();

    static void  boolean_expression();
private:
    static void printAll(const fbstring &cur, size_t index, const fbstring &data);
};


#endif //SSH_STRINGAGLO_H
