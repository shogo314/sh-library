#pragma once
#include <algorithm>
#include <cassert>
#include <functional>
#include <optional>
#include <utility>
#include <vector>

class MergeSortTree {
    using K = int;
    using S = long long;

    struct Element {
        S operator()() const {
            return {};
        }
    };

   public:
    using Compare = std::less<K>;
    using Operator = std::plus<S>;
    using Inverse = std::negate<S>;
    using key_type = K;
    using value_type = S;

    inline constexpr static auto comp = Compare();
    inline constexpr static auto op = Operator();
    inline constexpr static auto inv = Inverse();
    inline constexpr static auto e = Element();

    int n, sz, height;
    std::vector<K> key_data;
    std::vector<S> cumulative_value;

    void initialize(const std::vector<K>& key, const std::vector<S>& value) {
        n = key.size();
        sz = 1;
        height = 1;
        while (sz < n) {
            sz <<= 1;
            height++;
        }
        key_data.assign(sz * height, {});
        std::vector<S> value_data(sz * height, e());
        cumulative_value.assign(sz * height, {});
        for (int i = 0; i < n; i++) {
            key_data[(height - 1) * sz + i] = key[i];
            value_data[(height - 1) * sz + i] = value[i];
            cumulative_value[(height - 1) * sz + i] = value[i];
        }
        int t = 1;
        for (int h = height - 1; h > 0; h--) {
            for (int i = 0; i < n; i += t * 2) {
                int j1 = h * sz + i;
                int j2 = h * sz + std::min(n, i + t);
                int j0 = (h - 1) * sz + i;
                int last1 = h * sz + std::min(n, i + t);
                int last2 = h * sz + std::min(n, i + t * 2);
                while (j1 != last1 or j2 != last2) {
                    if (j1 == last1) {
                        key_data[j0] = key_data[j2];
                        value_data[j0] = value_data[j2];
                        j0++;
                        j2++;
                    } else if (j2 == last2) {
                        key_data[j0] = key_data[j1];
                        value_data[j0] = value_data[j1];
                        j0++;
                        j1++;
                    } else if (comp(key_data[j2], key_data[j1])) {
                        key_data[j0] = key_data[j2];
                        value_data[j0] = value_data[j2];
                        j0++;
                        j2++;
                    } else {
                        key_data[j0] = key_data[j1];
                        value_data[j0] = value_data[j1];
                        j0++;
                        j1++;
                    }
                }

                if (i < n) {
                    cumulative_value[(h - 1) * sz + i] = value_data[(h - 1) * sz + i];
                }
                for (int j = i + 1; j < std::min(n, i + t * 2); j++) {
                    cumulative_value[(h - 1) * sz + j] = op(cumulative_value[(h - 1) * sz + j - 1], value_data[(h - 1) * sz + j]);
                }
            }
            t <<= 1;
        }
    }

    S _prod_section(int l, int r, std::optional<K> a, std::optional<K> b) const {
        S ret = e();
        if (a.has_value()) {
            int i = std::lower_bound(key_data.begin() + l, key_data.begin() + r, a.value()) - key_data.begin();
            if (i != l) {
                ret = inv(cumulative_value[i - 1]);
            }
        }
        if (b.has_value()) {
            int i = std::lower_bound(key_data.begin() + l, key_data.begin() + r, b.value()) - key_data.begin();
            if (i != l) {
                ret = op(ret, cumulative_value[i - 1]);
            }
        } else {
            ret = op(ret, cumulative_value[r - 1]);
        }
        return ret;
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
        if (l.has_value() and r.has_value() and l >= r) return e();
        return _prod(l.value_or(0), r.value_or(n), a, b);
    }

    // std::vector<std::pair<K, S>> to_vector() const {
    //     std::vector<std::pair<K, S>> ret;
    //     ret.reserve(n);
    //     for (int i = 0; i < n; i++) {
    //         ret.push_back(key_value_data[(height - 1) * sz + i]);
    //     }
    //     return ret;
    // }
};
