//
// Created by 破忆断回 on 2021/9/26.
//

#ifndef SSH_UNIONFINDSET_H
#define SSH_UNIONFINDSET_H

#include <vector>
#include <unordered_map>
#include <cassert>


class UnionFindSet {

private:
    std::vector<int> container = {};
    std::vector<int> father = {};
    std::vector<int> counter_size = {};
public:


    explicit UnionFindSet(std::vector<int> data);

    int find_father(int val);

    int find_head(int val);

};


#endif //SSH_UNIONFINDSET_H
