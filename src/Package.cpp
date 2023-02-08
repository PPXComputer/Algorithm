//
// Created by Administrator on 2022/5/8.
//

#include "Package.h"
#include <array>
#include <dbg.h>

#include <functional>
#include <vector>

using std::vector;
void Package::pack01() {

  // 01 背包问题

  std::array values{2, 4, 4, 5, 2};
  std::array volumes{1, 2, 3, 4, 5};
  constexpr int packVolume = 10;
  {
    std::vector<std::vector<int>> dp(values.size() + 1,
                                     std::vector<int>(packVolume + 1));
    auto answer_enum = [&](int rest, int index, int count, auto answer_dfs) {
      if (rest <= 0 || index == values.size())
        return count;
      int get = 0;
      if (rest >= volumes[index]) {
        get = answer_dfs(rest - volumes[index], index + 1,
                         count + values[index], answer_dfs);
      }
      return std::max(get, answer_dfs(rest, index + 1, count, answer_dfs));
    };
  }

  {
    // 暴力递归
    std::function<int(int, int, int)> impl = [&](int index, int value,
                                                 int amount) {
      if (index == volumes.size()) {
        if (amount >= 0) {
          return value;
        }
        return INT_MIN;
      }

      int get = impl(index + 1, value + values[index], amount - volumes[index]);
      int not_get = impl(index + 1, value, amount);
      return std::max(get, not_get);
    };

    impl(0, 0, packVolume);
  }
  {
    // 去除value 输入参数的暴力递归
    std::function<int(int, int)> impl = [&](int index, int bag) {
      if (bag < 0) {
        return -1;
      }
      if (index == volumes.size()) {
        return 0;
      }

      int res = impl(index + 1, bag - volumes[index]);
      if (res != -1) {
        res += values[index];
      }
      return std::max(impl(index + 1, bag), res == -1 ? 0 : res);
    };
    {
      vector<vector<int>> vt(volumes.size() + 1, vector<int>(packVolume + 1));

      for (int index = volumes.size() - 1; index >= 0; --index) {
        // std::for_each(vt[i].begin(), vt[i].begin() + volumes[i],
        // vt[i+1][]);
        for (int bag = 0; bag <= packVolume; ++bag) {
          if (bag < volumes[index]) {
            vt[index][bag] = vt[index + 1][bag];
          } else {
            vt[index][bag] =
                std::max(values[index] + vt[index + 1][bag - volumes[index]],
                         vt[index + 1][bag]);
          }
        }
      }
      dbg(vt[0][packVolume]);
    }

    // 只存在一层 依赖上一层
    {
      auto vt = vector<int>(packVolume + 1);
      auto vtDbg = vector<int>(packVolume + 1);
      vector<vector<int>> vtRes;
      vector<vector<int>> vtResDbg;
      for (int index = volumes.size() - 1; index >= 0; --index) {
        for (int bag = packVolume; bag >= volumes[index]; --bag) {
          vt[bag] = std::max(values[index] + vt[bag - volumes[index]], vt[bag]);
        }
        // 依赖部分应该是没有被使用的部分  从小到大 小的部分已经填上了最新的值了
        // 所以被覆盖了 不能用
        for (int bag = volumes[index]; bag <= packVolume; ++bag) {
          vtDbg[bag] =
              std::max(values[index] + vtDbg[bag - volumes[index]], vtDbg[bag]);
        }
        vtRes.emplace_back(vt);
        vtResDbg.emplace_back(vtDbg);
      }
      dbg(vt[packVolume]);
      dbg(vtDbg[packVolume]);
      dbg(vtRes, vtResDbg);
    }
  }
  //
}
