#pragma once

#include <cassert>
#include <vector>

class MergeSortTree {
    using S = long long;
    using K = int;
    S op(const S& a, const S& b) {
        return a + b;
    }
    S e() {
        return 0;
    }
    int n, sz, height;
    std::vector<S> value_data;
    std::vector<K> key_data;
    void update(int k) {
        int h;
    }

   public:
    MergeSortTree() = default;
    MergeSortTree(const std::vector<S>& v, const std::vector<S>& k) {
        assert(v.size() == k.size());
        n = v.size();
    }
};
