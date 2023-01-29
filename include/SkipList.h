//
// Created by ppx on 2021/11/8.
//

#ifndef SKIPLIST_H
#define SKIPLIST_H


#include <array>
#include <folly/FBVector.h>
#include <memory>
#include <random>

class SkipList {
public:
    struct SkipNode {
        using Ptr = std::unique_ptr<SkipNode>;
        using SharedPtr = std::shared_ptr<SkipNode>;
        using HeadVector = folly::fbvector<SkipNode::SharedPtr>;
        int data = 0;
        Ptr next = nullptr;
        folly::fbvector<SkipNode *> layer{};

        SkipNode(int value, int height) {
            this->data = value;
            this->next = nullptr;
            layer = folly::fbvector<SkipNode *>(height, nullptr);
        }

        SkipNode(const SkipNode &) = delete;

        SkipNode &operator=(const SkipNode &) = delete;

        ~SkipNode() = default;
    };


    static folly::fbvector<SkipNode::SharedPtr> create_normal() {
        constexpr std::array<int, 6> raw_data = {1, 3, 5, 6, 13, 14};
        auto headPtr = std::make_shared<SkipNode>(raw_data.front(), 0);
        constexpr unsigned __int64 size = raw_data.size();
        for (int i = 1; i < size; ++i) {
            headPtr->next = std::make_unique<SkipNode>(raw_data[i], 0);
        }
        folly::fbvector<SkipNode::SharedPtr> container{headPtr};
        return container;
    }

    int search_below(SkipNode *pNode, int cur_layer, int target) {
        return 0;
    }

    int search_data(const SkipNode::HeadVector &root, int target) {
        assert(! root.empty());
        SkipNode *curPtr = root.back().get();
        while (curPtr && curPtr->data < target) {
            curPtr = curPtr->next.get();
        }
        if (curPtr) {
            int curLayer = static_cast<int>(root.size()) - 1;
            return search_below(curPtr, curLayer, target);
        }
        return -1;
    }
};


class RawSkipList {
    struct Node {
        folly::fbvector<Node *> nextArray;
        int value = 0;

        explicit Node(int data) : nextArray{}, value{data} {}
    };

    using HeadNode = folly::fbvector<RawSkipList::Node *>;
public:
    HeadNode create_normal() {

        HeadNode head;
        auto values = {1, 3, 4, 6, 13, 16};
        Node *front = new Node(*values.begin());
        head.push_back(front);
        size_t size = values.size();
        std::uniform_int_distribution<int> d(0, 3);

        std::random_device rd1;
        bool levelUp = false;
        for (int i = 1; i < size; ++i) {
            front->nextArray.emplace_back(new Node(*(values.begin() + i)));
            // 1/4 提升层次
            if (d(rd1) == 0) {
                Node *&cur = front->nextArray.back();
                cur->nextArray.resize(cur->nextArray.size() + 1);
                levelUp = true;
            }
            front = front->nextArray.back();
        }

        // 将有所提升的层 串联起来
        if (levelUp) {
            Node *lastLayer = head.back();

            unsigned __int64 lastHeight = head.size();
            Node *firstLeveUpNode = nullptr;
            while (lastLayer) {
                if (std::size(lastLayer->nextArray) > lastHeight) {
                    firstLeveUpNode = lastLayer;
                    break;
                }
            }
            head.push_back(firstLeveUpNode);
            while (lastLayer->nextArray.back()) {
                if (std::size(lastLayer->nextArray) > lastHeight) {
                    firstLeveUpNode = lastLayer;
                    break;
                }

            }
        }
        return head;
    }


};

class Trie {
    struct TrieNode{
        TrieNode * next [26] {};
        bool isEnd=false;
    };
    TrieNode root{} ;
public:
    Trie()=default;

   inline void insert(const std::string& word) {
        // 将当前的数据转换到线上
        auto p =&root;
        int size =word.size();
        for(int i =0;i<size ;++i){
            int index =word[i]-'a';
            if(p->next[index]==nullptr){
                p->next [index]= new TrieNode{};
            }
            p= p->next [index];
        }
        p->isEnd=true;
    }

   inline bool search(const std::string& word) {
        int size =word.size();
        auto p =&root;
        for(int i =0;i<size ;++i){
             int index =word[i]-'a';
            if(p->next[index]==nullptr){
                return false;
            }
             p= p->next [index];
        }
        if(p!=nullptr && p->isEnd)return true;
        return false;
    }

   inline bool startsWith(const std::string& word) {
        int size =word.size();
        auto p =&root;
        for(int i =0;i<size ;++i){
             int index =word[i]-'a';
            if(p->next[index]==nullptr){
                return false;
            }
             p= p->next [index];
        }
        return true;
    }
};


#endif // SKIPLIST_H
