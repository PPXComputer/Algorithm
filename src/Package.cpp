//
// Created by Administrator on 2022/5/8.
//

#include "Package.h"
#include<array>
#include<vector>

void Package::pack01() {
    // 01 背包问题

    std::array values{2, 4, 4, 5, 2};
    std::array volumes{1, 2, 3, 4, 5};
    constexpr int packVolume = 10;
    std::vector<std::vector<int>> dp(values.size() + 1, std::vector<int>(packVolume + 1));
    auto answer_enum = [&](int rest, int index, int count, auto answer_dfs) {
        if (rest <= 0 or index == values.size())return count;
        int get = 0;
        if (rest >= volumes[index]) {
            get = answer_dfs(rest - volumes[index], index + 1, count + values[index], answer_dfs);
        }
        return std::max(get, answer_dfs(rest, index + 1, count, answer_dfs));
    };
    //
}
