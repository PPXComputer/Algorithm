//
// Created by Administrator on 2022/5/8.
//

#ifndef PACKAGE_H
#define PACKAGE_H

#include <vector>

class Package {
public:
    // 背包问题 汇总
    static void pack01();

    static void pack02();

    static void pack03();

    static void pack_416();

    static void pack322();

    static void pack_494();

    static void pack_198();

    static void pack_139();

    static void pack_476();

    static void pack_518();

    static void pack_279();

    static void pack_1049();

    static void longestCommntSub();

    // 63. 不同路径 II
    static void uniquePathsWithObstacles();

    static void jump();

    // 343. 整数拆分
    static void integerBreak();

    // 96. 不同的二叉搜索树 numTrees
    static void numTrees();

    // 474. 一和零
    static void findMaxForm();

    static std::vector<int> getVector(const std::array<int, 5> &nums);

    static std::vector<int> getVector3(const std::vector<int> &nums);

    static std::vector<int> getVector4(const std::vector<int> &nums);
};

#endif // PACKAGE_H
