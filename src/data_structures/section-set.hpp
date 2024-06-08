#pragma once
#include <cassert>
#include <functional>
#include <iterator>
#include <limits>
#include <set>
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
        
    };
    void remove(T l, T r) {
        assert(l < r);
    }
};
