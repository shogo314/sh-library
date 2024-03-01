#pragma once

#include <algorithm>
#include <cassert>
#include <iostream>
#include <optional>
#include <tuple>
#include <utility>
#include <vector>

class MergeSortTree {
    using S = long long;
    using K = int;
    static S op(const S& a, const S& b) {
        return a + b;
    }
    static S e() {
        return 0;
    }
    int n, sz, height;
    std::vector<std::tuple<K, S, int>> key_value_index_data;

    void initialize(const std::vector<K>& key, const std::vector<S>& value) {
        n = key.size();
        sz = 1;
        height = 1;
        while (sz < n) {
            sz <<= 1;
            height++;
        }
        key_value_index_data.assign(sz * height, {K{}, e(), 0});
        for (int i = 0; i < n; i++) {
            key_value_index_data[i + sz * (height - 1)] = {key[i], value[i], i};
        }
        int t = 1;
        for (int h = height - 1; h > 0; h--) {
            for (int i = 0; i < n; i += t * 2) {
                std::merge(key_value_index_data.begin() + h * sz + i,
                           key_value_index_data.begin() + h * sz + std::min(n, i + t),
                           key_value_index_data.begin() + h * sz + std::min(n, i + t),
                           key_value_index_data.begin() + h * sz + std::min(n, i + t * 2),
                           key_value_index_data.begin() + (h - 1) * sz + i,
                           [](const std::tuple<K, S, int>& p1, const std::tuple<K, S, int>& p2) { return std::get<0>(p1) < std::get<0>(p2); });
            }
            t <<= 1;
        }
    }

    S _prod_section(int l, int r, std::optional<K> a, std::optional<K> b) const {
        std::cerr << "l = " << l << ", r = " << r << std::endl;

        return 0;
    }
    S _prod(int l, int r, std::optional<K> a, std::optional<K> b) const {
        S ret = e();
        int h = height - 1;
        int t = 1;
        while (l < r) {
            if (l & t) {
                ret += _prod_section(h * sz + l, h * sz + l + t, a, b);
                l += t;
            }
            if (r & t) {
                r -= t;
                ret += _prod_section(h * sz + r, h * sz + r + t, a, b);
            }
            h--;
            t <<= 1;
        }
        return ret;
    }

   public:
    MergeSortTree() = default;
    explicit MergeSortTree(const std::vector<std::pair<K, S>>& key_value) {
        std::vector<K> key;
        std::vector<S> value;
        key.reserve(key_value.size());
        value.reserve(key_value.size());
        for (size_t i = 0; i < key_value.size(); i++) {
            key.push_back(key_value[i].first);
            value.push_back(key_value[i].second);
        }
        this->initialize(key, value);
    }
    /**
     * key ソートする基準
     * value prodで計算する対象
     */
    MergeSortTree(const std::vector<K>& key, const std::vector<S>& value) {
        assert(key.size() == value.size());
        this->initialize(key, value);
    }

    /**
     * ploduct value[i] s.t. a <= key[i] < b , i in [l, r)
     */
    S prod(std::optional<int> l = std::nullopt, std::optional<int> r = std::nullopt, std::optional<K> a = std::nullopt, std::optional<K> b = std::nullopt) const {
        if (a.has_value() and b.has_value() and not(a.value() < b.value())) return e();
        if (l >= r) return e();
        return _prod(l.value_or(0), r.value_or(n), a, b);
    }

    /**
     * @brief 内容を出力する
     *
     * @tparam CharT 出力ストリームの文字型
     * @tparam Traits 出力ストリームの文字型特性
     * @param os 出力ストリーム
     * @param mst マージソートツリー
     * @return std::basic_ostream<CharT, Traits>& 出力ストリーム
     */
    template <class CharT, class Traits>
    friend std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, const MergeSortTree& mst) {
        for (int i = 0; i < mst.n; i++) {
            if (i != 0) os << CharT(' ');
            os << std::get<1>(mst.key_value_index_data[mst.sz * (mst.height - 1) + i]);
        }
        return os;
    }
};
