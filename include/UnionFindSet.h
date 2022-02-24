//
// Created by 破忆断回 on 2021/9/26.
//

#ifndef SSH_UNIONFINDSET_H
#define SSH_UNIONFINDSET_H

#include <vector>
#include <unordered_map>
#include <cassert>
using std::unordered_map;
using std::vector;
using std::addressof;

class UnionFindSet {

private:
    vector<int> container = {};
    vector<int> father = {};
    vector<int> counter_size = {};
public:


    explicit UnionFindSet(vector<int> data);

    int find_father(int val);

    int find_head(int val);

};


#endif //SSH_UNIONFINDSET_H
