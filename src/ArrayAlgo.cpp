#include "ArrayAlgo.h"

#include <dbg.h>
#include <fmt/format.h>
#include <folly/FBString.h>
#include <folly/FBVector.h>
#include <folly/Optional.h>
#include <folly/String.h>

#include <algorithm>
#include <array>
#include <memory>
#include <numeric>
#include <queue>
#include <random>
#include <utility>
#include <vector>
#include <stack>
#include "GreedyAlgo.h"

using fmt::format;
using folly::fbstring;
using folly::fbvector;
using folly::Optional;

using std::addressof;
using std::cout;

void ArrayAlgo::huffman_tree()
{
    const auto &getFibonacci = [](int end)
    {
        std::vector<int> result;
        result.reserve(end);
        int start = 0;
        while (start != end)
        {
            if (start == 0 || start == 1)
            {
                result.push_back(1);
            }
            else
            {
                size_t len = result.size();
                result.push_back(result[len - 1] + result[len - 2]);
            }
            start += 1;
        }
        return result;
    };

    std::vector data = getFibonacci(10);
    for (int i : data)
        cout << i << " ";
    cout << "\n";
    std::make_heap(data.begin(), data.end());
    while (data.size() != 1)
    {
        std::pop_heap(data.begin(), data.end());
        int first = data.back();
        data.pop_back();

        std::pop_heap(data.begin(), data.end());
        int second = data.back();
        data.pop_back();

        cout << fmt::format("first {} second :{} \n", first, second);
        data.push_back(first + second);
        std::push_heap(data.begin(), data.end());
    }
}

void ArrayAlgo::long_increase_sub_array()
{
    std::array data = {3, 1, 2, 6, 3, 4, 0};

    // 1 2 3 4
    std::array<int, 7> dp{1};
    constexpr size_t len = data.size();
    for (int i = 1; i < len; i++)
    {
        dp.at(i) = 1;
        for (int j = 0; j < i; j++)
        {
            if (data.at(j) < data.at(i) && dp.at(j) + 1 > dp.at(i))
            {
                dp.at(i) = dp.at(j) + 1;
            }
        }
    }
    std::cout << fmt::format("dp {}", folly::join(',', dp));
}

void ArrayAlgo::data_array()
{
    std::array data = {1, 3, 4, 3};
    std::unordered_map<int, int> map;
    for (const int &ref : data)
    {
        if (map.find(ref) != map.cend())
        {
            std::cout << "result: " << ref;
            break;
        }
        map.insert({ref, 1});
    }
    constexpr auto len = data.size();
    for (int i = 1; i < len; i++)
    {
        std::swap(data[i], i);
        //			if () {
        //
        //			}
    }
}

void ArrayAlgo::not_exists_num()
{
    // 连续序列中未出现的数字
    std::array<int, 7> data = {3, 2, 1, 6, 2, 7, 5}; // 1-n
    //                          0 1 2 3 4 5 6
    size_t cur = 0;
    constexpr auto size = data.size();
    while (cur < size)
    {
        int cur_value = data[cur];
        size_t promise_pos = static_cast<size_t>(cur_value) - 1;
        if (cur + 1 == cur_value)
        {
            cur += 1;
        }
        else
        {
            int swap_value = data[promise_pos];
            if (swap_value != cur_value)
            {
                std::swap(data[cur], data[promise_pos]);
            }
            else
            {
                // 当前的位置的值为重复的
                fmt::print("result data :{}", promise_pos + 1);
                break;
            }
        }
        fmt::print("cur array {} pos:{}\n", fmt::join(data, ","), cur);
    }
}

void ArrayAlgo::coin_change()
{
    int cur = 6;
    int target = 10;
    constexpr int add_spend = 120;
    constexpr int multiply_spend = 500;
    constexpr int subtract_spend = 140;

    auto fault = [=](int coin, int end, auto &&self) -> int
    {
        if (coin == end)
        {
            return 0;
        }
        // 递归中的重复范围会将重新出现 导致无限递归
        auto subtract = self(coin - 2, end, self) + subtract_spend;
        auto add = self(coin + 2, end, self) + add_spend;
        auto multiply = self(coin * 2, end, self) + multiply_spend;
        return std::min({subtract, add, multiply});
    };

    int maxCoin = target * 2;
    int maxSpend = ((target - cur) / 2) * add_spend;
    // 当前 有一定的 递归的范围
    // 而且 避免 f(2) ->f(4) ->f(2) 的情况出现的时候
    // 当前 递归的深度也有限制
    auto base_case = [=](int coin, int end, int spend, auto &&self) -> int
    {
        if (coin == end)
            return spend;
        if (coin < 0 || coin > maxCoin || spend > maxSpend)
            return INT_MAX;
        auto subtract = self(coin - 2, end, spend + subtract_spend, self);
        auto add = self(coin + 2, end, spend + add_spend, self);
        auto multiply = self(coin * 2, end, spend + multiply_spend, self);
        return std::min({subtract, add, multiply});
    };

    auto dfImpl = [maxCoin, maxSpend](int coin, int end)
    {
        fbvector<fbvector<int>> data(maxCoin, fbvector<int>(maxSpend));
        // result= f(coin,0)
        //  = std::min({f(coin-2,subtract_spend),
        //  f(coin+2,add_spend),f(coin*2,multiply_sepnd)} );
    };
}

void ArrayAlgo::xor_max_range()
{
    // xor  最多的区间划分为

    constexpr std::array data = {1, 2, 0, 3, 2, 2, 1};
    // 当前的划分区间为
    int result = 0;
    for (int cur : data)
    {
        if (cur == 0)
            result++;
    }
}

void ArrayAlgo::change_array_data()
{
    constexpr static std::array first = {1, 3, 5, 6};
    constexpr static std::array second = {2, 6, 7};
    constexpr static int data = 10;
    std::function<int(int, int)> get_first = [&](int index, int rest) -> int
    {
        if (rest == 0 && index != 0)
        {
            return 1;
        }
        if (index == first.size())
        {
            return 0;
        }
        int count = 0;
        for (int i = rest / first[index]; i >= 0; i--)
        {
            count += get_first(index + 1, rest - first[index] * i);
        }
        return count;
    };

    constexpr static auto get_first_reverse = [&](int index, int rest,
                                                  auto &&self) -> int
    {
        if (index == -1)
        {
            return rest == 0 ? 1 : 0;
        }
        int result = 0;
        for (int k = 0; first[index] * k <= rest; k++)
        {
            result += self(index - 1, rest - first[index] * k, self);
        }

        return result;
    };

    constexpr auto get_first_forward = [&]() -> int
    {
        //// f(index,rest) = f(index+1,rest-array[index]*1)+
        /// f(index+1,rest-array[index]*2) + ......
        // std::vector<std::vector<int>>
        // container(first.size()+1,std::vector<int>(data+1));
        //// f(1,0)  f(2,0) ....f(n-1,0) =1            f(n,0)=0
        // std::for_each(container.begin() + 1, container.end(),
        // [](std::vector<int>& ref) {ref[0] = 1; }); for (int index =
        // container.size(); index < ) {

        //}
        constexpr size_t row_index = first.size() + 1;
        constexpr auto column_rest = data + 1;
        // 当前数据的多数行为
        auto dp = std::make_unique<int[]>(row_index * column_rest);
        // 钱为0的情况下 各个节点的为1   在节点0处 钱为第一个元素的倍数全为1
        std::memset(dp.get(), 0, row_index * column_rest);
        for (size_t i = 0; i < row_index; i++)
        {
            dp[i * column_rest] = 1;
        }
        for (size_t j = 0; j * first[0] < column_rest; j++)
        {
            dp[j * first[0]] = 1;
        }
        const auto enum_all_element = [&]()
        {
            // 当前节点的 转换上将 由当前行 的取值 将由上一行 数字存储过程
            // 目标dp[first.size()][data]
            for (size_t row = 1; row < row_index; row++)
            {
                for (size_t column = 1; column < column_rest; column++)
                {
                    size_t cur = row * column_rest + column; // dp[row][column]
                    for (size_t take = 0; take * first[row] <= data; take++)
                    {
                        // 假设当前的元素拿了 take 数 则查询上一层中的
                        // dp[row-1][data-take*first[row]]
                        size_t take_cur =
                            (row - 1) * column_rest + data - take * first[row];
                        dp[cur] += dp[take_cur];
                    }
                }
            }
            return dp[row_index * column_rest - 1]; // dp[first.size()][data]
        };
        // 斜优化
        const auto inclined_to_optimize = [&]()
        {
            for (size_t row = 1; row < row_index; row++)
            {
                for (size_t column = 1; column < column_rest; column++)
                {
                    size_t cur = row * column_rest + column;

                    // dp[row][column]
                    // 假设当前的元素拿了 take 数 则查询同层中的
                    // dp[row][data-（take-1)*first[row]]
                    // dp[row-1][data-take*first[row]]  和当前的上一个元素
                    // dp[row][column]=dp[cur-1][column-data[row]]

                    // 同层元素存在着
                    // dp[row][column] += dp[row][column - first[row]];
                    if (column - first[row] >= 0)
                    {
                        dp[cur] = dp[cur - first[row]];
                    }
                    size_t pre_layer = (row - 1) * column_rest + column;
                    dp[cur] += dp[pre_layer];
                }
            }
            return dp[row_index * column_rest - 1]; // dp[first.size()][data]
        };

        // 压缩存储 只需要两个向量空间
        const auto compression_storage = [&]()
        {
            std::array<int, 11> dp[2]{};
            // 只需要两个数组即可
            // i 为first 的倍数
            for (size_t i = 0; i * first[0] < column_rest; i++)
            {
                dp[0][i] = 1;
            }
            dp[1][0] = 1; // 当前的钱为0 则方法数为1
            size_t cur_row = 0;
            for (int row = 1; row < row_index; row++)
            {
                cur_row = (cur_row + 1) % 2;
                for (size_t column = 0; column < column_rest; column++)
                {
                    size_t pre_column = column - first[row];
                    if (pre_column >= 0)
                    {
                        dp[cur_row][column] = dp[cur_row][pre_column];
                    }
                    size_t pre_row = (cur_row + 1) % 2;
                    dp[cur_row][column] += dp[pre_row][column];
                }
            }
            return dp[cur_row].back();
        };
        return -1;
    };

    std::function<int(int, int)> get_second = [&get_second](int index, int rest) -> int
    {
        if (rest == 0 && index != 0)
            return 1;
        if (index == first.size())
            return 0;
        int count = 0;
        count += get_second(index + 1, rest - second[index]);
        count += get_second(index + 1, rest);
        return count;
    };
    int count = 0;
    for (int i = 0; i <= data; i++)
    {
        int a = get_first(0, data - i) * get_second(0, i);
        count += a;
        dbg(a, data - i, i);
    }
}

void ArrayAlgo::find_top_k()
{
    // 当前的 计算数据为
    // 从两个有序地列表中找到 第k小的元素
    std::array<int, 5> first = {1, 4, 7, 8, 9};
    std::array<int, 5> second = {2, 3, 5, 6, 10};

    constexpr int k = 6;
    const auto counter = [&]()
    {
        // 双指针
        size_t first_index = 0;
        size_t second_index = 0;
        int count = 0;
        int target = first[0];
        while (count != k)
        {
            if (first[first_index] < second[second_index])
            {
                target = first[first_index];
                first_index++;
            }
            else
            {
                target = second[second_index];
                second_index++;
            }
            count++;
        }
        return target;
    };

    // 多次使用 二分搜索
    const auto binary = [&]()
    {
        // 获得小于等于当前的位置
        const auto get_leq_pos = [](const std::array<int, 5> &data, int left,
                                    int right, int target)
        {
            assert(left <= right && left >= 0);
            while (left <= right)
            {
                int mid = (left + right) >> 2;
                if (data[mid] < target)
                {
                    right = mid - 1;
                }
                else if (data[mid] > target)
                {
                    left = mid + 1;
                }
                else
                {
                    return mid;
                }
            }
            return left;
        };

        int start = first.size() / 2;
        int first_left = 0;
        int first_right = 0;
        int second_left = 0;
        int second_right = second.size() - 1;
        int cur_k = start +
                    get_leq_pos(second, second_left, second_right, first[start]) +
                    1;
        bool search_on_second = true;
        while (cur_k != k)
        {
            if (cur_k < k)
            {
                if (search_on_second)
                {
                    first_left = ((first_left + first_right) >> 2) + 1;
                    // cur_k =
                }
                else
                {
                }
            }
            else
            {
            }
            search_on_second = !search_on_second;
        }
    };
}

void ArrayAlgo::JosephProblem()
{
    // 约瑟夫问题
    constexpr int total = 20;
    constexpr int m = 3;
    fbvector<int> data;
    data.reserve(total);
    for (size_t i = 0; i < total; i++)
    {
        data.emplace_back(i);
    }
    size_t start = 0;
    while (data.size() != 1)
    {
        start = (start + m - 1) % data.size();
        dbg(data[start]);
        data.erase(data.begin() + start);
        start = (start + 1) % data.size();
    }

    // 约瑟夫问题 当前子问题很小的时候 可以很简单求解
    //  ysf(1,3,10)=ysf(3,3,10)

    const auto ysf = [](int start, int interval, int total) {};
}

void ArrayAlgo::longestTotalArray()
{
    // 子数组中总和达到目标  最长的子数组为
    std::array arr = {1, 2, 5, 3, 2, 1};
    constexpr int k = 5;
    // 滑动窗口 将当前的最大间隔的双指针记录下来
    int left = 0;
    int right = left + 1;
    int sum = arr[left] + arr[right];
    int result = INT_MAX;
    int size = arr.size();
    while (right != size)
    { // 当前数据
        if (sum > k)
        {
            sum -= arr[left];
            left += 1;
        }
        else if (sum < k)
        {
            right += 1;
            if (right == size)
                break;
            sum += arr[right];
        }
        else
        {
            int interval = right - left + 1;
            std::string data = fmt::format(
                "{}", fmt::join(arr.begin() + left, arr.begin() + right + 1, ","));
            dbg(data, left, right);
            if (interval < result)
            {
                result = interval;
            }
            if (right == size - 1)
            {
                return;
            }
            else
            {
                right += 1;
                sum += arr[right];
            }
        }
    }
}

void ArrayAlgo::change_position()
{
    // 使得排列的数据要求4的倍数最少的情况下
    //  改变当前的数组的排列 使相邻数据相乘为4的倍数
    {
        fbvector<int> data = GreedyAlgo::geRandomArray(10, 0, 30);

        std::sort(data.begin(), data.end());
        const auto &check = [&]
        {
            assert(!data.empty());
            for (size_t i = 0; i < data.size() - 1; ++i)
            {
                int cur = data.at(i) * data.at(i + 1);
                if (cur == 0 || (cur & 1) == 0)
                    continue;
                // 100  10000 1000000    100100100100=0x555555
                if ((cur & 0x55555555) != cur)
                {
                    return false;
                }
            }
            return true;
        };
        do
        {
            if (check())
            {
                fmt::print("data:{}", fmt::join(data, ","));
            }
        } while (std::next_permutation(data.begin(), data.end()));
    }
    // 使得排列的数据要求4的倍数最少的情况下
    //  将当前问题作为分类 奇数 一类   2的倍数一类   4的倍数一类
    {
        //  奇数(4的倍数)奇数(4的倍数)奇数  当(2的倍数)==0
        //  (2的倍数)(4的倍数)奇数       当(2的倍数)!=0
        //  (2的倍数)(2的倍数)(4的倍数)奇数(4的倍数)奇数  当(4的倍数)>=1

        // 可知  满足(4的倍数)>=奇数 条件就行了
    }
}

void ArrayAlgo::standard_str()
{
    //
    std::function<int(const std::string &, const int)> fn = [&](const std::string &cur, const int target) -> int
    {
        size_t size = cur.size();
        if (cur == "0" ||
            (size >= 2 && cur.at(size - 1) == '0' && cur.at(size - 2) == '0'))
            return 0;
        if (size == target)
            return 1;
        int zero = fn(cur + '0', target);
        int one = fn(cur + '1', target);
        return zero + one;
    };
    fmt::print("{} fn(, 1) == 1 {}\n", fn("", 1), fn("", 1) == 1);
    fmt::print("{} fn(, 3, fn) == 3 {}\n", fn("", 3), fn("", 3) == 3);
    // 矩阵的快速联乘
    // f(n)= x*f(n-1) + y*f(n-2)
    // [f(n) ,f(n-1)] = [f(n-1) ,f(n-2)] *[a ,b]
    //                                    [c ,d]
    // 矩阵的快速联乘
    // f(n)= x*f(n-1) + y*f(n-2) +z *(fn-3) +w*f(n-4)
    // [f(n) ,f(n-1),f(n-2),f(n-3),f(n-4)] =[f(n-1),f(n-2),f(n-3),f(n-4),f(n-5)]
    // *[4x4]

    // 快速矩阵乘法 和 相关的 数列递推问题
    int power = 35;
    size_t base = 10;
    size_t result = 1;
    // 10^35   10 0011 10^1 *10^2 *10^32
    while (power != 0)
    {
        base *= base;
        if ((power & 1) == 1)
        {
            result *= base;
        }
        power >>= 1;
    }

    // 快速矩阵相乘

    struct MyMatrix
    {
        int a, b, c, d;

        MyMatrix(int a_value, int b_value, int c_value, int d_value)
            : a(a_value), b(b_value), c(c_value), d(d_value) {}

        void Multiply(const MyMatrix &second)
        {
            this->a = a * second.a + b * second.c;
            this->b = a * second.b + b * second.d;
            this->c = c * second.a + d * second.c;
            this->d = c * second.b + d * second.d;
        }
    };

    int power_matrix = 35;
    MyMatrix base_matrix = MyMatrix(1, 1, 1, 0);
    MyMatrix result_matrix = MyMatrix(1, 0, 1, 0);
    // 10^35   10 0011 10^1 *10^2 *10^32
    while (power_matrix != 0)
    {
        base_matrix.Multiply(base_matrix);
        if ((power_matrix & 1) == 1)
        {
            result_matrix.Multiply(base_matrix);
        }
        power_matrix >>= 1;
    }
}

void ArrayAlgo::findKthBit()
{
    auto data = []
    {
        fbstring data = "0";
        folly::fbvector<folly::fbstring> result;
        constexpr int count = 20;
        result.reserve(count);
        for (int i = 0; i < count; ++i)
        {
            fbstring tmp;
            tmp.reserve(data.size());
            std::transform(data.rbegin(), data.rend(), std::back_inserter(tmp),
                           [](char ch)
                           { return ch == '1' ? '0' : '1'; });

            data += '1' + tmp;
            result.emplace_back(folly::fbstring{data.data(), data.size()});
        }
        return result;
    };

    constexpr int len = (2 << 5) - 1;
    constexpr int k = 10;
    std::function<char(int, int)> impl = [&impl](int n, int k) -> char
    {
        if (n == 1)
        {
            return '0';
        }
        int midPos = (1 << (n - 1)) - 1;
        dbg(midPos, k);
        // 再前一半的位数是没有进行翻转的
        if (k < midPos)
        {
            dbg(n - 1, k);
            return impl(n - 1, k);
        }
        else if (k > midPos)
        {
            dbg(n - 1, midPos * 2 - k);
            // 映射到前半部分
            return impl(n - 1, midPos * 2 - k) == '0' ? '1' : '0';
        }
        else
        {
            return '1';
        }
    };
    dbg(impl(4, 11 - 1)); //"0111001"
}

void ArrayAlgo::salesRange()
{
    auto impl = []
    {
        folly::fbvector<int> data{10, 2, 1, 4, 3, 9, 6, 9, 9};
        int result = 0;
        std::function<void(int, int, int)> dfs = [&](int left, int right, int cur) -> void
        {
            if (left > right)
                return;

            result = std::max(result, cur);
            dbg(folly::join(",", data.begin() + left, data.begin() + right), cur);
            if (right == data.size() - 1)
            {
                cur += data[right] > 8 ? 1 : -1;
                if (left == right)
                {
                    result = std::max(result, data.back() > 8 ? 1 : 0);
                    return;
                }
                else
                {
                    dfs(left + 1, right, cur - (data[left] > 8 ? 1 : -1));
                }
            }
            else
            {
                cur += data[right] > 8 ? 1 : -1;
                result = std::max(result, cur);
                dfs(left + 1, right, cur - (data[left] > 8 ? 1 : -1));
                dfs(left, right + 1, cur + (data[right] > 8 ? 1 : -1));
            }
        };
        dfs(0, 0, 0);
        dbg(result);
    };
    impl();
}

void ArrayAlgo::binarySearch()
{
    // 搜索左侧边界 小左进一 右等中

    const auto leftBound = [](std::vector<int> &array, int target)
    {
        int left = 0;
        int right = array.size();

        while (left < right)
        {
            int mid = left + ((right - left) >> 1);
            if (array[mid] < target)
            {
                left = mid + 1;
            }
            else
            {
                right = mid; // 相等则继续缩短右边界
            }
        }
        return left;
    };

    // 搜索右侧边届  大右等中 左进一
    const auto rightBound = [](std::vector<int> &array, int target)
    {
        int left = 0;
        int right = array.size();

        while (left < right)
        {
            int mid = left + ((right - left) >> 1);
            if (array[mid] > target)
            {
                right = mid;
            }
            else
            {
                left = mid + 1;
            }
        }
        return left;
    };
}

void ArrayAlgo::advantageCount()
{
    fbvector<int> first;
    fbvector<int> second;
    using constPair = const std::pair<int, int>;
    auto data = [](constPair &a, constPair &b)
    {
        return a.first > b.first;
    };

    std::priority_queue<std::pair<int, int>, fbvector<std::pair<int, int>>,
                        decltype(data)>
        myQueue{data};
    int secondSize = second.size();
    for (int i = 0; i < secondSize; ++i)
    {
        myQueue.emplace(second[i], i);
    }

    std::sort(first.begin(), first.end());
    int left = 0;
    int right = first.size() - 1;
    fbvector<int> res(secondSize);

    while (!myQueue.empty())
    {
        auto cur = myQueue.top();
        myQueue.pop();
        if (first[right] > cur.first)
        {
            // 如果打得过
            res[cur.second] = first[right];
            right--;
        }
        else
        {
            res[cur.second] = first[left];
            left++;
        }
    }
}

void ArrayAlgo::minEatingSpeed()
{
    const auto impl = []()
    {
        fbvector<int> piles{3, 6, 7, 11};
        int h = 8;
        int sum = std::accumulate(piles.begin(), piles.end(), 0);

        int left = 1;
        int right = sum;

        const auto check = [&piles](int num)
        {
            int cnt = 0;

            int size = piles.size();
            for (int i = 0; i < size; ++i)
            {
                cnt += piles[i] / num + (piles[i] % num != 0 ? 1 : 0);
            }
            return cnt;
        };

        while (left < right)
        {
            int mid = left + ((right - left) >> 1);
            int curTime = check(mid);
            if (curTime <= h)
            { // 花费的时间小了可以减少容量
                right = mid;
            }
            else
            {
                left = mid + 1;
            }
        }
        return left;
    };
}

void ArrayAlgo::shipWithinDays()
{
    fbvector<int> weights{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int days = 5;
    [[maybe_unused]] const auto splitDaty = [&weights, days]()
    {
        int min = INT_MIN;
        int max = 0; // 最小值为 max-ele  最大值为  sum
        for (int a : weights)
        {
            if (min > a)
            {
                min = a;
            }
            max += a;
        }

        const auto check = [&weights, days](int capcity)
        {
            int cnt = 1;
            int sum = weights.front();
            int size = weights.size();
            for (int i = 1; i < size; ++i)
            {
                if (sum + weights[i] > capcity)
                {
                    ++cnt;
                    sum = weights[i];
                }
                else
                {
                    sum += weights[i];
                }
            }
            return cnt <= days;
        };

        int left = min;
        int right = max;
        while (left < right)
        {
            int curCapcity = left + ((right - left) >> 1); // 当前能承载的重量
            if (check(curCapcity))
            { // 花费更小的时间 则 当前的 容量过重
                right = curCapcity;
            }
            else
            {
                left = curCapcity + 1; // 当前 容量轻了
            }
        }
        return left;
    };
}

void ArrayAlgo::minSubArrayLen(int target, std::vector<int> &nums)
{
    int left = 0;
    int right = 0;
    int resLen = INT_MAX;
    int sum = 0;
    while (right < nums.size())
    {
        int curRight = nums[right++];
        if (sum < target)
            sum += curRight;
        // 缩小当前左侧节点
        while (sum >= target)
        {
            if (sum >= target && right - left < resLen)
            {
                resLen = right - left;
            }
            int curLeft = nums[left++];
            sum -= curLeft;
        }
    }
    dbg(resLen == INT_MAX ? 0 : resLen);
}

bool ArrayAlgo::containsNearbyDuplicate()
{
    std::vector<int> nums = {1, 2, 3, 1};
    int k = 3;
    if (k == 0)
        return false;
    int left = 0;
    int right = 0;
    std::unordered_set<int> mSet;
    while (right < nums.size())
    {
        int curRight = nums[right++];
        // 判断当前元素添加是否合理
        // 添加后元素个数
        int eleCount = right - left;
        dbg(curRight);
        dbg(eleCount, folly::join(",", nums.begin() + left, nums.begin() + right),
            left, right);
        if (eleCount <= k + 1 && !mSet.insert(curRight).second)
        {
            return true;
        }

        if (eleCount > k + 1)
        {
            mSet.erase(nums[left++]);
            if (!mSet.insert(curRight).second)
                return true;
        }
    }
    return false;
}

void ArrayAlgo::takeCharacters()
{
    std::string s = "aabaaaacaabc";
    int k = 2;
    std::array<int, 3> array{0, 0, 0};
    int size = s.size();
    int n = size;
    // 没前缀的情况  只取后缀
    int ans = -1;
    while (array[0] < k && array[1] < k && array[2] < k)
    {
        if (n == 0)
            return; // return  -1
        --n;
        ++array[static_cast<int>(s[n] - 'a')];
        dbg(n, array);
    }
    ans = size - n;

    for (int i = 0; i < size; ++i)
    {
        int chIndex = static_cast<int>(s[i] - 'a');
        ++array[chIndex];
        dbg(n, array);
        while (n < size && array[chIndex] > k)
        {
            array[chIndex]--;
            n++;
            dbg(n, array);
        }
        ans = std::min(ans, i + 1 + size - n);
        dbg(ans);
    }
    // return ans
}

void ArrayAlgo::nextGreaterElement()
{
    std::vector<int> nums = {2, 1, 2, 4, 3};
    int size = nums.size();
    std::vector<int> res(size);
    // 维护单调队列
    std::deque<int> mStack;
    const auto push = [&](int value)
    {
        while (not mStack.empty())
        {
            if (mStack.front() < value)
            {
                mStack.pop_front();
            }
            else
            {
                break;
            }
        }
        mStack.push_back(value);
    };

    const auto pop = [&](int index)
    {
        if (nums[index] == mStack.front())
        {
            mStack.pop_front();
        }
    };

    int i = 0;
    for_each(nums.rbegin(), nums.rend() - 1, [&](int value) {

    });
}

void ArrayAlgo::pickIndex()
{
    std::vector<int> data{1, 3};
    std::vector<int> preSum;
    preSum.reserve(data.size());
    int sum = 0;
    std::transform(data.begin(), data.end(), std::back_inserter(preSum),
                   [&sum](int i)
                   {
                       sum += i;
                       return sum;
                   });
    dbg(preSum);
    std::random_device device;

    std::uniform_int_distribution dis(1, sum); // 这边是 [1,sum]
    int randomNum = dis(device);
    int left = 0;
    int right = preSum.size();
    // 找到第一个大于等于的数
    while (left < right)
    {
        int mid = left + ((right - left) >> 1);
        if (preSum[mid] < randomNum)
        {
            left = mid + 1;
        }
        else
        {
            right = mid;
        }
    }
    dbg(left);
}

void ArrayAlgo::countSmaller()
{

    using std::vector;
    vector<int> nums{5, 2, 6, 1};

    int size = static_cast<int>(nums.size());

    struct Val
    {
        int data = 0;
        int index = 0;

        Val() = default;

        explicit Val(int a, int b) : data{a}, index{b} {}
    };

    vector<Val> valWithIndex;
    valWithIndex.reserve(size);
    for (int i = 0; i < size; ++i)
    {
        valWithIndex.emplace_back(nums[i], i);
    }
    vector<int> res(size);

    dbg(nums);
    const auto merge = [&res, &valWithIndex](
                           int
                               left,
                           int
                               right)
    {
        // 转换的时候 将当前
        // 将当前存在于将小的坐标转换为大的坐标的情况 则添加当前的计数
        int mid = (left + right) / 2;
        int secondStart = mid + 1;

        vector<Val> help(right - left + 1);

        int index = 0;
        while (left <= mid && secondStart <= right)
        {
            if (valWithIndex[left].data < valWithIndex[secondStart].data)
            {
                res[valWithIndex[left].index] += right - mid - 1;
                help[index++] = valWithIndex[left++];
            }
            else
            {
                help[index++] = valWithIndex[secondStart++];
            }
        }

        if (left > mid)
        { // 右侧有元素
            help[index++] = valWithIndex[secondStart++];
        }
        else
        { // 左侧有元素
            res[valWithIndex[left].index] += right - mid - 1;
            help[index++] = valWithIndex[left++];
        }
    };

    std::function<void(int, int)> mergeSort = [&](int left, int right)
    {
        if (left < right)
        {
            int mid = (left + right) / 2;
            mergeSort(left, mid);
            mergeSort(mid + 1, right);
            merge(left, right);
        }
    };

    mergeSort(0, size - 1);

    dbg(res);
    // return res;
}

void ArrayAlgo::reversePair()
{
    // 求逆序对数
}
