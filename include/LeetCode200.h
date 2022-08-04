锘�#pragma once

#include <cassert>
#include <memory>
#include <vector>

class LeetCode200 {
public:
    static void medium_33();

    static void medium_34();

    //. 鎼滅储浜岀淮鐭╅樀
    static void medium_74();

    // 25  k 涓竴缁勭炕杞摼琛�
    static void reverseKGroup();

    //162 瀵绘壘宄板��
    static void findPeakElement();

    // 153 鎵惧埌鏃嬭浆鏁扮粍鐨勭殑鏈�灏忓��
    static void findMin();

    //198. 鎵撳鍔垗
    static void houseRobber();

    //11. 鐩涙渶澶氭按鐨勫鍣�
    static void maxArea();

    //79. 鍗曡瘝鎼滅储

    static void existInMesh();

    //82. 鍒犻櫎鎺掑簭閾捐〃涓殑閲嶅鍏冪礌 II
    static void deleteDuplicatesFromList();

    //15. 涓夋暟涔嬪拰
    static void three_num();

    //17. 鐢佃瘽鍙风爜鐨勫瓧姣嶇粍鍚�
    static void letterCombinations();

    //70. 鐖ゼ姊�
    static void climbStairs();

    //117. 濉厖姣忎釜鑺傜偣鐨勪笅涓�涓彸渚ц妭鐐规寚閽� II
    static void connectRight();

    //1091 浜岃繘鍒剁煩闃典腑鐨勬渶鐭矾寰�
    static void shortestPathBinaryMatrix();

    //130. 琚洿缁曠殑鍖哄煙
    static void solveRound();

    // 78瀛愰泦
    static void subsets();

    //90. 瀛愰泦 II
    static void otherSubSets();

    //39. 缁勫悎鎬诲拰
    static void combinationSum();

    //797. 鎵�鏈夊彲鑳界殑璺緞
    static void allPathsSourceTarget();

    //22. 鎷彿鐢熸垚
    static void generateParenthesisByBrackets();

    // 鎵撳鍔垗2
    static void robOnStreet();


    static void jumpGame();

    //5. 鏈�闀垮洖鏂囧瓙涓�
    static void longestPalindrome();

    // 178 最大数
    static void maxNum();

    //48 鏃嬭浆鍥惧儚
    static void rotateImage();

    //49. 字母异位词分组
    static void groupAnagrams();
private:

    struct ListNode {
        ListNode() : val(0), next{nullptr} {}

        explicit ListNode(int x) : val(x), next(nullptr) {}

        ListNode(int x, ListNode *raw_ptr) : val(x), next(raw_ptr) {}

        ListNode(const ListNode &) = delete;

        ListNode *next;
        int val;


        ~ListNode() {

            for (auto data: node) {
                delete data;
            }
        }

        static std::unique_ptr<ListNode> new_list(size_t length) {
            assert(length != 0);
            auto result = std::make_unique<ListNode>(0);
            result->node.reserve(length - 1);
            auto root = result.get();
            for (size_t i = 1; i < length; i++) {
                root->next = new ListNode(i);
                root = root->next;
                result->node.emplace_back(root);
            }
            return result;
        }

        static std::unique_ptr<ListNode> new_list(const std::vector<int> &data) {
            if (data.empty())return nullptr;
            auto result = std::make_unique<ListNode>(data[0]);
            auto root = result.get();
            result->node.reserve(data.size() - 1);
            size_t size = data.size();
            for (size_t i = 1; i < size; i++) {
                root->next = new ListNode(data[i]);
                root = root->next;
                result->node.emplace_back(root);
            }
            return result;
        }

        std::vector<ListNode *> node = {};
    };


};