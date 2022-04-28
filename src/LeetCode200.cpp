#include "LeetCode200.h"
#include <array>

#include <string>
#include <queue>
#include <map>
#include <fmt/format.h>
#include <dbg.h>
#include <unordered_map>
#include <set>
#include <algorithm>
#include<numeric>
#include <folly/String.h>
#include<cmath>

using std::array;
using std::vector;
using std::queue;
using std::string;

inline void LeetCode200::medium_33() {
    //找到当前数据的最小值

    auto impl = []() {
        std::array<int, 7> nums{4, 5, 6, 7, 0, 1, 2};
        int target = 0;
        int left = 0;
        int right = nums.size() - 1;
        while (left < right) {
            int mid = ((right - left) >> 1) + left;
            dbg(left, right, mid, nums[mid]);
            if (target == nums[mid]) return mid;
            if (nums[mid] <= nums[right]) // ???????
            {
                if (target <= nums[right] and target > nums[mid]) {
                    left = mid + 1;
                } else {
                    //???????
                    right = mid - 1;
                }

            } else { //???????
                if (target >= nums[left] and target < nums[mid]) {
                    right = mid - 1;
                } else {
                    //???????
                    left = mid + 1;
                }
            }
        }
        if (nums[left] == target)return left;
        return -1;
    };
    dbg(impl());
}

inline void LeetCode200::medium_34() {
    using std::vector;
    auto answer = [](vector<int> &nums, int target) -> vector<int> {
        if (nums.empty())return {-1, -1};
        int left = 0;
        int right = static_cast<int>(nums.size() - 1);
        while (left < right) {
            //????????????target????
            int mid = left + ((right - left) >> 1);
            dbg(left, right, mid, nums[mid]);
            if (nums[mid] > target) {
                right = mid - 1;
            } else if (nums[mid] < target) {
                left = mid + 1;
            } else {
                right = mid; //??????? ??????????????
            }
        }
        if (nums[left] != target)return {-1, -1};
        int left_result = left;
        left = 0;
        right = static_cast<int>(nums.size() - 1);

        while (left < right) {
            //?????????????target????
            int mid = left + ((right - left) >> 1) + 1; //??????????? ??????
            dbg(left, right, mid, nums[mid]);
            if (nums[mid] > target) {
                right = mid - 1;
            } else if (nums[mid] < target) {
                left = mid + 1;
            } else {
                left = mid;
            }

        }
        return {left_result, left};
    };
    vector<int> data{5, 7, 7, 8, 8, 10};
    dbg(answer(data, 8));
}

//. ???????????

inline void LeetCode200::medium_74() {
    std::array<std::array<int, 4>, 3> matrix = {
            std::array<int, 4>{1, 3, 5, 7},
            {10, 11, 16, 20},
            {23, 30, 34, 60}
    };
    // ??????????? ???????????
    int left = 0;
    constexpr size_t matrix_column = matrix.front().size();
    constexpr size_t matrix_row = matrix.size();
    int right = static_cast<int> (matrix_row * matrix_column - 1);
    int target = 3;
    auto transform_really_pos = [](int pos, int row, int column) -> std::pair<int, int> {
        assert(pos >= 0 and pos < row * column);
        return {pos / column, pos % column};
    };
    auto find = [&]() {
        while (left < right) {
            int mid = ((right - left) >> 1) + left;
            dbg(fmt::format("{} {} {} ", left, right, mid));
            auto pos = transform_really_pos(mid, matrix_row, matrix_column);
            dbg(fmt::format("{}", matrix[pos.first][pos.second]));
            if (matrix[pos.first][pos.second] == target) {
                return true;
            } else if (matrix[pos.first][pos.second] > target) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        auto pos = transform_really_pos(left, matrix_row, matrix_column);
        return matrix[pos.first][pos.second] == target;

    };
    dbg(find());

}

// 25  k ????鷭?????

inline void LeetCode200::reverseKGroup() {
    constexpr int length = 10;
    std::unique_ptr<ListNode> ptr = ListNode::new_list(length);

    ListNode *root = ptr.get();
    //????????
    //?????????????????
    int k = 4;
    int time = length / 4;


    // ?????? ?  β ?????????
    auto reverse_list = [](ListNode *start, int need) {
        ListNode *head = nullptr;
        ListNode *cur = nullptr;
        int repeat_time = 0;
        std::tuple<ListNode *, ListNode *, ListNode *> result{nullptr, start, nullptr};
        while (repeat_time != need) {
            cur = start->next;
            start->next = head;
            head = start;
            start = cur;
            repeat_time++;

            bool isLastTime = repeat_time == need;
            if (isLastTime) {
                //???????????????????????
                std::get<0>(result) = head;
                std::get<2>(result) = cur;
            }
        }
        return result;
    };

    ListNode *result = nullptr;
    ListNode *lastTail = nullptr;
    ListNode *lastStart = root;
    if (time > 0) {
        int start = 0;
        while (time != start) {
            auto result_tuple = reverse_list(lastStart, k);
            if (start == 0) {
                result = std::get<0>(result_tuple); //?????????
            } else {
                if (lastTail)lastTail->next = std::get<0>(result_tuple);

            }
            lastStart = std::get<2>(result_tuple);
            lastTail = std::get<1>(result_tuple);
            start++;
        }
    }


}

//162 ?????

inline void LeetCode200::findPeakElement() { //???? ???????????????
    vector<int> data{1, 2, 1, 3, 5, 6, 4};
    size_t left = 0;
    size_t right = data.size() - 1;
    while (left < right) {
        size_t mid = ((right - left) >> 1) + left;

        dbg(fmt::format("{} {} {} ", left, right, mid));
        dbg(fmt::format("{} {} {} ", data[left], data[right], data[mid]));

        if (data[mid] < data[static_cast<size_t>(mid + 1)]) {
            left = mid + 1;
        } else {
            right = mid; // ???????λ????
        }
    }
    dbg(left);

}

// 153 ??????????????С?

inline void LeetCode200::findMin() {
    std::vector<int> data = {3, 4, 5, 1, 2};
    //?????????????С?
    // ??????????е????????? ????????????? ???????????? ??????С????
    auto ans = [](vector<int> &nums) {
        // ????????????
        int left = 0;
        int right = static_cast<int>(nums.size() - 1);

        while (left < right) {
            int mid = ((right - left) >> 1) + left;
            dbg(fmt::format("{} {} {} ", left, right, mid));
            dbg(fmt::format("{} {} {} ", nums[left], nums[right], nums[mid]));
            if (nums[mid] < nums[right])
                right = mid;
            else
                left = mid + 1;

        }
        dbg(nums[left]);

    };
    ans(data);

}

//198. ??????

inline void LeetCode200::houseRobber() {
    /*
    * ???????????С???????????????????????????????????
    ?????????Ψ????????????????????????????????????????????????????????????С??????????????????

    ????????????????????????????????飬?????? ??????????????????? ????????????????????䶮
    */
    vector<int> data{2, 7, 9, 3, 1};
    const auto answerEnum = [](std::vector<int> &nums) {

        const auto answerImpl = [](int cur, int money, std::vector<int> &nums, auto &&answerImpl) -> int {
            if (cur >= nums.size())return money;
            int result = money + nums[cur];

            std::max({answerImpl(cur + 1, money, answerImpl),
                      result,
                      answerImpl(cur + 2, money, answerImpl)});
            return result;
        };

    };
    const auto answerDp = [](std::vector<int> &nums) {

    };
}

//11. ???????????

inline void LeetCode200::maxArea() {
    vector data{1, 8, 6, 2, 5, 4, 8, 3, 7};
    const auto answer = [](vector<int> &height) {
        int j = static_cast<int> (height.size() - 1);
        int i = 0;
        int result = (j - i) * std::min(height[i], height[j]);
        while (i != j) {
            result = std::max((j - i) * (std::min(height[i], height[j])), result);
            if (height[i] < height[j])i++;
            else j++;
        }
        return result;
    };
    const auto answerForward = [](vector<int> &height) {
        int j = static_cast<int> (height.size() - 1);
        int i = 0;
        int result = (j - i) * std::min(height[i], height[j]);
        int n = 0;

        while (i != j) {
            if (height[i] < height[j])n = height[i];
            else n = height[j];
            result = std::max(result, n * (j - i));
            while (i != j and height[i] <= n) {
                i++;
            }
            while (i != j and height[j] <= n) {
                j--;
            }
        }
        return result;
    };
}

//82. ????????????е??????? II

inline void LeetCode200::deleteDuplicatesFromList() {
    //???????????????????? head ?? ?????????????????????????????????????? ?????? ??????????? ??
    std::vector<int> data = {1, 1, 2, 2};
    std::unique_ptr<ListNode> ptr = ListNode::new_list(data);
    ListNode *head = ptr.get();
    auto answer_forward = [&]() {
        auto root = head;
        if (root == nullptr)return head;
        int val;
        ListNode *cur = root->next;
        ListNode *prev = root;
        bool isFirstTime = true;
        while (cur != nullptr) {
            val = root->val;

            if (val == cur->val) {
                while (cur != nullptr and cur->val == val) {
                    cur = cur->next;
                }

                if (prev == root) {
                    if (cur == nullptr)return static_cast<ListNode *>(nullptr);
                    else {
                        head = cur;
                        prev = cur;
                        root = cur;
                    }
                } else {
                    prev->next = cur;
                    root = cur;
                }
                if (cur == nullptr)break;
                cur = cur->next;

            } else {
                prev = root;
                root = cur;
                cur = cur->next;
            }

        }
        return head;
    };
    //answer_forward();
    auto answer_dummpy_head = [&]() {
        auto root = head;
        if (root == nullptr)return head;
        auto dummy = std::make_unique<ListNode>(0, head);
        auto cur = dummy.get();
        while (cur->next != nullptr and cur->next->next != nullptr) {
            if (cur->next->val == cur->next->next->val) {
                auto forward = cur->next->next;
                do { forward = forward->next; } while (forward != nullptr and forward->val != cur->next->val);
                cur->next = forward;
            } else {
                cur = cur->next;
            }
        }
        return dummy->next;
    };
}

//15. ???????

inline void LeetCode200::three_num() {
    // ??????к?? 0?????????????
    std::vector nums = {-2, 0, 0, 2, 2};

    auto answer = [&](const std::vector<int> &data) -> std::vector<std::vector<int>> {
        if (nums.size() < 3)return {};
        // ?????????
        std::unordered_map<int, int> map;
        for (auto i: data) {
            if (map.find(i) == map.end()) {
                map.insert({i, 1});
            } else {
                map[i] += 1;
            }
        }
        dbg(map);
        std::vector<std::vector<int>> result;
        for (auto first: data) {
            if (map[first] > 0) {
                //????????????????????

                int take_time = -1;
                int value = -first;
                map[first] -= 1;
                bool if_not_match = true;
                for (auto second: data) {
                    if (map[second] > 0) {
                        //???????????
                        map[second] -= 1;
                        int third = value - second;
                        if (map.find(third) != map.end() and map[third] > 0) {
                            if (not if_not_match) {
                                if (map[first] <= 0) {
                                    map[second] += 1;
                                    continue;
                                }
                                map[first] -= 1;
                            } else {
                                if_not_match = false;
                            }
                            map[third] -= 1;
                            dbg(map[third], map[first], if_not_match ? map[first] : map[first] - 1);

                            result.emplace_back(vector<int>{first, second, third});

                        } else {
                            map[second] += 1;
                        }
                    }
                }
                if (if_not_match) {
                    map[first] += 1;
                }

            }
        }
        dbg(map);
        dbg(result);
        return result;

    };
    //answer(nums);

    auto sort_answer = [&](std::vector<int> &data) -> std::vector<std::vector<int>> {
        std::vector<int>::size_type size = data.size();
        if (size < 3)return {};
        std::sort(data.begin(), data.end());
        int start = 0;

        std::vector<std::vector<int>> result;
        while (start < size - 2 and data[start] <= 0) {
            if (start > 0 and data[start] == data[static_cast<size_t>(start) - 1]) {
                start++;
                continue;
            } // ???????????
            //data ???????????? ?????????????????????????
            int left = start + 1;
            int right = static_cast<int>(size - 1);
            while (left < right) {
                int cur = data[left] + data[start] + data[right];
                //auto str = fmt::format("left{} right{} start{}", left, right, start);
                //dbg(str, cur);
                if (cur == 0) {
                    //dbg(data[start], data[left], data[right]);
                    result.emplace_back(std::vector<int>{data[start], data[left], data[right]});
                    // ?????????left ?????????????????λ??
                    while (left < right and data[left] == data[static_cast<size_t>(left) + 1])left++;
                    while (left < right and data[right] == data[static_cast<size_t>(right) - 1])right--;
                    left++;
                    right--; //????????????????????????
                } else if (cur > 0) {
                    right -= 1;
                } else {
                    left += 1;
                }
            }
            start++;
        }
        return result;
    };
    auto parm = vector<int>{-1, 0, 1, 2, -1, -4};
    dbg(sort_answer(parm));
}

//70. ?????

inline void LeetCode200::climbStairs() {
    auto answer = [](int n) -> int {

        constexpr auto fib_impl = [] {
            std::array<int, 31> fib{0, 1};
            for (int i = 2; i != 31; ++i) {
                fib[i] = fib[i - 1] + fib[i - 2];
            }
            return fib;
        }();
        return fib_impl[n];
    };
}

void LeetCode200::connectRight() {
    //std::list<ListNode*> container;
    //std::unique_ptr<ListNode> first = LeetCode200::decode(10);
    //auto root = first.get();
    //if (root == NULL)return NULL;
    //vector<Node*> container;
    //container.push_back(root);

    //while (not container.empty())
    //{
    //	int curLayer = container.size();
    //	Node* lastNode = nullptr;
    //	for (int i = 0; i < curLayer; i++)
    //	{
    //		Node* back = container.back();
    //		container.pop_back();
    //		if (lastNode != nullptr) {
    //			lastNode->left = back;
    //		}
    //		lastNode = back;
    //		// ???????д???
    //		if (back->left) {
    //			container.push_back(back->left);
    //		}
    //		if (back->right) {
    //			container.push_back(back->right);
    //		}
    //	}
    //}
    //return root;

}

void LeetCode200::shortestPathBinaryMatrix() {
    //vector<vector<int>> grid = { {0,0,0},{1,1,0},{1,1,0} };
    // 8????????????л??????????? ??????б??????????????
    auto dfsDp = [&](const vector<vector<int>> &grid, int x, int y, int count, auto dfs) -> int {
        if (x == grid.size() - 1 and y == grid[0].size() - 1)return count + 1;

        if (x >= grid.size() or x < 0 or y < 0 or y >= grid[0].size())return INT_MAX;
        dbg(x, y);
        if (grid[x][y] == 1)return INT_MAX;
        count += 1;
        return std::min({dfs(grid, x + 1, y, count, dfs),
                         dfs(grid, x, y + 1, count, dfs),
                         dfs(grid, x - 1, y, count, dfs),
                         dfs(grid, x, y - 1, count, dfs),
                         dfs(grid, x + 1, y + 1, count, dfs),
                         dfs(grid, x - 1, y - 1, count, dfs),
                         dfs(grid, x - 1, y + 1, count, dfs),
                         dfs(grid, x + 1, y - 1, count, dfs)});
    };


    /*vector<vector<int>> grid = { {0, 1, 0, 0, 1, 1, 0},
        {1, 0, 0, 0, 0, 0, 0},{1, 0, 0, 1, 1, 1, 1},
        {0, 1, 0, 0, 0, 0, 0},{1, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 1, 0, 0, 0},{1, 0, 1, 0, 0, 1, 0} };*/
    vector<vector<int>> grid = {{0, 0, 0},
                                {1, 1, 0},
                                {1, 1, 0}};


    //	vector<vector<int>> grid = { {0,0,0},{1,1,0},{1,1,1} };

    const auto answerDfsWithVisited = [&](int x, int y, int count, int n, auto &&dfs) -> int {
        if (x == n - 1 and y == n - 1)return count + 1;
        if (x >= n or x < 0 or y < 0 or y >= n)return INT_MAX;
        if (grid[x][y] == 1)return INT_MAX;

        count += 1;

        int result = INT_MAX;


        grid[x][y] = 1;
        for (int i = -1; i < 2; i++) {
            for (int j = -1; j < 2; j++) {
                if (i == 0 and j == 0) continue;
                if (x + i >= n or x + i < 0 or y + j < 0 or y + j >= n) continue;
                result = std::min(result, dfs(x + i, y + j, count, n, dfs));
                dbg(x + i, y + j, result);
            }
        }
        grid[x][y] = 0;
        return result;
    };

    //dbg(answerDfsWithVisited(0, 0, 0, grid.size(), answerDfsWithVisited));
    const auto answerQueue = [](vector<vector<int>> &grid) {
        if (grid[0][0] == 1)return -1;
        size_t n = grid.size();
        int ans = 1;
        const int dire[8][2] = {{1,  0},
                                {-1, 0},
                                {0,  1},
                                {0,  -1},
                                {1,  1},
                                {1,  -1},
                                {-1, -1},
                                {-1, 1}};
        queue<std::pair<int, int> > q;
        q.emplace(0, 0);         //??0,0???
        grid[0][0] = 1;           //????1???????
        while (!q.empty()) {      // bfs
            size_t m = q.size(); //?????????е????
            while (m--) {
                auto[x, y] = q.front();
                q.pop();
                if (x == n - 1 && y == n - 1)return ans;
                for (auto i: dire) {                       //????????????
                    int nx = x + i[0];
                    int ny = y + i[1];
                    if (nx < 0 || ny < 0 || nx >= n || ny >= n)continue;   //?ж???????
                    if (grid[nx][ny] == 0) {        //?ж????????
                        q.emplace(nx, ny);
                        grid[nx][ny] = 1;         //???
                        dbg(grid);
                    }
                }
            }
            ans++;          //??????????
        }
        return -1;
    };
    //dbg(answerQueue(grid));


    const auto answerQueueWidth = [](vector<vector<int>> &grid) {
        if (grid[0][0] == 1)return -1;
        size_t n = grid.size();
        int ans = 1;
        const int dire[8][2] = {{1,  0},
                                {-1, 0},
                                {0,  1},
                                {0,  -1},
                                {1,  1},
                                {1,  -1},
                                {-1, -1},
                                {-1, 1}};
        queue<std::pair<int, int> > q;
        q.emplace(0, 0);         //??0,0???
        grid[0][0] = 1;           //????1???????
        while (!q.empty()) {      //bfs
            size_t m = q.size(); //?????????е???? ?????
            while (m--) {
                auto[x, y] = q.front();
                q.pop();
                if (x == n - 1 && y == n - 1)return ans;
                for (auto i: dire) {                       //????????????
                    int nx = x + i[0];
                    int ny = y + i[1];
                    if (nx < 0 || ny < 0 || nx >= n || ny >= n)continue;   //?ж???????
                    if (grid[nx][ny] == 0) {        //?ж????????
                        q.emplace(nx, ny);
                        grid[nx][ny] = 1;         //???
                        dbg(grid);
                    }
                }
            }
            ans++;          //??????????
        }
        return -1;
    };

}

void LeetCode200::solveRound() {

    const auto answerDfs = [](vector<vector<char>> &board) {
        size_t n = board.size();
        size_t m = board[0].size();
        vector<int> visited(n * m);


        auto dfsAllBoard = [&](int x, int y, auto &&dfsAllBoard) {
            if (x < 0 or y < 0 or x >= n or y >= m)return;
            if (visited[x * m + y] == 0 and board[x][y] == 'O') {
                visited[x * m + y] = 1;
                dfsAllBoard(x + 1, y, dfsAllBoard);
                dfsAllBoard(x, y + 1, dfsAllBoard);
                dfsAllBoard(x, y - 1, dfsAllBoard);
                dfsAllBoard(x - 1, y, dfsAllBoard);
            }
        };

        // ???????? ?????δ??????????????д???
        for (int i = 0; i < m; i++) {
            for (auto j: std::initializer_list<size_t>{0, n - 1}) {
                dfsAllBoard(static_cast<int>(j), i, dfsAllBoard);
            }
        }
        for (int i = 0; i < n; i++) {
            for (auto j: std::initializer_list<size_t>{0, m - 1}) {
                dfsAllBoard(i, static_cast<int>(j), dfsAllBoard);

            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (board[i][j] == 'O' and visited[i * m + j] != 1) {
                    board[i][j] = 'X';
                    dbg(board);
                }
            }
        }
    };
    vector<vector<char>> board = {
            {'X', 'O', 'X', 'O', 'X', 'O'},
            {'O', 'X', 'O', 'X', 'O', 'X'},
            {'X', 'O', 'X', 'O', 'X', 'O'},
            {'O', 'X', 'O', 'X', 'O', 'X'}};

    answerDfs(board);
    //dbg(answerDfsWithVisited(0, 0, 0, 2, answerDfsWithVisited));

}

void LeetCode200::allPathsSourceTarget() {
    const auto answerDfs = [](vector<vector<int>> &graph) {
        vector<vector<int>>::size_type nodeNum = graph.size();
        std::set<int> visited;
        vector<vector<int>> result;

        for (int node = 0; node < nodeNum; node++) {
            if (not graph[node].empty()) {

            }

        }
    };
}

void LeetCode200::subsets() {
    vector<vector<int>> (*answer)(vector<int> &) = [](vector<int> &nums) -> vector<vector<int>> {
        std::vector<std::vector<int>> result;
        size_t numsSize = nums.size();
        auto dfs = [&result, numsSize, &nums](int curPos, vector<int> &other, auto &&dfs) -> void {
            if (curPos == numsSize) {
                result.emplace_back(other);
            } else {
                dfs(curPos + 1, other, dfs);
                other.emplace_back(nums[curPos]);
                dfs(curPos + 1, other, dfs);
                other.pop_back();
            }
        };
        std::vector<int> tmp;
        dfs(0, tmp, dfs);
        return result;
    };

    vector<vector<int>> (*answerBinary)(vector<int> &) = [](vector<int> &nums) -> vector<vector<int>> {
        std::vector<int> temp;
        vector<vector<int>> result;
        auto numSize = nums.size();
        auto last = 1 << numSize;
        result.reserve(last);
        temp.reserve(numSize);
        for (int i = 0; i < last; ++i) {
            temp.clear();
            int cur = i;
            int start = 0;
            do {
                if ((cur & 1) == 0) {
                    temp.push_back(nums[start]);
                }
                start++;
                cur = cur >> 1;
            } while (cur != 0);
            result.push_back(temp);
        }
        return result;
    };
}

void LeetCode200::otherSubSets() {
    vector<vector<int>> (*subsetsWithDup)(vector<int> &) = [](vector<int> &nums) -> vector<vector<int>> {
        std::vector<int> temp;
        vector<vector<int>> result;
        auto numSize = nums.size();
        auto last = 1 << numSize;
        std::set<int> uniqueSet;
        for (int i = 0; i < last; ++i) {
            temp.clear();
            int cur = i;
            if ((cur & 1) == 1 and not uniqueSet.insert(nums[static_cast<size_t>(std::sqrt(cur))]).second) { //需要选择当前的元素
                continue;
            } else {
                int start = 0;// 只有start 元素时 将当前存在的
                do {
                    if ((cur & 1) == 1) {
                        temp.push_back(nums[start]);
                    }
                    start++;
                    cur = cur >> 1;
                } while (cur != 0);
                result.push_back(temp);
            }
        }
        return result;
    };

    vector<vector<int>> (*subsetsWithDupSet)(vector<int> &) = [](vector<int> &nums) -> vector<vector<int>> {
        std::vector<int> temp;
        vector<vector<int>> result;
        auto numSize = nums.size();
        auto last = 1 << numSize;
        std::set<std::vector<int>> uniqueSet;
        std::sort(nums.begin(), nums.end()); //要不然 122  和 221 就不一样了
        for (int i = 0; i < last; ++i) {
            temp.clear();
            int cur = i;
            int start = 0;// 只有start 元素时 将当前存在的
            do {
                if ((cur & 1) == 1) {
                    temp.push_back(nums[start]);
                }
                start++;
                cur = cur >> 1;
            } while (cur != 0);
            if (uniqueSet.insert(temp).second)
                result.push_back(temp);
        }
        return result;
    };

}

void LeetCode200::combinationSum() {
    /*
     * 给你一个 无重复元素 的整数数组candidates 和一个目标整数target，找出candidates中可以使数字和为目标数target
     * 的 所有不同组合 ，并以列表形式返回。你可以按 任意顺序 返回这些组合。
     */

    //warn 错误方法 将多余的数字重复进行了计算
    vector<vector<int>> (*answer)(vector<int> &, int) = [](vector<int> &candidates, int target) -> vector<vector<int>> {
        size_t size = candidates.size();
        vector<vector<int>> result;
        auto dfs = [&, target, size](int curPos, int curNum, std::vector<int> &cur,
                                     auto &&dfs) -> void {
            dbg(curNum);
            if (curNum == target) {
                dbg(cur);
                result.push_back(cur);
            }
            if (curNum > target or curPos >= size) return;

            dfs(curPos + 1, curNum, cur, dfs);
            size_t curContainer = cur.size();
            for (int i = 1; i <= (target - curNum) / candidates[curPos]; ++i) {
                cur.push_back(candidates[curPos]);
                dfs(curPos + 1, curNum + i * candidates[curPos], cur, dfs);
            }
            cur.erase(cur.begin() + static_cast<long long>(curContainer), cur.end());
        };
        std::vector<int> cur;
        dfs(0, 0, cur, dfs);
        return result;
    };
    //    std::vector<int> data{2, 3, 6, 7};
    //    dbg(answer(data, 7));

    vector<vector<int>>
    (*answerOther)(vector<int> &, int) =
    [](vector<int> &candidates, int target) -> vector<vector<int>> {
        size_t size = candidates.size();
        vector<vector<int>> result;
        auto dfs = [&, target, size]
                (int curPos, int curSum, std::vector<int> &cur,
                 auto &&dfs) -> void {

            if (curSum == target) {
                result.push_back(cur);
                return;
            }
            if (curSum > target or curPos >= size) return;

            dfs(curPos + 1, curSum, cur, dfs);
            size_t curContainer = cur.size();
            for (int i = 1; i <= (target - curSum) / candidates[curPos]; ++i) {
                cur.push_back(candidates[curPos]);
                dbg(curPos + 1, curSum + i * candidates[curPos], cur);
                //不应该当前的进入下一步 应该重复当前 将当前的数字 从零到满的情况全部拿全
                dfs(curPos + 1, curSum + i * candidates[curPos], cur, dfs);
            }
            cur.erase(cur.begin() + static_cast<long long>(curContainer), cur.end());
        };
        std::vector<int> cur;
        dfs(0, 0, cur, dfs);
        return result;
    };
    //    std::vector<int> data{2, 3, 6, 7};
    //    dbg(answerOther(data, 7));
    vector<vector<int>>
    (*answerWithOutDup)(vector<int> &, int) =
    [](vector<int> &candidates, int target) -> vector<vector<int>> {
        vector<vector<int>> ans;
        vector<int> nums;
        sort(candidates.begin(), candidates.end());
        auto backtrace = [](vector<vector<int>> &ans,
                            vector<int> &candidates,
                            vector<int> &nums,
                            int cur, int target,
                            auto &&backtrace) {
            if (0 == target) {
                ans.push_back(nums);
                return;
            }
            // 当前for 循环中的数据 将要到达于 left+1 的数据也是当前的层数为 next层
            // 同一层数中不能多次取到同一个数字
            //                1
            //             1    2
            //          1        1(错误)
            for (int next = cur; next < candidates.size() && target - candidates[next] >= 0; next++) {
                bool isNotFirstOne = next > cur; //不是第一个 并且元素还相同 则直接跳过
                if (isNotFirstOne && candidates[next - 1] == candidates[next]) { //
                    dbg(next, cur, candidates[next - 1], candidates[next]);
                    continue;
                }
                nums.push_back(candidates[next]);
                dbg(nums);
                backtrace(ans, candidates, nums, next + 1, target - candidates[next], backtrace);
                nums.pop_back();
            }
        };

        backtrace(ans, candidates, nums, 0, target, backtrace);
        return ans;
    };
    std::vector<int> data{6, 1, 1, 2, 5};
    dbg(answerWithOutDup(data, 8));
}

void LeetCode200::letterCombinations() {
    //


    auto answer = [&](const std::string_view digit) {
        std::vector<std::vector<char>> data = {{'a', 'b', 'c'},
                                               {'d', 'e', 'f'},
                                               {'g', 'h', 'i'},
                                               {'j', 'k', 'l'},
                                               {'m', 'n', 'o'},
                                               {'p', 'q', 'r', 's'},
                                               {'t', 'u', 'v'},
                                               {'w', 'x', 'y', 'z'}};
        // dfs
        vector<string> result;
        size_t capacity = 1;
        for (char ch: digit) {
            capacity *= data[static_cast<size_t>(ch - '0' - 2)].size();
        }
        result.reserve(capacity);
        auto dfs = [&](std::string &last, std::string_view curDigit, auto &&dfs) -> void {
            if (curDigit.empty()) {
                result.emplace_back(last);
                return;
            }
            size_t num = curDigit[0] - '0' - 2;
            for (char curChar: data[num]) {
                last += curChar;
                dbg(last + "  " + curChar);
                dfs(last, curDigit.substr(1), dfs);
                last.pop_back();
            }
        };
        string cur;
        dfs(cur, digit, dfs);
        return result;
    };
    dbg(answer("8"));
}

void LeetCode200::generateParenthesisByBrackets() {
    auto answer = [](int n) {
        std::vector<string> result;
        std::vector<int> tmp;
        tmp.resize(n * 2);
        std::fill_n(tmp.begin() + n, n, 1);
        string curResult;
        curResult.reserve(n * 2);
        do {
            int count = 0;
            bool isSuccess = true;
            for (int i: tmp) {
                if (i == 0) { count++; }
                else {
                    if (count == 0) {
                        isSuccess = false;
                        break;
                    }
                    count--;
                }
            }
            if (isSuccess) {
                curResult.clear();
                for (int i: tmp) {
                    if (i == 0) {
                        curResult.push_back('(');
                    } else {
                        curResult.push_back(')');
                    }
                }
                result.emplace_back(curResult);
            }
        } while (std::next_permutation(tmp.begin(), tmp.end()));
        return result;
    };
    //    dbg(folly::join(",", answer(3)));
    auto answerDp = [](int n) {
        std::vector<string> result;
        result.reserve(n * 2);
        auto dfs = [&](string &cur, int left, int right, auto &&dfs) -> void {
            if (left == 0 and right == 0) {
                result.emplace_back(cur);
            }
            if (left > right) {
                return;
            }
            if (left > 0) {
                cur.push_back('(');
                dfs(cur, left - 1, right, dfs);
                cur.pop_back();
            }
            if (right > 0) {
                cur.push_back(')');
                dfs(cur, left, right - 1, dfs);
                cur.pop_back();
            }
        };
        string cur;
        cur.reserve(n * 2);
        dfs(cur, n, n, dfs);
        dbg(folly::join(",", result));
    };
    answerDp(3);
}

void LeetCode200::existInMesh() {
    auto exist = []() -> bool { //vector<vector<char>> &board, string const &word
        // [0-row][0-column]
//        auto cache = std::vector<int>((board.size() + 1) * (board[0].size() + 1) * (word.size() + 1));

        std::vector<std::vector<char>> board = {{'A', 'B', 'C', 'E'},
                                                {'S', 'F', 'C', 'S'},
                                                {'A', 'D', 'E', 'E'}};
        string word = "SEE";
        std::unique_ptr<int[]> visited(new int[board.size() * board[0].size()]);
        auto dfs = [&](int row, int column, int wordPos, auto &&dfs) -> bool {

            if (wordPos == word.size()) {
                dbg(row, column, wordPos);
                return true;
            }
            if (row == board.size() or row < 0 or column < 0 or column == board[0].size())return false;
            if (board[row][column] == word[wordPos] and visited[row * board[0].size() + column] == 0) {
                ++wordPos;
                visited[row * board[0].size() + column] = 1;
                if (dfs(row + 1, column, wordPos, dfs)) return true;
                if (dfs(row, column + 1, wordPos, dfs)) return true;
                if (dfs(row - 1, column, wordPos, dfs)) return true;
                if (dfs(row, column - 1, wordPos, dfs)) return true;
                visited[row * board[0].size() + column] = 0;

            }
            return false;
        };
        bool result = false;
        //        for (int row = 0; row < board.size(); row++) {
        //            for (int column = 0; column < board[0].size(); column++) {
        //                if (result)break;
        //                if (board[row][column] == word[0]) {
        //
        //
        //                }
        //            }
        //        }
        result = dfs(1, 3, 0, dfs);
        dbg(result);
        return result;

    };

    exist();

}

void LeetCode200::robOnStreet() {
    vector<int> nums{1, 3, 1, 3, 100};
    auto rob = [&]() {// 每次只需要知道当前 需要计算的式子就是了
        std::vector<int> dp(nums.size() + 1);
        dp[0] = 0;
        dp[1] = nums[0];
        for (int i = 2; i < nums.size(); ++i) {
            dbg(dp);
            dp[i] = std::max(dp[i - 2] + nums[i], dp[i - 1]);
        }
        dbg(dp);
        return dp.back();
    };
    //    rob();
    auto rob2 = [&]() {
        if (nums.size() <= 3)return *std::max_element(nums.begin(), nums.end());
        auto robImpl = [](vector<int> &nums, int start, int end) {
            int pre = nums[start];
            //left 为当前的下一个位置 所以应该为 f(2) 而不是直接变成 nums[start+1]
            int next = std::max(nums[start + 1], pre);
            int result = next;
            for (int i = start + 2; i < end; i++) {
                result = std::max(pre + nums[i], next);
                pre = next;
                next = result;
            }
            return result;
        };
        //        return robImpl(nums, 0, nums.size() - 1);
        return robImpl(nums, 1, nums.size());
        //        return std::max(robImpl(nums, 0, nums.size() - 1), robImpl(nums, 1, nums.size()));
    };
    dbg(rob2());
}

void LeetCode200::jumpGame() {
    //
    std::vector<int> data{1, 1, 1, 4};

    auto dfs = [&](int pos, int length, auto &&dfs) -> bool {
        if (pos == length)return true;
        else if (pos > length)return false;
        else {
            for (int i = 1; i <= data[pos]; ++i) {
                if (dfs(pos + i, length, dfs)) return true;
            }
            return false;
        }

    };

    auto dp = [](vector<int> &data) {
        std::vector<int> dp(data.size() + 1);
        dp[data.size()] = 1;
        for (int cur = static_cast<int>(data.size() - 1); cur >= 0; cur++) {
            for (int interval = 1; interval <= data[cur]; ++interval) {
                if (cur + interval == data.size()) {
                    dp[cur] = 1;
                    break;
                } else if (cur + interval < data.size()) {
                    dp[cur] = dp[cur + interval];
                } else {
                    dp[cur] = 0;
                }
            }

        }
        return dp[0] == 1;
    };
    //    dbg(greedy(data));
    auto greedy = [](vector<int> &data) {
        int n = data.size();
        int last = n - 1;
        for (int i = last - 1; i >= 0; i--) {
            if (data[i] + i >= last) {
                last = i;
            }
        }
        return last == 0;
    };


    auto dp2 = [](vector<int> &data) {
        int n = static_cast<int>(data.size());
        if (n == 1)return 0;
        std::vector<int> dp(n);
        dp[n - 1] = 1;

        for (int cur = n - 2; cur >= 0; --cur) {
            int interval = std::min(data[cur], n - cur);
            for (int step = 1; step <= interval; ++step) {
                if (dp[cur + step]) {
                    dp[cur] = 1;
                    break;
                }
            }
        }
        dbg(dp);
        dbg(data);
        int result = 0;
        for (int i = 0; i < n - 1;) {
            // 当前的 i能到达的最远距离
            // 将当前 最近的中的
            for (int last = std::min(data[i], n - i - 1); last >= 1; --last) {
                if (dp[i + last]) {
                    i += last;
                    ++result;
                    break;
                }
            }
        }
        return result;
    };

    //    dbg(dp2(data));
    auto greedy2 = [](std::vector<int> &data) {

        // 贪心 算法当前的 当前跳跃的范围找到然后找到下一次可以到达的次数
        int start = 0;
        int end = 1; //到达位置的下一个位置
        int n = data.size();
        int result = 0;
        while (end < n) { // 当 end=n 表示当前的 end 可以到达 n-1  end >n 则 end可以到达 n
            int maxPos = 0;
            for (int i = start; i < end; ++i) {
                // 可以到达的最大位置
                maxPos = std::max(maxPos, i + data[i]);
            }
            start = end;
            end = maxPos + 1;
            ++result;
        }

        return result;
    };
    //    dbg(greedy2(data));
    int result = 0;
    result = [](int m, int n) {
        //        int data[m][n];

        std::vector<int> dp(m * n);
        dp[m * n - 1] = 1;
        for (int row = m - 1; row >= 0; row--) {
            for (int column = n - 1; column >= 0; column--) {
                int cur = column + row * n;
                if (column + 1 < n) {
                    dp[cur] += dp[cur + 1];
                }
                if (row + 1 < m) {
                    dp[cur] += dp[cur + n];
                }
            }
        }
        dbg(dp);
        return dp[0];
    }(3, 2);

    // c++ 不支持变长数组
//    int vlaResult = [](int m, int n) {
//        int dp[m][n];
//        dp[m - 1][n - 1] = 1;
//        for (int row = m - 1; row >= 0; --row) {
//            for (int column = n - 1; column >= 0; --column) {
//
//                if (column + 1 < n) {
//                    dp[row][column] += dp[row][column + 1];
//                }
//                if (row + 1 < m) {
//                    dp[row][column] += dp[row + 1][column];
//                }
//            }
//        }
//        return dp[0][0];
//
//    }(3, 2);
//    dbg(result == vlaResult);



}

void LeetCode200::longestPalindrome() {
    string s = "abb";
    //    if (s.size() == 1)return std::tostring(s[0]);
    auto reverseBegin = s.rbegin();
    auto reverseEnd = s.rend();
    auto forwardBegin = s.begin();
    auto forwardEnd = s.end();
    int left = 0;
    int right = 1;
    while (forwardBegin != forwardEnd) {
        if (*forwardBegin++ == *reverseBegin++) {
            int count = 1;
            dbg(forwardBegin - s.begin());
            while (forwardBegin != forwardEnd) {
                if (*forwardBegin == *reverseBegin) {
                    count++;
                    ++forwardBegin;
                    ++reverseBegin;
                } else {
                    break;
                }
            }
            dbg(forwardBegin - s.begin(), count);
            // 将当前的答案转换为当前的存在的 left right 两个边界
            // 当前left 应该为
            if (count > right - left) {
                left = forwardBegin - s.begin() - count;
                right = left + count;
                dbg(left);
            }
            forwardBegin = forwardBegin - count + 1;
            dbg(*forwardBegin, forwardBegin - s.begin());
            reverseBegin = reverseBegin - count + 1;
        }
    }


    dbg(string(s.begin() + left, s.begin() + right));

}

void LeetCode200::maxNum() {
    //给定一组非负整数 nums，重新排列每个数的顺序（每个数不可拆分）使之组成一个最大的整数。
    //
    //注意：输出结果可能非常大，所以你需要返回一个字符串而不是整数。
    std::vector<int> nums = {0, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    auto answer_first = [&]() mutable {
        std::sort(nums.begin(), nums.end(), [](int first, int second) {
            // 得到每个数的最高位
            string firstStr = std::to_string(first);
            string secondStr = std::to_string(second);
            int firstIndex = 0;
            int secondIndex = 0;
            auto firstSize = firstStr.size();
            auto secondSize = secondStr.size();
            while (firstIndex < firstSize and secondIndex < secondSize) {
                if (firstStr[firstIndex] > secondStr[secondIndex]) {
                    return true;
                } else if (firstStr[firstIndex] < secondStr[secondIndex]) {
                    return false;
                }
                ++firstIndex;
                ++secondIndex;
            }
            if (firstSize == secondSize)return true;
            else if (firstSize < secondSize) {
                char curFirstNum = firstStr.back();
                while (secondIndex < secondSize) {
                    if (secondStr[secondIndex] > curFirstNum)return false;
                    else if (secondStr[secondIndex] < curFirstNum)return true;
                    ++secondIndex;
                }

            } else {
                char curSecondNum = secondStr.back();
                while (firstIndex < firstSize) {
                    if (firstStr[firstIndex] > curSecondNum)return true;
                    else if (firstStr[firstIndex] < curSecondNum)return false;
                    ++firstIndex;
                }
            }

            return true;

        });
    };

    auto answer_second = [&]()mutable {
        std::sort(nums.begin(), nums.end(), [](int first, int second) {
            auto numWei = [](int cur) {
                int w = 0;
                while (cur != 0) {
                    cur /= 10;
                    ++w;
                }
                return w;
            };
            int firstWei = numWei(first);
            int secondWei = numWei(second);
            if (firstWei + secondWei < 9) {
                int firstCopy = first * std::pow(10, secondWei) + second;
                int secondCopy = second * std::pow(10, firstWei) + first;
                dbg(first, second, firstCopy, firstWei, secondWei, secondCopy, firstCopy > secondCopy);
                return firstCopy > secondCopy;
            }
            return std::to_string(first) + std::to_string(second) > std::to_string(second) + std::to_string(first);

        });
    };
//    answer_second();
    auto impl = [](int first, int second) {
        auto numWei = [](int cur) {
            int w = 0;
            while (cur != 0) {
                cur /= 10;
                ++w;
            }
            return w;
        };
        int firstWei = numWei(first);
        int secondWei = numWei(second);
        if (firstWei + secondWei < 9) {
            int firstCopy = first * std::pow(10, secondWei) + second;
            int secondCopy = second * std::pow(10, firstWei) + first;
            dbg(first, second, firstCopy, firstWei, secondWei, secondCopy, firstCopy > secondCopy);
            return firstCopy > secondCopy;
        }
        return std::to_string(first) + std::to_string(second) > std::to_string(second) + std::to_string(first);

    };

    auto answer_final = [&]() mutable {
        std::sort(nums.begin(), nums.end(), [](int first, int second) {
            // 得到每个数的最高位
            auto numWei = [](int cur) {
                int w = 0;
                while (cur != 0) {
                    cur /= 10;
                    ++w;
                }
                return w;
            };
            int firstWei = numWei(first);
            int secondWei = numWei(second);

            /*
             *  long sx = 10, sy = 10;
                while(sx <= x) sx *= 10;
                while(sy <= y) sy *= 10;
                return sy * x + y > sx * y + x;
             */
            double firstCopy = first * pow(10, secondWei) + second;
            double secondCopy = second * pow(10, firstWei) + first;
            return firstCopy > secondCopy;


        });

    };

    string result;
    result.reserve(nums.size());
    for (const int val: nums) {
        result.append(std::to_string(val));
    }


    fmt::print("{} {}", fmt::join(nums, ","), result);
}




