// Created by Administrator on 2022/3/21.
//

#include <cmath>
#include <string>
#include <random>
#include <set>
#include <numeric>
#include <vector>
#include <dbg.h>
#include <fmt/core.h>

#include<unordered_map>
#include "Offer.h"

using std::vector;
using std::set;
using std::string;
using std::unordered_map;


int Offer::divide() {
    int a = 15;
    int b = 2;
    bool negative = true;
    if (a < 0 and b < 0) negative = false;
    a = std::abs(a);
    b = std::abs(b);

    int answer = a / b;
    return 0;
}

int Offer::addBinary() {
    string first = "10";
    string second = "101111";
    size_t secondSize = second.size();
    size_t firstSize = first.size();
    std::string result;
    if (firstSize >= secondSize) {
        std::swap(first, second);
        std::swap(firstSize, secondSize);
    }

    bool isMetric = false;
    result.reserve(secondSize + 1);
    int firstIndex = firstSize - 1;
    int secondIndex = secondSize - 1;
    while (firstIndex >= 0) {
        int addNum = 0;
        if (isMetric) {
            addNum = first[firstIndex] + second[secondIndex] - '0' * 2 + 1;

        } else {
            addNum = first[firstIndex] + second[secondIndex] - '0' * 2;

        }
        dbg(addNum);
        if (addNum >= 2) {
            result.push_back(addNum + '0' - 2);
            isMetric = true;
        } else {
            result.push_back('0' + addNum);
            isMetric = false;
        }
        --firstIndex;
        --secondIndex;
    }

    dbg(result);
    while (secondIndex >= 0) {
        if (isMetric) {
            char addNum = 0;
            addNum = static_cast<char>(second[secondIndex] - '0' + 1);
            if (addNum == 2) {
                isMetric = true;
                result.push_back('0');
            } else {
                result.push_back('1');
                --secondIndex;
                while (secondIndex >= 0) {
                    result.push_back(second[secondIndex]);
                    --secondIndex;
                }
                isMetric = false;
            }
        } else {
            result.push_back(second[secondIndex]);
        }
        --secondIndex;
    }
    if (isMetric) {
        result.push_back('1');
    }


    std::reverse(result.begin(), result.end());
    dbg(result);


    vector<int> resultA;
    int newCapacity = 80;
    resultA.reserve(newCapacity);

    resultA.push_back(0);
    for (int i = 1; i < newCapacity; ++i) {
        if ((i & 1) == 1) { //????????? ???????????? ????????? ?????????
            resultA.push_back(resultA[i >> 1] + 1);
        } else {
            resultA.push_back(resultA[i >> 1]);
        }
    }


    return 0;
}

void Offer::singleNum() {
    std::vector<int> nums{0, 1, 0, 1, 0, 1, 99};
    std::sort(nums.begin(), nums.end());
    int count = 1;
    int last = nums[0];
    for (auto start = nums.begin() + 1; start != nums.end(); ++start) {
        if (*start == last) {
            count++;
        } else {
            if (count == 1) {
                dbg(last);
                break;
            }
            count = 1;
            last = *start;
        }
    }
    //    dbg(nums.back());
    std::vector<std::string> words = {"abcw", "baz", "foo", "bar", "xtfn", "abcdef"};
    size_t n = words.size();
    auto masks = std::vector<int>(n);
    for (int i = 0; i < n; ++i) {
        dbg(masks[i]);
    }
    int res = 0;
    for (int i = 0; i < n; i++) {
        int bitMask = 0;
        for (char c: words[i]) {
            bitMask |= (1 << (c - 'a'));
        }
        masks[i] = bitMask;
        dbg(masks[i]);
    }

}

void Offer::threeSum() {
    //    std::unordered_map<int, int> mMap;
    //    for (int i: data) {
    //        mMap[i]++;
    //    }
    //    size_t size = data.size();
    //    vector<vector<int>> result;
    //    for (int i = 0; i + 2 < size; ++i) {
    //        int first = data[i];
    //        if (mMap[first] > 0) {
    //            --mMap[first];
    //            bool isSuccess = false;
    //            for (int j = i + 1; j + 1 < size; ++j) {
    //
    //                int second = data[j];
    //                if (mMap[second] > 0) {
    //                    --mMap[second];
    //                    int third = -i - j;
    //                    if (mMap[third] > 0) {
    //                        --mMap[third];
    //                        isSuccess = true;
    //                        result.emplace_back(std::vector<int>{first, second, third});
    //                    } else {
    //                        ++mMap[second];
    //                    }
    //                }
    //
    //            }
    //            if (not isSuccess) {
    //                ++mMap[first];
    //            }
    //        }
    //    }
    //threeSumFirstAnswer(data);


    std::vector<int> data{-2, 0, 1, 1, 2};
    // threeSumSecondAnswer(data);
    // ??????  sort ??????????????????????????? ????????? 
    auto answer = [&data]()mutable {
        std::sort(data.begin(), data.end());
        auto size = std::size(data);
        dbg(data);
        std::vector<std::vector<int>> results;
        int left = 1;
        int right = size - 1;
        for (int i = 0; i < size;) {
            int cur = data[i];

            dbg(i, left, right);
            bool isFind = false;
            while (left < right) {

                const string &basicString = fmt::format("{} {} {}", cur, data[left], data[right]);
                dbg(basicString);
                //????????????????????????????????????
                int curResult = data[left] + data[right] + cur;

                if (curResult > 0) {
                    --right;
                } else if (curResult < 0) {
                    ++left;
                } else {
                    results.emplace_back(std::vector<int>{cur, data[left], data[right]});
                    isFind = true;
                    break;
                }
            }
            if (i + 1 < size and data[i + 1] == data[i]) {
                while (i + 1 < size and data[i + 1] == data[i])
                    ++i;
            } else {
                ++i;
            }
            if (isFind)
                right = right - 1;
            left = i + 1;
        }
        dbg(results);
    };

    auto otherAnswer = [&data]()mutable {
        std::vector<std::vector<int>> result;
        std::sort(data.begin(), data.end());
        auto size = std::size(data);

        // ???????????????
        //1. ???????????????   ?????? -1,-1,0,0,1,1   -1,0,1 ????????? left???0 ?????????????????????0?????????
        //2. ???????????????????????? -2,-1,0,2,3    -2 0 2   -2  -1  3 ?????????????????????left ???????????????????????? ????????????????????????

        for (int i = 0; i < size; ++i) {
            if (i > 0 and data[i - 1] == data[i]) continue;
            int left = i + 1;
            int right = size - 1;
            while (left < right) {
                int curResult = data[left] + data[i] + data[right];
                if (curResult == 0) {
                    result.emplace_back(std::vector<int>{data[i], data[left], data[right]});
                    while (left < right and data[left] == data[1 + left])++left;
                    ++left; //??????????????? left ??????????????????
                    continue;
                } else if (curResult < 0) {
                    ++left;
                } else {
                    --right;
                }
            }
        }
        dbg(result);
    };
    otherAnswer();
}

void Offer::threeSumSecondAnswer(vector<int> &data) {
    std::unordered_map<int, int> mMap;
    for (int i: data) {
        mMap[i]++;
    }
    std::vector<std::vector<int>> results;
    auto size = data.size();
    for (int i = 0; i < size; ++i) {
        int cur = data[i];
        if (mMap[cur] > 0) {
            --mMap[cur];
            bool isSuccess = false;
            for (int j = i + 1; j < size; ++j) {
                int first = data[j];
                if (mMap[first] > 0) {
                    --mMap[first];
                    const auto &iterator = mMap.find(-cur - first);
                    if (iterator != mMap.end() and ((*iterator).second > 0)) {
                        dbg(*iterator);
                        results.emplace_back(std::vector<int>{cur, first, (*iterator).first});
                        isSuccess = true;
                        continue;
                    }
                    ++mMap[first];
                }
            }

            if (not isSuccess) {
                ++mMap[cur];
            }
        }
        // ?????????????????????


    }
    dbg(results);
}

void Offer::threeSumFirstAnswer(std::vector<int> &data) {
    std::vector<std::vector<int>> result;
    std::sort(data.begin(), data.end());
    int size = data.size();
    for (int i = 0; i < size; ++i) {

        while (i + 1 < size and data[i] == data[i + 1]) {
            ++i;
        }
        int left = i + 1;
        int right = size - 1;
        while (left < right) {
            if (data[i] + data[left] + data[right] == 0) {
                dbg(data[i], data[left], data[right]);
                result.emplace_back(std::vector<int>{data[i], data[left], data[right]});
                left++;
                right--;
                continue;
            } else if (data[i] + data[left] + data[right] > 0) {
                --right;
            } else {
                ++left;
            }
        }
    }
}

void Offer::minSubArrayLen() {
    // ????????????
    std::vector<int> data{2, 3, 1, 2, 4, 3};
    int target = 7;
    auto size = data.size();
    int right = 0;
    int curResult = data[0];
    int result = INT_MAX;
    int left = 0;
    while (left <= right and right < size) {
        if (curResult < target) {
            ++right;
            if (right < size)curResult += data[right];
        } else if (curResult >= target) {
            int curRange = right - left + 1;
            if (result > curRange) {
                result = curRange;
            }
            curResult -= data[left];
            ++left;
        }
    }
    dbg(result);

}

void Offer::numSubarrayProductLessThanK() {
    //??????????????????????????? nums????????? k ???????????????????????????????????? k ?????????????????????????????????
    // ?????????????????? 1850 ?????????4 ???????????????????????? 1+2+3+4   ????????????[fast-slow+1]
    auto answer = [] {
        std::vector<int> data{10, 5, 2, 6};
        int k = 100;
        int fast = 0;
        int slow = 0;
        auto size = data.size();
        int tmp = 1;
        int result = 0;
        //????????????????????????fast ???????????? ??????????????????????????? ????????????
        while (fast < size) {
            // ????????? result += fast  -slow+1  (fast ???????????????)
            if (data[fast] * tmp < k) {
                tmp *= data[fast];
                ++fast;
                result += fast - slow;
            } else {
                // tmp ?????? slow????????? slow?????????  slow+1
                // ?????? ?????????????????????????????????????????? fast??? slow????????????+1
                tmp /= data[slow];
                if (fast == slow) {
                    ++fast;
                }
                ++slow;
            }
        }

        return result;
    };
//    dbg(answer());
    auto answerSumk = [] {
        vector<int> data{1, 1, 1};
        int k = 2;
        int size = data.size();
        // ???????????????????????????????????????  ??????????????????????????????????????????
        // ????????? ??????????????????????????? ???????????? ????????????
        // ?????? ????????????????????????
        int preSum = 0;

        // ?????????????????? ?????????????????? ???k???????????????????????????
        std::unordered_map<int, int> map;
        map.reserve(size + 1);
        map[0] = 1;
        int result = 0;
        for (int i = 0; i < size; ++i) {
            preSum += data[i];
            dbg(map, preSum);
            const auto &findIterator = map.find(preSum - k);
            if (findIterator != map.end()) {
                result += findIterator->second;
            }
            ++map[preSum];
        }
        return result;
    };
    dbg(answerSumk());
}

void Offer::findMaxLengthWithSameCount() {
    //??????????????????????????? nums , ??????????????????????????? 0 ??? 1 ????????????????????????????????????????????????????????????
    // ???????????????????????? ??????????????????????????? ???????????????0 ????????????????????????
    // 0,1 ???????????? ????????????????????????
    std::vector<int> data{0, 1};
    auto size = data.size();
    {

        int countSum = data[0];
        std::vector<int> countCache;
        countCache.reserve(size + 1);
        countCache.push_back(0);
        int result = 0;
        for (int i = 0; i < size; ++i) {
            int cur = data[i] ? 1 : -1;
            countCache.push_back(cur + countCache[i]);
        }
        dbg(countCache);
    }

    {
        std::unordered_map<int, int> mMap;
        mMap.reserve(size + 1);
        mMap.insert({0, 0});
        int count = 0;
        int result = 0;
        for (int i = 0; i < size; ++i) {
            count += data[i] ? 1 : -1;

            auto iterator = mMap.find(count);
            if (iterator != mMap.end()) {
                result = std::max(result, i - iterator->second + 1);
            } else {
                // ?????????????????? ?????????????????? ????????? i
                mMap[count] = i;
            }

        }
        dbg(result);
    }
}

int Offer::pivotIndex() {
    /*
     * ???????????????????????? nums ????????????????????? ???????????? ???

    ?????? ???????????? ???????????????????????????????????????????????????????????????????????????????????????????????????

     */
    auto a = [] {
        std::vector<int> data{1, 7, 3, 6, 5, 6};
        dbg(data);
        auto size = data.size();

        if (size == 1) return -1;

        std::vector<int> sumCache;
        sumCache.reserve(size);
        int sum = 0;
        for (int i = 0; i < size; ++i) {
            sum += data[i];
            sumCache.emplace_back(sum);
        }
        if (sum - data[0] == 0) {
            return 0;
        }
        dbg(data);
        // ???????????? ?????????????????????
        dbg(sumCache);
        for (int i = 1; i < size; ++i) {
            dbg(sum - sumCache[i], sumCache[i - 1]);
            if (sum - sumCache[i] == sumCache[i - 1])return i;
        }
        return -1;
    };
    auto b = [] {
        std::vector<int> data{1, 7, 3, 6, 5, 6};
        auto size = data.size();
        int total = std::accumulate(data.begin(), data.end(), 0);
        int sum = 0;
        for (int i = 0; i < size; ++i) {
            sum += data[i];
            if (total - sum == sum - data[i]) {
                return i;
            }
        }
        return -1;
    };
//    return a();

    std::vector<std::vector<int>> sumCache{};
    sumCache.emplace_back(std::vector<int>{-4});
    sumCache.emplace_back(std::vector<int>{-5});
    int row = sumCache.size();
    int col = sumCache[0].size();
    for (int i = 0; i < row; ++i) {
        for (int j = 1; j < col; ++j) {
            sumCache[i][j] += sumCache[i][j - 1];
        }
    }
    int result = 0;
    int row1 = 0;
    std::random_device device; //??????????????????????????????
    std::default_random_engine e{device()}; //??????????????????
    // ???????????? ???????????????????????? ???????????????
    std::binomial_distribution<int> distribution(3, 2);
    int col1 = distribution(e) % 2 ? 0 : 1;
    int row2 = 0;
    int col2 = 1;
    for (int i = row1; i <= row2; ++i) {
        if (col1 != 0) {
            result += sumCache[i][col2] - sumCache[i][col1 - 1];
        } else {
            result += sumCache[i][col2];
        }
    }
    dbg(result);
    return 0;
}

int Offer::NumMatrix() {
    vector<vector<int>> matrix{{-4, -5},
                               {1,  2}};
    int row = matrix.size();
    int col = matrix[0].size();
    auto answer = [&matrix, row, col] {

        std::vector<std::vector<int>> preSum(row + 1, std::vector<int>(col + 1));
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                preSum[i + 1][j + 1] = preSum[i][j + 1] + preSum[i + 1][j] - preSum[i][j] + matrix[i][j];
            }
        }

        auto sumRegion = [&](int row1, int col1, int row2, int col2) {
            ++row1;
            ++col1;
            ++row2;
            ++col2;
            return preSum[row2][col2] + preSum[row1 - 1][col1 - 1] - preSum[row1 - 1][col2] - preSum[row2][col1 - 1];
        };
        dbg(preSum);

        dbg(sumRegion(0, 0, 1, 1));
        int row1 = 1;
        int col1 = 1;
        int row2 = 2;
        int col2 = 2;
        dbg(preSum[row2][col2], preSum[row1 - 1][col1 - 1], preSum[row1 - 1][col2], preSum[row2][col - 1]);
    };


    auto inPlaceAnswer = [&matrix, row, col] {

        for (int i = 1; i < row; ++i) {
            matrix[i][0] += matrix[i - 1][0];
        }
        for (int j = 1; j < col; ++j) {
            matrix[0][j] += matrix[0][j - 1];
        }
        for (int i = 1; i < row; ++i) {
            for (int j = 1; j < col; ++j) {
                matrix[i][j] += matrix[i - 1][j] + matrix[i][j - 1] - matrix[i - 1][j - 1];
            }
        }
        dbg(matrix);

    };
    inPlaceAnswer();
    return 0;
}

void Offer::checkInclusion() {
    //????????????????????? pattern ??? text??????????????????????????? text ???????????? pattern ?????????????????????
    //???????????????????????????????????????????????????????????????????????? ?????? ???
    //pattern = "ab" text = "eidbaooo" true

    auto answer = [] {
        string pattern = "ab";

        string text = "eidboaoo";
        const int patternLen = pattern.size();
        const int textLen = text.size();

        std::vector<int> data(26);
        for (int i = 0; i < patternLen; ++i) {
            ++data[pattern[i] - 'a'];
        }
        int left = 0;

        int right = left;
        while (right < textLen) {
            dbg(data);
            int curPos = text[right] - 'a';
            --data[curPos];
            while (data[curPos] < 0) {
                int leftPos = text[left] - 'a';
                ++data[leftPos];
                ++left;
            }

            //????????????????????????
            // ???????????????????????? ??????????????? right-left+1 < patternLen
            if (patternLen == right - left + 1) {
                return true;
            }
            ++right;
        }
        return false;
    };
    dbg(answer());
}

int Offer::lengthOfLongestSubstring(string &s) {
    std::array<int, 256> cache{};
    const int length = s.length();
    int left = 0;
    int right = 0;
    int result = 0;
    while (right < length) {
        const char cur = s[right];
        ++cache[cur];
        while (cache[cur] > 1) {
            const char leftPos = s[left];
            --cache[leftPos];
            ++left;
        }
        result = std::max(right - left + 1, result);
        ++right;
    }
    return result;
}

int Offer::countSubstrings() {
    // ?????????????????????
    string varString = "abababaadhqjqqq";
    const int len = varString.length();
    int result = 0;
    // ???????????? ?????? ??? len ???
    // ????????? ????????? ??? len-1 ??? ??????  2*len-1
    for (int cur = 0; cur < 2 * len - 1; ++cur) {
        int left = cur / 2;
        // right ????????? ????????????????????????
        // right ?????????????????? ???????????? ????????? ?????? ????????????
        int right = left + cur % 2;
        while (right < len and left >= 0 and varString[left] == varString[right]) {
            --left;
            ++right;
            ++result;
        }
    }
    return result;
}

void Offer::removeNthFromEnd() {
    const std::unique_ptr<ListNode> &ptr = Offer::ListNode::new_list(10);
    auto root = ptr.get();
    ListNode::printAll(root);
    auto a = ListNode(0, root);
    auto dummy = std::addressof(a);
    int n = 2;

    auto first = dummy;
    auto second = dummy;
    while (n-- != 0) {
        second = second->next;
    }
    while (second != nullptr) {
        second = second->next;
        first = first->next;
    }
    first->next = first->next->next;
    // dummy->left;
}

void Offer::maxPathSum() {
    // ???????????????????????????
    // ??????????????????????????? ????????????????????? ??? ????????????????????????

    int maximum = INT_MIN;


    fbstring str{"[1,-2,-3,1,3,-2,#,-1]"};
    auto a = TreeNode::newTree(str);
    int result = INT_MIN;
    auto answer = [&result](TreeNode *root, auto &&answer) {


        if (root == nullptr)return 0;

        int maxLeft = std::max(0, answer(root->left, answer));
        int maxRight = std::max(0, answer(root->right, answer));
        int curResult = std::max({root->val, root->val + maxLeft, root->val + maxRight});

        // ??????????????? ???????????? ?????? ???????????????  root+left+right??????????????????????????????
        result = std::max({maxLeft + maxRight + root->val, curResult, result});
        return curResult;
    };
    dbg(answer(a.get(), answer));
}

void Offer::setZero() {
    //???????????? m x n ????????????????????????????????? 0 ??????????????????????????????????????????????????? 0 ???????????? ?????? ?????????
    vector<vector<int>> matrix{{0, 1, 2, 0},
                               {3, 4, 5, 2},
                               {1, 3, 1, 5}};


    auto answer = [&matrix]() mutable {
        auto row = matrix.size();
        auto col = matrix[0].size();
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                if (matrix[i][j] == 0) {
                    matrix[i][j] = INT_MIN;
                    // search in different row and col
                    for (int next = 0; next < col; ++next) {
                        if (next == j) continue;
                        if (matrix[i][next] != 0)
                            matrix[i][next] = 0;
                        else
                            matrix[i][next] = INT_MIN;
                    }
                    break;
                }
            }
        }
        dbg(matrix);
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                if (matrix[i][j] == INT_MIN) {
                    for (int k = 0; k < row; ++k) {
                        matrix[k][j] = 0;
                    }
                }

            }
        }

    };


//    answer();
//    dbg(matrix);
    dbg(matrix);
    auto answer_without_space = [&]() {
        auto row = matrix.size();
        auto col = matrix[0].size();
        // ??????????????? ????????? ????????? ????????????
        auto iterator = std::find(matrix.front().begin(), matrix.front().end(), 0);
        bool findZeroInFirstRow = iterator != matrix.front().end();

        bool findZeroInFirstCol = std::find_if(matrix.begin(),
                                               matrix.end(),
                                               [](const std::vector<int> &data) { return data[0] == 0; }) !=
                                  matrix.end();

        // ?????????????????? ????????????   ?????????  0??? ??? 0????????????  ????????? ????????? ?????????
        for (int i = 1; i < row; ++i) {
            for (int j = 1; j < col; ++j) {
                if (matrix[i][j] == 0) {
                    matrix[i][0] = 0;
                    matrix[0][j] = 0;
                }
            }
        }
        dbg(matrix);
        // ??????
        for (int j = 1; j < col; ++j) {
            if (matrix[0][j] == 0) {
                for (int i = 1; i < row; ++i) {
                    matrix[i][j] = 0;
                }
            }
        }
        // ????????????????????????  ??????
        for (int i = 1; i < row; ++i) {
            if (matrix[i][0] == 0) {
                for (int j = 1; j < col; ++j) {
                    matrix[i][j] = 0;
                }
            }
        }


        if (findZeroInFirstRow) {
            for (int j = 0; j < col; ++j) matrix[0][j] = 0;
        }
        if (findZeroInFirstCol) {
            for (int i = 0; i < row; ++i) matrix[i][0] = 0;
        }

        dbg(matrix);

    };

    answer_without_space();

    dbg(matrix);
}

void Offer::groupAnagrams() {
    // ["eat", "tea", "tan", "ate", "nat", "bat"]
    //vector<string> data = {"eat", "tea", "tan", "ate", "nat", "bat"};
    auto answer_ = [](std::vector<string> &data) -> std::vector<std::vector<string>> {
        if (data.empty()) return {};
        auto size = data.size();
        std::unordered_map<int, std::vector<int>> map;
        for (int i = 0; i < size; ++i) {
            int count = 0;
            for (char ch: data[i]) {
                count = count | (1 << (ch - 'a'));
            }
            if (map.find(count) == map.end()) {
                map[count] = std::vector<int>{i};
            } else {
                map[count].emplace_back(i);
            }
        }
        dbg(map);
        std::vector<std::vector<std::string >> result;
        result.resize(map.size());
        int curIndex = 0;
        for (const auto &cur: map) {
            const auto &ele = cur.second;
            for (const int index: ele) {
                result[curIndex].emplace_back(std::move(data[index]));
            }
            ++curIndex;
        }
        dbg(result);
        return result;

    };
//    answer_(data);
    auto answer_other = [](std::vector<string> &data) -> std::vector<std::vector<string>> {
        if (data.empty()) return {};
        auto size = data.size();

        std::unordered_map<string, std::vector<std::string>> map;
        for (int i = 0; i < size; ++i) {
            string basicString{};
            basicString.resize(26);
            for (char ch: data[i]) {
                ++basicString[ch - 'a'];
            }
            if (map.find(basicString) != map.end()) {
                map[basicString].emplace_back(std::move(data[i]));
            } else {
                map[basicString] = std::vector<string>{std::move(data[i])};
            }
        }
        std::vector<std::vector<std::string >> result;
        result.reserve(map.size());
        for (auto &&sd: map) {
            result.emplace_back(std::move(sd.second));
        }
        return result;
    };
//    std::hash<int> fn{};
//    dbg(fn(10));
//    //
    auto answer_hashmap = [](std::vector<string> data) -> std::vector<std::vector<string>> {
        std::unordered_map<std::string, std::vector<std::string >> container;
        for (std::string &cur: data) {
            auto copy = cur;
            std::sort(cur.begin(), cur.end());
            container[cur].emplace_back(std::move(copy));
        }
        std::vector<std::vector<string>> result;
        result.reserve(container.size());
        for (auto &&item: container) {
            result.emplace_back(std::move(item.second));
        }
        return result;
    };
    // ??????????????????  ?????? hash ????????? ????????????????????????????????? ????????? ????????????
    auto answer_order = [](std::vector<std::string> &data1) {
        std::vector<int> result;
        result.reserve(data1.size());
        std::array<int, 26> order = {2, 3, 5, 7, 11, 13,
                                     17, 19, 23, 29, 31, 37,
                                     41, 43, 47, 53, 59, 61,
                                     67, 71, 73, 79, 83, 89,
                                     97, 101};
        for (const auto &item: data1) {
            int t = 1;
            for (const char ch: item) {
                t *= order[ch - 'a'];
            }
            result.emplace_back(t);
        }
    };

}

void Offer::toGoatLatin() {
    //824 ???????????????
    auto answer_latin = [](std::string &data) {

        std::stringstream stream(data);
        std::string word;
        int idx = 1;
        std::string result;
        while (stream >> word) {
            if (word[0] == 'a' || word[0] == 'e' || word[0] == 'i' || word[0] == 'o' || word[0] == 'u') {

            }
        }

    };
}

void Offer::wordBreak() {

    /*
     * ????????????????????? s ???????????????????????? wordDict ????????????(??????????????????????????????)?????????????????????????????????????????????????????????????????? s ???
        ?????????????????????????????????????????????????????????????????????????????????????????????????????????
        ??????: s = "leetcode", wordDict = ["leet", "code"]
        ??????: true
        ??????: ?????? true ?????? "leetcode" ????????? "leet" ??? "code" ????????????
     */

    vector<string> wordDict1 = {"leet", "code"};
    std::string cur1 = "leetcode";
    // ??????????????????
    auto answer_word = [](const std::vector<string> &data, std::string &word) {
        auto answer_impl = [&](int dataIndex, int wordIndex, auto answer_impl) {
            int wordSize = word.size();
            if (wordIndex == wordSize)return true;
            if (dataIndex >= data.size())return false;
            // ????????????????????????????????????
            int howManyLeft = wordSize - wordIndex;
            int curWordSize = data[dataIndex].size();
            int matchTime = howManyLeft / curWordSize;
            if (word.compare(wordIndex, curWordSize, data[dataIndex]) == 0) {
                return false;
            }
            for (int i = 0; i < matchTime; ++i) {
                if (answer_impl(dataIndex + 1, wordIndex + curWordSize * (i + 1), answer_impl))return true;
            }
            return false;
        };


    };

    // ???????????????

    struct TrieNode {
        std::unique_ptr<TrieNode> next[26]{};
        bool isEnd = false;
    };

    // ??????
    TrieNode root;
    {
        for (const string &word: wordDict1) {
            TrieNode *p = std::addressof(root);
            for (char ch: word) {
                int curPos = ch - 'a';
                if (p->next[curPos] == nullptr) {
                    p->next[curPos] = std::make_unique<TrieNode>();
                }
                p = p->next[curPos].get();

            }
            p->isEnd = true;
        }
    }
    bool failMemo[301]{false}; //// ??????dfs?????????????????????s??????index
    auto answer_dfs = [&failMemo](std::string &word, int startPos, const TrieNode &root, auto answer_dfs) {
        if (failMemo[startPos])return false;
        int wordSize = word.size();
        if (startPos == wordSize)return true;
        const TrieNode *p = std::addressof(root);
        for (int i = startPos; i < wordSize; ++i) {
            int curWordIndex = word[i] - 'a';
            if (p->next[curWordIndex] != nullptr) {
                p = p->next[curWordIndex].get();
                if (p->isEnd and answer_dfs(word, i + 1, root, answer_dfs))return true;
            } else break;
        }
        failMemo[startPos] = true; // ??????????????????????????????
        return false;
    };

}





