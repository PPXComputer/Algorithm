#include "ArrayAlgo.h"
#include "folly/Random.h"

#include<vector>
#include <dbg.h>
#include <memory>
#include <optional>

void ArrayAlgo::huffman_tree() {
    const auto &getFibonacci = [](int end) {
        std::vector<int> result;
        result.reserve(end);
        int start = 0;
        while (start != end) {
            if (start == 0 || start == 1)
                result.push_back(1);
            else {
                size_t len = result.size();
                result.push_back(result[len - 1] + result[len - 2]);
            }
            start += 1;
        }
        return result;
    };

    std::vector data = getFibonacci(10);
    for (int i: data)
        cout << i << " ";
    cout << "\n";
    std::make_heap(data.begin(), data.end());
    while (data.size() != 1) {
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

void ArrayAlgo::long_increase_sub_array() {
    std::array data = {3, 1, 2, 6, 3, 4, 0};

    // 1 2 3 4
    std::array<int, 7> dp{1};
    constexpr
    size_t len = data.size();
    for (int i = 1; i < len; i++) {
        dp.at(i) = 1;
        for (int j = 0; j < i; j++) {
            if (data.at(j) < data.at(i) and dp.at(j) + 1 > dp.at(i)) {
                dp.at(i) = dp.at(j) + 1;
            }
        }
    }
    std::cout << fmt::format("dp {}", folly::join(',', dp));
}

void ArrayAlgo::data_array() {
    std::array data = {1, 3, 4, 3};
    std::unordered_map<int, int> map;
    for (const int &ref: data) {
        if (map.find(ref) != map.cend()) {
            std::cout << "result: " << ref;
            break;
        }
        map.insert({ref, 1});
    }
    constexpr auto len = data.size();
    for (int i = 1; i < len; i++) {
        std::swap(data[i], i);
        //			if () {
        //
        //			}
    }
}

void ArrayAlgo::not_exists_num() {
    //����������δ���ֵ�����
    std::array<int, 7> data = {3, 2, 1, 6, 2, 7, 5}; // 1-n
    //                          0 1 2 3 4 5 6
    size_t cur = 0;
    constexpr auto size = data.size();
    while (cur < size) {
        int cur_value = data[cur];
        size_t promise_pos = static_cast<size_t>(cur_value) - 1;
        if (cur + 1 == cur_value) {
            cur += 1;
        } else {
            int swap_value = data[promise_pos];
            if (swap_value == cur_value) {
                // ��ǰ��λ�õ�ֵΪ�ظ���
                fmt::print("result data :{}", promise_pos + 1);
                break;
            } else {
                std::swap(data[cur], data[promise_pos]);
            }
        }
        fmt::print("cur array {} pos:{}\n", fmt::join(data, ","), cur);
    }
}

void ArrayAlgo::coin_change() {
    int cur = 6;
    int target = 10;
    constexpr int add_spend = 120;
    constexpr int multiply_spend = 500;
    constexpr int subtract_spend = 140;

    auto fault = [=](int coin, int end, auto &&self) -> int {
        if (coin == end) {
            return 0;
        }
        // �ݹ��е��ظ���Χ�Ὣ���³��� �������޵ݹ�
        auto subtract = self(coin - 2, end, self) + subtract_spend;
        auto add = self(coin + 2, end, self) + add_spend;
        auto multiply = self(coin * 2, end, self) + multiply_spend;
        return std::min({subtract, add, multiply});
    };

    int maxCoin = target * 2;
    int maxSpend = ((target - cur) / 2) * add_spend;
    // ��ǰ ��һ���� �ݹ�ķ�Χ
    // ���� ���� f(2) ->f(4) ->f(2) ��������ֵ�ʱ��
    // ��ǰ �ݹ�����Ҳ������
    auto base_case = [=](int coin, int end, int spend, auto &&self) -> int {
        if (coin == end)
            return spend;
        if (coin < 0 or coin > maxCoin or spend > maxSpend)
            return INT_MAX;
        auto subtract = self(coin - 2, end, spend + subtract_spend, self);
        auto add = self(coin + 2, end, spend + add_spend, self);
        auto multiply = self(coin * 2, end, spend + multiply_spend, self);
        return std::min({subtract, add, multiply});
    };

    auto dfImpl = [maxCoin, maxSpend](int coin, int end) {
        fbvector <fbvector<int>> data(maxCoin, fbvector<int>(maxSpend));
        // result= f(coin,0)
        //  = std::min({f(coin-2,subtract_spend),
        //  f(coin+2,add_spend),f(coin*2,multiply_sepnd)} );
    };
}

void ArrayAlgo::xor_max_range() {
    // xor  �������仮��Ϊ

    constexpr
    std::array data = {1, 2, 0, 3, 2, 2, 1};
    // ��ǰ�Ļ�������Ϊ
    int result = 0;
    for (int cur: data) {
        if (cur == 0)
            result++;
    }
}

void ArrayAlgo::change_array_data() {
    constexpr
    static std::array first = {1, 3, 5, 6};
    constexpr
    static std::array second = {2, 6, 7};
    constexpr static int data = 10;
    constexpr static auto get_first = [&](int index, int rest,
                                          auto &&get_first) -> int {
        if (rest == 0 and index != 0)
            return 1;
        if (index == first.size())
            return 0;
        int count = 0;
        for (int i = rest / first[index]; i >= 0; i--) {
            count += get_first(index + 1, rest - first[index] * i, get_first);
        }
        return count;
    };

    constexpr static auto get_first_reverse = [&](int index, int rest,
                                                  auto &&self) -> int {
        if (index == -1) {
            return rest == 0 ? 1 : 0;
        }
        int result = 0;
        for (int k = 0; first[index] * k <= rest; k++) {
            result += self(index - 1, rest - first[index] * k, self);
        }

        return result;
    };

    constexpr auto get_first_forward = [&]() -> int {
        //// f(index,rest) = f(index+1,rest-array[index]*1)+
        ///f(index+1,rest-array[index]*2) + ......
        // std::vector<std::vector<int>>
        // container(first.size()+1,std::vector<int>(data+1));
        //// f(1,0)  f(2,0) ....f(n-1,0) =1            f(n,0)=0
        // std::for_each(container.begin() + 1, container.end(),
        // [](std::vector<int>& ref) {ref[0] = 1; }); for (int index =
        // container.size(); index < ) {

        //}
        constexpr
        size_t row_index = first.size() + 1;
        constexpr auto column_rest = data + 1;
        // ��ǰ���ݵĶ�����Ϊ
        auto dp = std::make_unique<int[]>(row_index * column_rest);
        // ǮΪ0������� �����ڵ��Ϊ1   �ڽڵ�0�� ǮΪ��һ��Ԫ�صı���ȫΪ1
        std::memset(dp.get(), 0, row_index * column_rest);
        for (size_t i = 0; i < row_index; i++) {
            dp[i * column_rest] = 1;
        }
        for (size_t j = 0; j * first[0] < column_rest; j++) {
            dp[j * first[0]] = 1;
        }
        const auto enum_all_element = [&]() {
            // ��ǰ�ڵ�� ת���Ͻ� �ɵ�ǰ�� ��ȡֵ ������һ�� ���ִ洢����
            // Ŀ��dp[first.size()][data]
            for (size_t row = 1; row < row_index; row++) {
                for (size_t column = 1; column < column_rest; column++) {

                    size_t cur = row * column_rest + column; // dp[row][column]
                    for (size_t take = 0; take * first[row] <= data; take++) {
                        // ���赱ǰ��Ԫ������ take �� ���ѯ��һ���е�
                        // dp[row-1][data-take*first[row]]
                        size_t take_cur =
                                (row - 1) * column_rest + data - take * first[row];
                        dp[cur] += dp[take_cur];
                    }
                }
            }
            return dp[row_index * column_rest - 1]; // dp[first.size()][data]
        };
        // б�Ż�
        const auto inclined_to_optimize = [&]() {
            for (size_t row = 1; row < row_index; row++) {
                for (size_t column = 1; column < column_rest; column++) {

                    size_t cur = row * column_rest + column;

                    // dp[row][column]
                    // ���赱ǰ��Ԫ������ take �� ���ѯͬ���е�
                    // dp[row][data-��take-1)*first[row]]
                    // dp[row-1][data-take*first[row]]  �͵�ǰ����һ��Ԫ��
                    // dp[row][column]=dp[cur-1][column-data[row]]

                    // ͬ��Ԫ�ش�����
                    // dp[row][column] += dp[row][column - first[row]];
                    if (column - first[row] >= 0) {

                        dp[cur] = dp[cur - first[row]];
                    }
                    size_t pre_layer = (row - 1) * column_rest + column;
                    dp[cur] += dp[pre_layer];
                }
            }
            return dp[row_index * column_rest - 1]; // dp[first.size()][data]
        };

        // ѹ���洢 ֻ��Ҫ���������ռ�
        const auto compression_storage = [&]() {
            std::array<int, 11> dp[2]{};
            // ֻ��Ҫ�������鼴��
            // i Ϊfirst �ı���
            for (size_t i = 0; i * first[0] < column_rest; i++) {
                dp[0][i] = 1;
            }
            dp[1][0] = 1; //��ǰ��ǮΪ0 �򷽷���Ϊ1
            size_t cur_row = 0;
            for (int row = 1; row < row_index; row++) {
                cur_row = (cur_row + 1) % 2;
                for (size_t column = 0; column < column_rest; column++) {
                    size_t pre_column = column - first[row];
                    if (pre_column >= 0) {
                        dp[cur_row][column] = dp[cur_row][pre_column];
                    }
                    size_t pre_row = (cur_row + 1) % 2;
                    dp[cur_row][column] += dp[pre_row][column];
                }
            }
            return dp[cur_row].back();
        };
    };

    constexpr auto get_second = [&](int index, int rest,
                                    auto &&get_second) -> int {
        if (rest == 0 and index != 0)
            return 1;
        if (index == first.size())
            return 0;
        int count = 0;
        count += get_second(index + 1, rest - second[index], get_second);
        count += get_second(index + 1, rest, get_second);
        return count;
    };
    int count = 0;
    for (int i = 0; i <= data; i++) {
        int a = get_first(0, data - i, get_first) * get_second(0, i, get_second);
        count += a;
        dbg(a, data - i, i);
    }
}

void ArrayAlgo::find_top_k() {
    // ��ǰ�� ��������Ϊ
    // ������������б����ҵ� ��kС��Ԫ��
    std::array<int, 5> first = {1, 4, 7, 8, 9};
    std::array<int, 5> second = {2, 3, 5, 6, 10};

    constexpr int k = 6;
    const auto counter = [&]() {
        // ˫ָ��
        size_t first_index = 0;
        size_t second_index = 0;
        int count = 0;
        int target = first[0];
        while (count != k) {
            if (first[first_index] < second[second_index]) {
                target = first[first_index];
                first_index++;
            } else {
                target = second[second_index];
                second_index++;
            }
            count++;
        }
        return target;
    };

    // ���ʹ�� ��������
    const auto binary = [&]() {
        // ���С�ڵ��ڵ�ǰ��λ��
        const auto get_leq_pos = [](const std::array<int, 5> &data, int left,
                                    int right, int target) {
            assert(left <= right and left >= 0);
            while (left <= right) {
                int mid = (left + right) >> 2;
                if (data[mid] < target) {
                    right = mid - 1;
                } else if (data[mid] > target) {
                    left = mid + 1;
                } else {
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
        while (cur_k != k) {
            if (cur_k < k) {

                if (search_on_second) {
                    first_left = (first_left + first_right) >> 2 + 1;
                    // cur_k =
                } else {
                }

            } else {
            }
            search_on_second = not search_on_second;
        }
    };
}

void ArrayAlgo::JosephProblem() {

    // Լɪ������
    constexpr int total = 20;
    constexpr int m = 3;
    fbvector<int> data;
    data.reserve(total);
    for (size_t i = 0; i < total; i++) {
        data.emplace_back(i);
    }
    size_t start = 0;
    while (data.size() != 1) {
        start = (start + m - 1) % data.size();
        dbg(data[start]);
        data.erase(data.begin() + start);
        start = (start + 1) % data.size();
    }

    // Լɪ������ ��ǰ�������С��ʱ�� ���Ժܼ����
    //  ysf(1,3,10)=ysf(3,3,10)

    const auto ysf = [](int start, int interval, int total) {};
}

void ArrayAlgo::longestTotalArray() {
    // ���������ܺʹﵽĿ��  ���������Ϊ
    std::array arr = {1, 2, 5, 3, 2, 1};
    constexpr int k = 5;
    // �������� ����ǰ���������˫ָ���¼����
    int left = 0;
    int right = left + 1;
    int sum = arr[left] + arr[right];
    int result = INT_MAX;
    int size = arr.size();
    while (right != size) { //��ǰ����
        if (sum > k) {
            sum -= arr[left];
            left += 1;

        } else if (sum < k) {
            right += 1;
            if (right == size)break;
            sum += arr[right];

        } else {
            int interval = right - left + 1;
            std::string data = fmt::format("{}", fmt::join(arr.begin() + left, arr.begin() + right + 1, ","));
            dbg(data, left, right);
            if (interval < result) {
                result = interval;
            }
            if (right == size - 1) return;
            else {
                right += 1;
                sum += arr[right];
            }

        }
    }
}

void ArrayAlgo::change_position() {
    //ʹ�����е�����Ҫ��4�ı������ٵ������
    // �ı䵱ǰ����������� ʹ�����������Ϊ4�ı���
    {
        fbvector<int> data = GreedyAlgo::geRandomArray(10, 0, 30);
        std::sort(data.begin(), data.end());
        const auto &check = [&] {
            assert(not data.empty());
            for (size_t i = 0; i < data.size() - 1; ++i) {
                int cur = data.at(i) * data.at(i + 1);
                if (cur == 0 or (cur & 1) == 0)
                    continue;
                // 100  10000 1000000    100100100100=0x555555
                if ((cur & 0x55555555) != cur) {
                    return false;
                }
            }
            return true;
        };
        do {
            if (check()) {
                fmt::print("data:{}", fmt::join(data, ","));
            }
        } while (std::next_permutation(data.begin(), data.end()));
    }
    //ʹ�����е�����Ҫ��4�ı������ٵ������
    // ����ǰ������Ϊ���� ���� һ��   2�ı���һ��   4�ı���һ��
    {
        //  ����(4�ı���)����(4�ı���)����  ��(2�ı���)==0
        //  (2�ı���)(4�ı���)����       ��(2�ı���)!=0
        //  (2�ı���)(2�ı���)(4�ı���)����(4�ı���)����  ��(4�ı���)>=1

        //��֪  ����(4�ı���)>=���� ����������
    }
}

void ArrayAlgo::standard_str() {
    //
    auto fn = [&](const std::string &cur, const int target, auto &&fn) -> int {
        size_t size = cur.size();
        if (cur == "0" or
            (size >= 2 and cur.at(size - 1) == '0' and cur.at(size - 2) == '0'))
            return 0;
        if (size == target)
            return 1;
        int zero = fn(cur + '0', target, fn);
        int one = fn(cur + '1', target, fn);
        return zero + one;
    };
    fmt::print("{} fn(, 1, fn) == 1 {}\n", fn("", 1, fn), fn("", 1, fn) == 1);
    fmt::print("{} fn(, 3, fn) == 3 {}\n", fn("", 3, fn), fn("", 3, fn) == 3);
    // ����Ŀ�������
    // f(n)= x*f(n-1) + y*f(n-2)
    // [f(n) ,f(n-1)] = [f(n-1) ,f(n-2)] *[a ,b]
    //                                    [c ,d]
    // ����Ŀ�������
    // f(n)= x*f(n-1) + y*f(n-2) +z *(fn-3) +w*f(n-4)
    // [f(n) ,f(n-1),f(n-2),f(n-3),f(n-4)] =[f(n-1),f(n-2),f(n-3),f(n-4),f(n-5)]
    // *[4x4]

    // ���پ���˷� �� ��ص� ���е�������
    int power = 35;
    size_t base = 10;
    size_t result = 1;
    // 10^35   10 0011 10^1 *10^2 *10^32
    while (power != 0) {
        base *= base;
        if ((power & 1) == 1) {
            result *= base;
        }
        power >>= 1;
    }

    // ���پ������

    struct MyMatrix {
        int a, b, c, d;

        MyMatrix(int a_value, int b_value, int c_value, int d_value)
                : a(a_value), b(b_value), c(c_value), d(d_value) {}

        void Multiply(const MyMatrix &second) {
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
    while (power_matrix != 0) {
        base_matrix.Multiply(base_matrix);
        if ((power_matrix & 1) == 1) {
            result_matrix.Multiply(base_matrix);
        }
        power_matrix >>= 1;
    }
}
