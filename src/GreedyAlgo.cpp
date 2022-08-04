#include "GreedyAlgo.h"
#include <iso646.h>
#include<array>

void
GreedyAlgo::concat_strings() {
    std::vector<std::string> data = {"123", "581", "135",
                                     "234"};
    std::string result;
    size_t all_size = 0;
    for (const auto &cost: data) {
        all_size += cost.size();
    }
    result.reserve(all_size);
    std::sort(data.begin(), data.end());
    for (auto &cost: data) {
        result += cost;
    }
    cout << result;
}

void
GreedyAlgo::split_metal() {
    folly::fbvector<int> data = {10, 20, 30};
    // 哈夫曼编码问题
    //get top 2
    const auto &min_heap = [](const auto &first, const auto &second) {
        return second < first;
    };
    std::make_heap(data.begin(), data.end(), min_heap);
    while (data.size() != 1) {
        get_last_two(data, min_heap);
    }
    cout << data[0];
}

inline void
GreedyAlgo::walk() {
    fbvector<fbvector<int>> matrix;
    int result = INT_MAX;
    walkImpl(0, 0, 0, matrix, result);
    cout << result;
}

inline void
GreedyAlgo::aim_plus() {
    // 目标数组中是否能累加出目标数据
    fbvector<int> datas;
    aimPlusImpl(datas, 0, 0, 10);
}

inline void
GreedyAlgo::chees() {
    //棋盘走路
    int result = 0;

    cout << cheesImpl(0, 0, std::make_pair<int, int>(6, 6), 0);
}

inline void
GreedyAlgo::get_money() {
    fbvector<int> data = {3, 5, 10, 14};
    constexpr int money = 1000;
    cout << money_way1(money, 0, data);//75631
    //动态规划打表中
}

inline void
GreedyAlgo::get_maximum_matrix() {
    array<array<int, 6>, 4> matrix = {
            array<int, 6>
                    {1, 0, 1, 1, 1, 1},
            {0, 1, 1, 0, 0, 1},
            {0, 0, 1, 0, 0, 1},
            {0, 1, 1, 1, 1, 1}
    };
    constexpr int row = 4;
    constexpr int col = 6;
    array<array<int, 6>, 4> right = {};//默认全部为0
    array<array<int, 6>, 4> down = {};//默认全部为0
    const auto &init_rigth = [&right, &matrix, row, col] {
        //  先处理最右列
        for (int i = 0; i < row; i++) {
            for (int j = col - 1; j >= 0; j--) {
                right[i][j] = matrix[i][j];
            }
        }

        for (int i = 0; i < row; i++) {
            for (int j = col - 2; j >= 0; j--) {
                int cur = matrix[i][j];
                if (cur) {
                    right[i][j] = right[i][static_cast<std::array<int, 6Ui64>::size_type>(j) + 1] + 1;
                } else {
                    right[i][j] = cur;
                }
            }
        }
    };
    const auto &init_down = [&down, &matrix, row, col] {
        //处理最下行
        for (int i = row - 1; i >= 0; i--) {
            for (int j = 0; j < col; j++) {
                down[i][j] = matrix[i][j];
            }
        }
        for (int i = row - 2; i >= 0; i--) {
            for (int j = 0; j < col; j++) {
                int cur = matrix[i][j];
                if (cur) {
                    down[i][j] = down[i + 1][j] + 1;
                } else {
                    down[i][j] = cur;
                }
            }
        }
    };
    const auto &enumerateImpl = [&matrix, row, col] {
        int result = -1;
        for (int x = 0; x < row; x++) {
            for (int y = 0; y < col; y++) {
                // 判断有多长的矩阵存在
                auto reachWidth = std::min(row - x, col - y);
                for (int width = 1; width <= reachWidth; width++) {
                    // 检查四条边
                }
            }
        }

    };
    const auto &dp = [&right, &down, row, col] {
        int result = -1;
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                const int cur = right[i][j];
                if (cur > result
                    && down[i][j + cur] >= cur
                    && down[i][j] >= cur
                    && i + cur < row
                    && right[i + cur][j] >= cur) {
                    result = cur;
                }
            }
        }
        return result;
    };
    init_down();
    init_rigth();
    cout << dp();

}

void
GreedyAlgo::buy_apples() {
    //  6 和 8的苹果
    for (int i = 0; i < 200; i++)
        cout << fmt::format("I: {} result: {} \n", i, appleImpl(i));
}

void
GreedyAlgo::winner() {
    for (int i = 0; i < 100; i++) {
        auto result = isFirstOne(i) ? 1 : 2;
        cout << fmt::format("num: {}  result: {} \n", i, result);
    }
}

void
GreedyAlgo::k_step_pair() {
    std::set<int> m_set = {3, 1, 2, 5, 7, 0, 0};
    int result = 0;
    for (auto start = m_set.begin(); start != m_set.end(); start++) {
        bool find_k = m_set.find(*start - 2) != m_set.end()
                      || m_set.find(*start + 2) != m_set.end();
        if (find_k)
            result++;
    }
    cout << result;
}

inline void
GreedyAlgo::max_deep() {
    fbstring data = "{{}{}{}}"; //最大深度
    int counter = 0;
    int max_deep = 0;
    for (const auto &cur: data) {
        if (cur == '{')
            counter++;
        else
            counter--;
        if (counter > max_deep)
            max_deep = counter;
    }
}

inline void
GreedyAlgo::long_bracket() {
    fbstring data = "{{}{}{}{{}{";
    fbstring::size_type len = data.size();
    const auto &check = [&data](int start, int end) {
        assert(start >= 0 and start < data.size());
        assert(end > start and end < data.size());
        int counter = 0;
        for (int i = start; i <= end; i++) {
            if (data[i] == '{')
                counter++;
            else
                counter--;
        }
        return counter == 0;
    };
    int result = 0;
    for (int i = 0; i < len; i++) {
        for (int j = i + 1; j < len; j++) {
            if (check(i, j)) {
                int interval = j - i + 1;
                if (interval > result)
                    result = interval;
            }
        }
    }
}

void
GreedyAlgo::matrix_multiplication() {
    using Matrix = fbvector<std::pair<int, int>>;
    //Matrix data = { std::pair<int,int>{2,3},{3,10},{10,1} };
    Matrix data = {std::pair<int, int>{2, 3}, {3, 10}, {10, 5}, {5, 6}};
    const auto &impl = [](Matrix data, int step, auto &&impl) -> int {
        if (step == data.size()) {
            int counter = 0;
            int start = 0;
            for (size_t next = 1; next < data.size(); next++) {
                counter += data[start].first * data[start].second * data[next].second;
                start++;
            }
            cout << fmt::format("rest {}\n", counter);
            return counter;
        }
        int result = INT_MAX;
        auto not_combine = impl(data, step + 1, impl);
        if (not_combine < result)
            result = not_combine;
        if (int nextStep = step + 1; nextStep < data.size()) {
            const auto &curElement = data[step];
            const auto &nextElement = data[nextStep];
            auto combine = curElement.first * curElement.second * nextElement.second;
            auto new_matrix = std::make_pair(curElement.first, nextElement.second);
            auto start = data.begin() + step;
            data.erase(start, start + 2);
            data.insert(data.begin() + step, new_matrix);
            size_t size = data.size();
            int combine_result = combine + impl(std::move(data), step, impl);
            if (combine_result < result)
                result = combine_result;
            cout << fmt::format("combine {} size:{}\n", combine_result, size);
        }
        return result;
    };
    cout << fmt::format("result {}", impl(data, 0, impl));

    const auto &dfsImpl = [](const Matrix &data, int start, int stop, auto &&dfsImpl) {
        if (start >= stop)
            return 0;
        int combine = dfsImpl(data, 0, start - 1, dfsImpl)
                      + dfsImpl(data, start + 2, stop, dfsImpl);

    };
}

void
GreedyAlgo::light_lame() {
    fbstring data = "12211211212222";
    fbstring::size_type len = data.size();
    const auto &impl = [&len](fbstring &str, int cur, int lame_counter, auto &&impl) -> int {
        cout << fmt::format("str : {} curr: {} \n", str, cur);
        if (cur == len)
            return lame_counter;

        // 贪心 将数据直接传递到相关的数据实现上
        if (str.at(cur) == '2') {
            lame_counter += 1;
            if (cur != len - 1 and str.at(cur + 1) == '2') {
                str.at(cur) = '1';
                str.at(cur + 1) = '1';
                cur += 1; // 包括了两个则 穷尽相关的数据项
                if (cur + 1 != len and str.at(cur + 1) == '2') {
                    str.at(cur + 1) = '1';
                    cur += 1;
                }
            } else {
                str.at(cur) = '1';
            }
        }
        return impl(str, cur + 1, lame_counter, impl);

    };
    cout << fmt::format("result {} {}", data, impl(data, 0, 0, impl));
}

bool
GreedyAlgo::isFirstOne(const size_t rest) {
    if (rest < 5) {
        // 1 - 2+ 3 - 4 -
        return not(rest == 0 || rest == 2);
    }
    size_t subtract = 1;//避免溢出
    while (subtract <= rest) {
        if (not isFirstOne(rest - subtract))
            return true;
        subtract *= 4;
    }
    return false;
}

//使用滑动窗口解法

inline int
GreedyAlgo::appleImpl(int money) {
    if (money % 2 == 1 || money < 6)
        return -1;
    if (money % 8 == 0)
        return money / 8;
    int max8 = money / 8;
    int rest_apples = money - 8 * max8;
    int max6 = -1;
    while (max8 >= 0 && rest_apples < 24) {
        if (rest_apples % 6 == 0) {
            max6 = rest_apples / 6;
            break;
        }
        max8--;
        rest_apples = money - 8 * max8;
    }
    return max6 != -1 ? max6 + max8 : -1;
}

inline int
GreedyAlgo::enum_rope_way2(const fbvector<int> &data, const int rope_len) {
    assert(not data.empty());
    int result = 1;//最少一个点
    size_t last_end = 1;
    fbvector<int>::size_type len = data.size();
    for (size_t start = 0; start < len; start++) {
        size_t end = last_end;
        int cur_result = 1;
        while (end < len && (data[end] - data[start] <= rope_len)) {
            if (cur_result > result) {
                result = cur_result;
            }
            ++cur_result;
            ++end;
        }
        last_end = end;//未能覆盖的end 坐标 end 不动 start 向前移动
    }
    return result;
}

inline int
GreedyAlgo::enum_rope(const fbvector<int> &data, const int rope_len) {
    int result = 1;//最少一个点
    fbvector<int>::size_type len = data.size();
    for (size_t start = 0; start < len; start++) {
        for (size_t end = start + 1; end < len; end++) {
            size_t interval = data[end] - data[start];
            if (interval <= rope_len && end - start >= result) {
                result = static_cast<int>(interval);
            }
        }
    }
    return result;
}

inline int
GreedyAlgo::money_way3(const fbvector<int> &cost, int aim) {
    if (cost.empty())
        return 0;
    size_t len = cost.size();
    FlexMatrix dp{len + 1, fbvector<int>{aim + 1}};
    dp[len][0] = 1;
    int counter = 0;
    for (int row = static_cast<int>(len - 1); row >= 0; row -= 1) {
        for (int rest = 0; rest <= aim; rest++) {
            int way = 0; // 对于打表的斜率优化
            dp[row][rest] = dp[row + 1][rest];//一定需要该节点下方节点的数据
            if (rest - cost[rest] >= 0) {
                dp[row][rest] += dp[row][rest - cost[rest]];
            }
        }
    }
    return dp[0][aim];
}

inline int
GreedyAlgo::money_way2(const fbvector<int> &cost, int aim) {
    if (cost.empty())
        return 0;
    size_t len = cost.size();
    FlexMatrix dp{len + 1, fbvector<int>{aim + 1}};

    dp[len][0] = 1;
    int counter = 0;
    for (int row = static_cast<int>( len - 1); row >= 0; row -= 1) {
        for (int col = 0; col <= aim; col++) {
            int way = 0;
            for (int get_num = 0; get_num * cost[row] <= col; get_num++) {
                way += dp[row + 1][col - get_num * cost[row]];
            }
            dp[row][col] = way;
        }
    }
    return dp[0][aim];
}

inline int
GreedyAlgo::money_way1(int cur, int index, const fbvector<int> &cost) {
    if (index == cost.size()) {
        return cur == 0 ? 1 : 0;
    }
    int counter = 0;
    auto cur_cost = cost.at(index);
    for (int get_num = 0; cur_cost * get_num <= cur; get_num += 1) {
        counter += money_way1(cur - get_num * cur_cost, index + 1, cost);
    }
    return counter;
}

void
GreedyAlgo::walkImpl(int x, int y, int cur, const fbvector<fbvector<int>> &matrix, int &result) {
    cur += matrix[x][y];
    if (x == matrix.size() - 1 && y == matrix.back().size() - 1) {
        result = std::min(cur, result);
        return;
    }
    if (x == matrix.size() - 1) {
        walkImpl(x, y + 1, cur, matrix, result);
    } else if (y == matrix.back().size() - 1) {
        walkImpl(x + 1, y, cur, matrix, result);
    } else {
        walkImpl(x, y + 1, cur, matrix, result);
        walkImpl(x + 1, y, cur, matrix, result);
    }
}

inline int
GreedyAlgo::walkImplWithNotVal(int x, int y, const fbvector<fbvector<int>> &matrix) {
    if (x == matrix.size() - 1 && y == matrix.back().size() - 1) {
        return matrix[x][y];

    }
    int right = INT_MAX;
    int down = INT_MAX;
    if (x == matrix.size() - 1) {
        right = walkImplWithNotVal(x, y + 1, matrix);
    } else if (y == matrix.back().size() - 1) {
        down = walkImplWithNotVal(x + 1, y, matrix);
    } else {
        right = walkImplWithNotVal(x, y + 1, matrix);
        down = walkImplWithNotVal(x + 1, y, matrix);
    }
    return matrix[x][y] + std::min(right, down);
}

// 备忘录递归

inline int
GreedyAlgo::walkMemo(int x, int y, const fbvector<fbvector<int>> &matrix, fbvector<fbvector<int>> &memo) {
    if (memo[x][y] != -1) {
        return memo[x][y];
    }
    if (x == matrix.size() - 1 && y == matrix.back().size() - 1) {
        //返回之前先记录
        memo[x][y] = matrix[x][y];
        return memo[x][y];

    }
    int right = INT_MAX;
    int down = INT_MAX;
    if (x == matrix.size() - 1) {
        right = walkImplWithNotVal(x, y + 1, matrix);
    } else if (y == matrix.back().size() - 1) {
        down = walkImplWithNotVal(x + 1, y, matrix);
    } else {
        right = walkImplWithNotVal(x, y + 1, matrix);
        down = walkImplWithNotVal(x + 1, y, matrix);
    }
    memo[x][y] = matrix[x][y] + std::min(right, down);
    return memo[x][y];
}

bool
GreedyAlgo::aimPlusImpl(const fbvector<int> &datas, int index, int cur_sum, int aim) {
    // 这里将只有两个变量 index ,cur_sum
//f(index,cur_sum) =f(index+1,cur_sum+data[index]) || f(index+1,cur_sum);
    if (index == datas.size()) {
        if (cur_sum == aim)
            return true;
    }
    return aimPlusImpl(datas, index + 1, cur_sum + datas[index], aim) ||
           aimPlusImpl(datas, index + 1, cur_sum, aim);
}

int
GreedyAlgo::cheesImpl(int x, int y, const std::pair<int, int> &target, int step) {
    if (x < 0 || y < 0 || x > 8 || y > 9)
        return -1; // 越界
    if (step == 7) {
        if (x == target.first && y == target.second) {
            return 1;
        }
        return 0;
    }

    return cheesImpl(x + 2, y + 1, target, step + 1) +
           cheesImpl(x + 2, y - 1, target, step + 1) +
           cheesImpl(x - 2, y + 1, target, step + 1) +
           cheesImpl(x - 2, y - 1, target, step + 1) +
           cheesImpl(x + 1, y + 2, target, step + 1) +
           cheesImpl(x - 1, y + 2, target, step + 1) +
           cheesImpl(x - 1, y - 2, target, step + 1) +
           cheesImpl(x + 1, y - 2, target, step + 1);
}

fbvector<int>
GreedyAlgo::geRandomArray(int len, int min, int max, bool unique) {
    std::random_device device;
    fbvector<int> result{len};
    std::uniform_int_distribution<int> dist(min, max);
    for (int i = 0; i < len; i++) {
        result.emplace_back(dist(device));
    }
    if (unique) {
        auto last = std::unique(result.begin(), result.end());
        result.erase(last, result.end());
    }
    return result;
}

void
GreedyAlgo::CompareResult() {
    for (int i = 0; i < 100; i++) {
        fbvector<int> random_array = GreedyAlgo::geRandomArray(20, 0, 30, true);
        std::sort(random_array.begin(), random_array.end());
        random_array.erase(std::unique(random_array.begin(), random_array.end()), random_array.end());
        int first_result = enum_rope(random_array, 10);
        int second_result = enum_rope_way2(random_array, 10);
        if (first_result != second_result) {
            cout << "error happened" << first_result << " " << second_result << '\n';
            for (auto &sd: random_array) {
                cout << sd << " ";
            }
            break;
        }
        cout << "done";
    }
}

template<typename T>
void
GreedyAlgo::get_last_two(folly::fbvector<int> &data, const T &min_heap) {
    std::pop_heap(data.begin(), data.end(), min_heap);
    int append_val = data.back();
    data.pop_back();
    std::pop_heap(data.begin(), data.end(), min_heap);
    append_val += data.back();
    data.pop_back();
    data.emplace_back(append_val);
}

void GreedyAlgo::jumpGame() {

    std::vector data = {2, 3, 1, 1, 4};

    // 找到当前的能跳跃的最大长度
    int curPos = 0;
    auto curIter = data.begin() + curPos;
    bool result = false;
    auto maxElement = std::max_element(curIter, curIter + *curIter);
    while (curIter != data.end() - 1 and *maxElement != 0) {
        //全进
        if (*maxElement >= data.end() - curIter) {
            result = true;
            return;
        }
        curIter += *maxElement;
    }
    result = maxElement == data.end() - 1;
    for (int i = data[curPos]; i > 0; --i) {

    }

}

