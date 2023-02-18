
#include <cassert>
#include <dbg.h>
#include <list>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
class LRUCache {

    struct DoubleListNode {
        DoubleListNode() = default;
        ~DoubleListNode() = default;
        DoubleListNode(DoubleListNode* prev, DoubleListNode* next, int val)
            : prev { prev }
            , next { next }
            , val { val }
        {
        }
        DoubleListNode* prev;
        DoubleListNode* next;
        int val;
    };
    class DoubleList {
        DoubleListNode* m_root;
        DoubleListNode* m_tail;
        int m_size;

    public:
        DoubleList()
            : m_root { new DoubleListNode() }
            , m_tail { m_root }
            , m_size { 0 }
        {
        }
        DoubleList(const DoubleList&) = delete;
        DoubleList(const DoubleList&&) = delete;
        ~DoubleList()
        {
            DoubleListNode* tmp = nullptr;
            while (m_root != nullptr) {
                tmp = this->m_root;
                this->m_root = this->m_root->next;
                dbg("delete tmp", tmp->val);
                delete tmp;
            }
        }

        DoubleListNode* add_to_front(int val)
        {
            DoubleListNode* curNode {};
            if (this->m_size == 0) {
                curNode = new DoubleListNode { this->m_root, nullptr, val };
                this->m_tail = curNode;
                this->m_root->next = curNode;
            } else {
                curNode = new DoubleListNode { this->m_root, this->m_root->next, val };
                this->m_root->next->prev = curNode;
                this->m_root->next = curNode;
            }

            ++this->m_size;
            return curNode;
        }

        void move_to_front(DoubleListNode* curNode)
        {
            if (this->m_size == 1) {
                return;
            }
            if (this->m_tail == curNode) {
                auto curNodePrev = curNode->prev;
                this->m_tail = curNodePrev;
                curNodePrev->next = nullptr;
            } else {
                auto curNodePrev = curNode->prev;
                curNodePrev->next = curNode->next;
                curNode->next->prev = curNodePrev;
            }
            curNode->prev = this->m_root;
            curNode->next = this->m_root->next;
            this->m_root->next->prev = curNode;
            this->m_root->next = curNode;
        }

        void delete_tail()
        {
            assert(this->m_size != 0);
            auto curNode = this->m_tail->prev;
            curNode->next = nullptr;
            dbg("delete tail", this->m_tail->val);
            delete this->m_tail;
            this->m_tail = curNode;
            --this->m_size;
        }
        int get_size() { return this->m_size; }
        const int get_size() const { return this->m_size; }
        DoubleListNode* get_tail() { return this->m_tail; }
        const DoubleListNode* get_tail() const { return this->m_tail; }
    };

public:
    explicit LRUCache(int capacity)
        : m_double_list {}
        , m_map(capacity)
        , m_capcaity(capacity)
    {
    }
    LRUCache(const LRUCache&) = delete;
    LRUCache(const LRUCache&&) = delete;
    ~LRUCache() = default;
    int get(int key)
    {
        auto findIter = this->m_map.find(key);
        if (findIter != this->m_map.end()) {
            this->m_double_list.move_to_front(findIter->second);
            return findIter->second->val;
        }
        return -1;
    }

    void put(int key, int value)
    {
        auto findIter = this->m_map.find(key);
        if (findIter != this->m_map.end()) {
            this->m_double_list.move_to_front(findIter->second);
            findIter->second->val = value;
        } else {
            // 添加新的元素
            int listSize = this->m_double_list.get_size();
            if (listSize == this->m_capcaity) {
                this->m_map.erase(this->m_double_list.get_tail()->val);
                this->m_double_list.delete_tail();
            }
            auto curNode = this->m_double_list.add_to_front(value);
            this->m_map.insert({ key, curNode });
        }
    }

private:
    std::unordered_map<int, DoubleListNode*> m_map;
    DoubleList m_double_list;
    int m_capcaity;
};

class OtherLRUCache {
public:
    explicit OtherLRUCache(int capcaity)
        : m_capcaity(capcaity)
        , m_map(capcaity)
        , m_double_list()
    {
    }

    int get(int key)
    {

        auto findIter = this->m_map.find(key);
        if (findIter != this->m_map.end()) {
            int val = findIter->second->second;
            this->m_double_list.splice(this->m_double_list.begin(), this->m_double_list, findIter->second);
            return val;
        }
        return -1;
    }

    void put(int key, int value)
    {
        auto findIter = this->m_map.find(key);
        if (findIter != this->m_map.end()) {
            findIter->second->second = value;
            m_double_list.splice(m_double_list.begin(), m_double_list, findIter->second);
        } else {
            if (m_double_list.size() == m_capcaity) {
                m_map.erase(m_double_list.back().first);
                m_double_list.pop_back();
            }
            m_double_list.push_front(std::make_pair(key, value));
            m_map.insert_or_assign(key, m_double_list.begin());
        }
    }

private:
    std::unordered_map<int, std::list<std::pair<int, int>>::iterator> m_map;
    std::list<std::pair<int, int>> m_double_list;
    int m_capcaity;
};

class Twitter {
public:
    Twitter() = default;

    void postTweet(int userId, int tweetId)
    {
        m_posts.emplace_back(userId, tweetId);
    }

    std::vector<int> getNewsFeed(int userId)
    {
        int count = 0;
        res.clear();
        for (int i = m_posts.size() - 1; i >= 0 && count != 10; --i) {
            int beforeUserId = m_posts[i].first;
            int tweetId = m_posts[i].second;
            if ((beforeUserId != userId) || (m_userLink[userId].find(beforeUserId) != m_userLink[userId].end())) {
                res.emplace_back(tweetId);
                ++count;
            }
        }
        return res;
    }

    void follow(int followerId, int followeeId)
    {
        m_userLink[followerId].insert(followeeId);
    }

    void unfollow(int followerId, int followeeId)
    {
        m_userLink[followerId].erase(followeeId);
    }
    std::unordered_map<int, std::unordered_set<int>> m_userLink = std::unordered_map<int, std::unordered_set<int>>(20);
    std::vector<std::pair<int, int>> m_posts;
    std::vector<int> res = std::vector<int>(10);
};
/**
 * Your Twitter object will be instantiated and called as such:
 * Twitter* obj = new Twitter();
 * obj->postTweet(userId,tweetId);
 * vector<int> param_2 = obj->getNewsFeed(userId);
 * obj->follow(followerId,followeeId);
 * obj->unfollow(followerId,followeeId);
 */