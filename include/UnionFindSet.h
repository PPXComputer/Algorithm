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
    int m_count; //连通分量
    std::vector<int> m_father;

    int find_father(int val);

public:


    explicit UnionFindSet(int n);

    int find_head(int val);

    bool connected(int a, int b);

    void merge(int a, int b);

    [[nodiscard]] int count() const;
};


#endif //SSH_UNIONFINDSET_H
