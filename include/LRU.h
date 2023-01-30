#pragma once
#include <dbg.h>
#include <unordered_map>
#include <cassert>
class LRUCache
{

    struct DoubleListNode
    {
        DoubleListNode() = default;
        ~DoubleListNode() = default;
        DoubleListNode(DoubleListNode *prev, DoubleListNode *next, int val) : prev{prev}, next{next}, val{val} {}
        DoubleListNode *prev;
        DoubleListNode *next;
        int val;
    };
    class DoubleList
    {
        DoubleListNode *m_root;
        DoubleListNode *m_tail;
        int m_size;

    public:
        DoubleList(int capacity) : m_root{new DoubleListNode()}, m_tail{m_root}, m_size{0} {}
        DoubleList(const DoubleList &) = delete;
        DoubleList(const DoubleList &&) = delete;
        ~DoubleList()
        {
            DoubleListNode *tmp = nullptr;
            while (m_root != nullptr)
            {
                tmp = this->m_root;
                this->m_root = this->m_root->next;
                dbg("delete tmp", tmp->val);
                delete tmp;
            }
        }

        DoubleListNode *add_to_front(int val)
        {
            DoubleListNode *curNode{};
            if (this->m_size == 0)
            {
                curNode = new DoubleListNode{this->m_root, nullptr, val};
                this->m_tail = curNode;
                this->m_root->next = curNode;
            }
            else
            {
                curNode = new DoubleListNode{this->m_root, this->m_root->next, val};
                this->m_root->next->prev = curNode;
                this->m_root->next = curNode;
            }

            ++this->m_size;
            return curNode;
        }

        void move_to_front(DoubleListNode *curNode)
        {
            if (this->m_size == 1)
            {
                return;
            }
            if (this->m_tail == curNode)
            {
                auto curNodePrev = curNode->prev;
                this->m_tail = curNodePrev;
                curNodePrev->next = nullptr;
            }
            else
            {
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
        int get_size()
        {
            return this->m_size;
        }
        const int get_size() const
        {
            return this->m_size;
        }
        DoubleListNode *get_tail()
        {
            return this->m_tail;
        }
        const DoubleListNode *get_tail() const
        {
            return this->m_tail;
        }
    };

public:
    explicit LRUCache(int capacity) : m_double_list{capacity}, m_map(capacity), m_capcaity(capacity)
    {
    }
    LRUCache(const LRUCache &) = delete;
    LRUCache(const LRUCache &&) = delete;
    ~LRUCache() = default;
    int get(int key)
    {
        auto findIter = this->m_map.find(key);
        if (findIter != this->m_map.end())
        {
            this->m_double_list.move_to_front(findIter->second);
            return findIter->second->val;
        }
        return -1;
    }

    void put(int key, int value)
    {
        auto findIter = this->m_map.find(key);
        if (findIter != this->m_map.end())
        {
            this->m_double_list.move_to_front(findIter->second);
            findIter->second->val = value;
        }
        else
        {
            // 添加新的元素
            int listSize = this->m_double_list.get_size();
            if (listSize == this->m_capcaity)
            {
                this->m_map.erase(this->m_double_list.get_tail()->val);
                this->m_double_list.delete_tail();
            }
            auto curNode = this->m_double_list.add_to_front(value);
            this->m_map.insert({key, curNode});
        }
    }

private:
    std::unordered_map<int, DoubleListNode *> m_map;
    DoubleList m_double_list;
    int m_capcaity;
};
