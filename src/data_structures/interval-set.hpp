#pragma once
#include <cassert>
#include <functional>
#include <iterator>
#include <limits>
#include <set>
#include <stack>
#include <type_traits>
template <typename T = long long, std::enable_if_t<std::is_scalar_v<T>>* = nullptr>
class IntervalSet {
   public:
    using value_type = T;
    inline constexpr static T max = std::numeric_limits<T>::max();
    inline constexpr static T min = std::numeric_limits<T>::min();

    std::set<std::pair<T, T>> data;
    IntervalSet() = default;
    void add(T l, T r) {
        assert(l < r);
        if (data.empty()) {
            data.emplace(l, r);
            return;
        }
        auto itr_l = data.upper_bound({l, max});
        if (itr_l == data.begin()) {
        } else {
            if (std::prev(itr_l)->second < l) {
            } else {
                --itr_l;
            }
        }
        if (itr_l == data.end() or r < itr_l->first) {
            data.emplace(l, r);
            return;
        }
        if (itr_l->first < l) l = itr_l->first;
        auto itr_r = data.upper_bound({r, r});
        if (itr_r == data.end()) --itr_r;
        if (r < itr_r->second) r = itr_r->second;
        data.erase(itr_l, ++itr_r);
        data.emplace(l, r);
    };
    void remove(T l, T r) {
        assert(l < r);
        auto itr_l = data.upper_bound({l, max});
        if (itr_l == data.begin()) {
        } else {
            if (std::prev(itr_l)->second < l) {
            } else {
                --itr_l;
            }
        }
        if (itr_l == data.end() or r < itr_l->first) {
            return;
        }
        std::stack<std::pair<T, T>> tmp;
        if (itr_l->first < l) tmp.push({itr_l->first, l});
        auto itr_r = data.upper_bound({r, r});
        if (itr_r == data.end()) --itr_r;
        if (r < itr_r->second) tmp.push({r, itr_r->second});
        data.erase(itr_l, ++itr_r);
        while (not tmp.empty()) {
            data.insert(tmp.top());
            tmp.pop();
        }
    }
};
