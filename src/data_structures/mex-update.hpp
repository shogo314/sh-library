#pragma once
#include <cassert>
#include <iostream>
#include <limits>
#include <map>
#include <set>
#include <vector>

template <typename T>
struct MexUpdate {
    using value_type = T;

   private:
    using inner_value_type = int;

    inline constexpr static value_type e = std::numeric_limits<value_type>::max();

    inner_value_type n;
    std::vector<value_type> v;
    std::set<inner_value_type> s;
    std::map<inner_value_type, size_t> m;

   public:
    MexUpdate() = default;
    MexUpdate(int n) : n(n), v(n, e) {
        assert(n > 0);
        assert(n + 1 < e);
        std::set<inner_value_type>::iterator hint = s.end();
        for (inner_value_type i = n; i >= 0; --i) {
            hint = s.emplace_hint(hint, i);
        }
    }
    MexUpdate(const std::vector<value_type>& init) : n(init.size()), v(init) {
        assert(n > 0);
        assert(n + 1 < e);
        std::set<inner_value_type>::iterator hint = s.end();
        for (inner_value_type i = n; i >= 0; --i) {
            s.insert(i);
        }
        for (const auto& i : init) {
            if (0 <= i and i <= n) {
                m[i]++;
                s.erase(i);
            }
        }
    }
    void set(int k, const value_type& x) {
        assert(0 <= k and k < n);
        if (0 <= v[k] and v[k] <= n) {
            inner_value_type v_k = v[k];
            auto itr = m.find(v_k);
            if (itr->second > 1) {
                itr->second--;
            } else {
                m.erase(itr);
                s.insert(v_k);
            }
        }
        if (0 <= x and x <= n) {
            inner_value_type xx = x;
            auto itr = m.find(xx);
            if (itr == m.end()) {
                m[xx]++;
                s.erase(xx);
            } else {
                itr->second++;
            }
        }
        v[k] = x;
    }
    value_type prod() const {
        return *s.begin();
    }
};
