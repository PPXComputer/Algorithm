//
// Created by 破忆断回 on 2021/9/26.
//

#include "UnionFindSet.h"

int UnionFindSet::find_father(int val) {
    assert(val < father.size());
    int father_val = father[val];
    int result = father_val;

    if (bool father_not_root = father[father_val] != father_val;father_not_root) {
        do {
            father_val = father[father_val];
        } while (father[father_val] != father_val);
        father[val] = father_val;
    }
    return result;
}

int UnionFindSet::find_head(int val) {
    assert(val < father.size());
    if (father[val] == val) {
        return val;
    }
    return find_head(father[val]);
}

UnionFindSet::UnionFindSet(vector<int> data) {
    container = std::move(data);
    father = container;
    counter_size = std::vector<int>(container.size(), 1);
}
