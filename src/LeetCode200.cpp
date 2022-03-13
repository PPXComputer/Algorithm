#include "../include/LeetCode200.h"
#include <array>

#include <string>
#include <queue>
#include <map>
#include <fmt/format.h>
#include <dbg.h>
#include <unordered_map>
#include <set>

using std::array;
using std::vector;
using std::queue;
using std::string;

inline void LeetCode200::medium_33() {
    //??????????
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
    int count = 0;


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
    if (time > 0 and length != 1) {
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
    int left = 0;
    int right = data.size() - 1;
    while (left < right) {
        int mid = ((right - left) >> 1) + left;

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
    //std::unique_ptr<ListNode> first = LeetCode200::new_list(10);
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
    //			lastNode->next = back;
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
        int n = grid.size(), ans = 1;
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
            int m = q.size(); //?????????е????
            while (m--) {
                auto[x, y] = q.front();
                q.pop();
                if (x == n - 1 && y == n - 1)return ans;
                for (int i = 0; i < 8; i++) {                       //????????????
                    int nx = x + dire[i][0];
                    int ny = y + dire[i][1];
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
        int n = grid.size(), ans = 1;
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
            int m = q.size(); //?????????е???? ?????
            while (m--) {
                auto[x, y] = q.front();
                q.pop();
                if (x == n - 1 && y == n - 1)return ans;
                for (int i = 0; i < 8; i++) {                       //????????????
                    int nx = x + dire[i][0];
                    int ny = y + dire[i][1];
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
        int n = board.size();
        int m = board[0].size();
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
            for (int j: {0, n - 1}) {
                dfsAllBoard(j, i, dfsAllBoard);
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j: {0, m - 1}) {
                dfsAllBoard(i, j, dfsAllBoard);

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
            if ((cur & 1) == 1) { //需要选择当前的元素
                int curNum = nums[static_cast<size_t>(std::sqrt(cur))];
                if (uniqueSet.insert(curNum).second) {
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
}



