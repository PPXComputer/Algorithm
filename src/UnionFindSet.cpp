//
// Created by 破忆断回 on 2021/9/26.
//

#include "UnionFindSet.h"
#include <algorithm>

using std::vector;

int UnionFindSet::find_father(int val) {
    assert(val < m_father.size());
    int father_val = m_father[val];

    while (m_father[father_val] != father_val) {
        father_val = m_father[father_val];
    }
    m_father[val] = father_val;
    return father_val;
}

int UnionFindSet::find_head(int val) {
    assert(val < m_father.size());
    if (m_father[val] != val)
        return find_father(val);
    else
        return val;
}

UnionFindSet::UnionFindSet(int n) : m_father{vector<int>(n)}, m_count{n} {
    int index = 0;
    std::for_each(m_father.begin(), m_father.end(), [&index](int &a) { a = index++; });
}

bool UnionFindSet::connected(int a, int b) {
    assert(a < m_father.size() && a > 0);
    assert(b < m_father.size() && b > 0);
    return find_head(a) == find_head(b);
}

void UnionFindSet::merge(int a, int b) {
    int father_a = find_father(a);
    int father_b = find_father(b);
    m_father[father_a] = father_b;
    m_father[a] = father_b;
    m_father[b] = father_b;
    this->m_count--;
}

int UnionFindSet::count() const {
    return this->m_count;
}
