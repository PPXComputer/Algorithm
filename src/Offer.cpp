// Created by Administrator on 2022/3/21.
//

#include <cmath>
#include <string>
#include <vector>
#include <dbg.h>
#include <fmt/core.h>
#include <fmt/format.h>

using std::vector;
using std::string;

#include "../include/Offer.h"

int Offer::divide() {
    int a = 15, b = 2;
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
        if ((i & 1) == 1) { //奇数则 将当前的 存在的 转换为
            resultA.push_back(resultA[i >> 1] + 1);
        } else {
            resultA.push_back(resultA[i >> 1]);
        }
    }

    return 0;
}
