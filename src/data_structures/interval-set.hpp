#pragma once
#include <cassert>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <optional>
#include <set>
#include <type_traits>
#include <vector>
/**
 * @brief 半開区間を管理する
 *
 * @tparam T スカラー
 */
template <typename T = long long, std::enable_if_t<std::is_scalar_v<T>>* = nullptr>
class IntervalSet {
   public:
    using key_type = T;
    using value_type = std::pair<key_type, key_type>;
    inline constexpr static key_type max = std::numeric_limits<key_type>::max();
    inline constexpr static key_type min = std::numeric_limits<key_type>::min();

   private:
    std::set<value_type> data;
    using iterator = typename std::set<value_type>::iterator;
    std::optional<std::pair<iterator, iterator>> find(key_type l, key_type r) {
        auto itr_l = data.upper_bound({l, max});
        if (itr_l == data.begin()) {
        } else {
            if (std::prev(itr_l)->second < l) {
            } else {
                --itr_l;
            }
        }
        if (itr_l == data.end() or r < itr_l->first) {
            return {};
        }
        if (itr_l->first < l) l = itr_l->first;
        auto itr_r = data.upper_bound({r, max});
        return std::pair<iterator, iterator>{itr_l, itr_r};
    }

   public:
    IntervalSet() = default;
    std::optional<value_type> find(key_type k) const {
        auto itr = data.upper_bound({k, max});
        if (itr == data.begin()) return {};
        --itr;
        if (k < itr->second) {
            return *itr;
        }
        return {};
    }
    void insert(key_type l, key_type r) {
        assert(l < r);
        auto opt = find(l, r);
        if (not opt.has_value()) {
            data.emplace(l, r);
            return;
        }
        auto [itr_l, itr_r] = opt.value();
        if (itr_l->first < l) l = itr_l->first;
        if (r < std::prev(itr_r)->second) r = std::prev(itr_r)->second;
        data.erase(itr_l, itr_r);
        data.emplace(l, r);
    };
    void erase(key_type l, key_type r) {
        assert(l < r);
        auto opt = find(l, r);
        if (not opt.has_value()) {
            return;
        }
        auto [itr_l, itr_r] = opt.value();
        std::vector<value_type> tmp;
        if (itr_l->first < l) tmp.push_back({itr_l->first, l});
        if (r < std::prev(itr_r)->second) tmp.push_back({r, std::prev(itr_r)->second});
        data.erase(itr_l, itr_r);
        while (not tmp.empty()) {
            data.insert(tmp.back());
            tmp.pop_back();
        }
    }
    std::vector<value_type> to_vector() const {
        return std::vector<value_type>(data.begin(), data.end());
    }
};
