#pragma once

#include <list>
#include <unordered_map>
#include <utility>
class LFUCache
{

    struct kv
    {

        int key;
        int value;
        kv(int key_, int value_) : value{value_}, key{key_} {}
    };
    using listOfKV = std::list<kv>;
    struct freqWithListIter
    {
        unsigned int freq;
        listOfKV::iterator iter{};
    };

    // key: frequency, value: list of original key-value pairs that have the same frequency.
    std::unordered_map<int, listOfKV> freq2listOfKV;
    // key: original key,
    // value: pair of frequency and the iterator corresponding key int the
    // frequencies map's list.
    std::unordered_map<int, freqWithListIter> key2freqWithListIter;
    unsigned int capacity;
    unsigned int minf;

    LFUCache(unsigned int capacity_) : capacity{capacity_}, freq2listOfKV(capacity_), key2freqWithListIter(capacity_), minf(0) {}

    void insert(unsigned int newFreq, int key, int value)
    {
        freq2listOfKV[newFreq].emplace_front(key, value);
        key2freqWithListIter[key] = freqWithListIter{newFreq, freq2listOfKV[newFreq].begin()};
    }

    int get(int key)
    {
        auto iter = key2freqWithListIter.find(key);
        if (iter == key2freqWithListIter.end())
        {
            return -1;
        }

        const auto freq = iter->second.freq;
        const auto listIter = iter->second.iter;
        const auto value = listIter->value;
        freq2listOfKV[freq].erase(listIter);
        if (freq2listOfKV[freq].empty() && minf == freq)
        {
            ++minf;
        }
        insert(freq + 1, key, value);
        return value;
    }
    void set(int key, int value)
    {
        if (capacity <= 0)
        {
            return;
        }
        auto iter = key2freqWithListIter.find(key);
        if (iter != key2freqWithListIter.end())
        {
            iter->second.iter->value = value;
            get(key);
            return;
        }

        if (capacity == key2freqWithListIter.size())
        {
            // 移除最小的
            auto deleteKey = freq2listOfKV[minf].back().key; //删除同一频率最前面的元素
            key2freqWithListIter.erase(deleteKey);
            freq2listOfKV[minf].pop_back();
        }
        minf = 1;
        insert(minf, key, value);
    }
};