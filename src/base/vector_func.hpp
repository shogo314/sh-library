#pragma once
#include <cmath>
#include <numeric>
#include <vector>

#include "traits.hpp"

#define METHOD_EXPAND(func_name)                                             \
    template <typename T, ENABLE_IF_T(has_##func_name##_v<T>)>               \
    inline constexpr auto func_name(const T &t) -> decltype(t.func_name()) { \
        return t.func_name();                                                \
    }

METHOD_EXPAND(sum)
METHOD_EXPAND(product)
METHOD_EXPAND(reversed)

template <typename T, ENABLE_IF_T(not has_reversed_v<T>)>
inline constexpr T reversed(T t) {
    using namespace std;
    reverse(t.begin(), t.end());
    return t;
}

template <typename T>
inline constexpr T sorted(T t) {
    using namespace std;
    sort(t.begin(), t.end());
    return t;
}

#define METHOD_AND_FUNC_ARG_EXPAND(func_name)                                     \
    template <typename T, typename U, ENABLE_IF_T(has_##func_name##_v<T, U>)>     \
    inline constexpr auto func_name(const T &t, const U &u)                       \
        -> decltype(t.func_name(u)) {                                             \
        return t.func_name(u);                                                    \
    }                                                                             \
    template <typename T, typename U, ENABLE_IF_T(not has_##func_name##_v<T, U>)> \
    inline constexpr auto func_name(const T &t, const U &u)                       \
        -> decltype(func_name(t.begin(), t.end(), u)) {                           \
        using namespace std;                                                      \
        return func_name(t.begin(), t.end(), u);                                  \
    }

METHOD_AND_FUNC_ARG_EXPAND(count)
METHOD_AND_FUNC_ARG_EXPAND(find)
METHOD_AND_FUNC_ARG_EXPAND(lower_bound)
METHOD_AND_FUNC_ARG_EXPAND(upper_bound)

template <typename T>
inline T max(const std::vector<T> &v) {
    return *std::max_element(v.begin(), v.end());
}

template <typename T>
inline T min(const std::vector<T> &v) {
    return *std::min_element(v.begin(), v.end());
}

template <class C, ENABLE_IF_T(not has_sum_v<C>)>
inline typename C::value_type sum(const C &v, typename C::value_type init = {}) {
    return std::accumulate(v.begin(), v.end(), init);
}

template <class C, ENABLE_IF_T(not has_product_v<C>)>
inline typename C::value_type product(const C &v, typename C::value_type init = {1}) {
    return std::accumulate(v.begin(), v.end(), init, std::multiplies<T>());
}

template <typename T>
inline T gcd(const std::vector<T> &v, T init = {0}) {
    for (const T &e : v) init = std::gcd(init, e);
    return init;
}

template <typename T>
inline T average(const std::vector<T> &v) {
    assert(not v.empty());
    return sum(v) / v.size();
}

template <typename T>
inline T median(const std::vector<T> &v) {
    assert(not v.empty());
    std::vector<size_t> u(v.size());
    std::iota(u.begin(), u.end(), 0);
    std::sort(u.begin(), u.end(), [&](size_t a, size_t b) {
        return v[a] < v[b];
    });
    if (v.size() & 1) {
        return v[u[v.size() / 2]];
    }
    return (v[u[v.size() / 2]] + v[u[v.size() / 2 - 1]]) / 2;
}

template <typename T, typename U, ENABLE_IF_T(std::is_convertible_v<U, T>)>
inline size_t index(const std::vector<T> &v, const U &x) {
    return std::distance(v.begin(), std::find(v.begin(), v.end(), T(x)));
}

template <typename T, ENABLE_IF_T(std::is_integral_v<T>)>
inline T mex(const std::vector<T> &v) {
    std::vector<bool> b(v.size() + 1);
    for (const auto &a : v) {
        if (0 <= a and a < b.size()) {
            b[a] = true;
        }
    }
    T ret;
    for (size_t i = 0; i < b.size(); i++) {
        if (not b[i]) {
            ret = i;
            break;
        }
    }
    return ret;
}

template <typename T>
inline std::vector<T> &operator++(std::vector<T> &v) {
    for (auto &e : v) e++;
    return v;
}
template <typename T>
inline std::vector<T> operator++(std::vector<T> &v, int) {
    auto res = v;
    for (auto &e : v) e++;
    return res;
}
template <typename T>
inline std::vector<T> &operator--(std::vector<T> &v) {
    for (auto &e : v) e--;
    return v;
}
template <typename T>
inline std::vector<T> operator--(std::vector<T> &v, int) {
    auto res = v;
    for (auto &e : v) e--;
    return res;
}

template <typename T, typename U, ENABLE_IF_T(std::is_convertible_v<U, T>)>
inline std::vector<T> &operator+=(std::vector<T> &v1, const std::vector<U> &v2) {
    if (v2.size() > v1.size()) {
        v1.resize(v2.size());
    }
    for (size_t i = 0; i < v2.size(); i++) {
        v1[i] += v2[i];
    }
    return v1;
}

template <typename T, typename U, ENABLE_IF_T(std::is_convertible_v<U, T>)>
inline std::vector<T> operator+(const std::vector<T> &v1, const std::vector<U> &v2) {
    std::vector<T> res(v1);
    return res += v2;
}

template <typename T, typename U, ENABLE_IF_T(std::is_convertible_v<U, T>)>
inline std::vector<T> &operator+=(std::vector<T> &v, const U &u) {
    for (T &e : v) {
        e += u;
    }
    return v;
}

template <typename T, typename U, ENABLE_IF_T(std::is_convertible_v<U, T>)>
inline std::vector<T> operator+(const std::vector<T> &v, const U &u) {
    std::vector<T> res(v);
    return res += u;
}

template <typename T, typename U, ENABLE_IF_T(std::is_convertible_v<U, T>)>
inline std::vector<T> operator+(const U &u, const std::vector<T> &v) {
    std::vector<T> res(v);
    return res += u;
}

template <typename T, typename U, ENABLE_IF_T(std::is_convertible_v<U, T>)>
inline std::vector<T> &operator*=(std::vector<T> &v1, const std::vector<U> &v2) {
    if (v2.size() > v1.size()) {
        v1.resize(v2.size());
    }
    for (size_t i = 0; i < v2.size(); i++) {
        v1[i] *= v2[i];
    }
    for (size_t i = v2.size(); i < v1.size(); i++) {
        v1[i] *= U(0);
    }
    return v1;
}

template <typename T, typename U, ENABLE_IF_T(std::is_convertible_v<U, T>)>
inline std::vector<T> operator*(const std::vector<T> &v1, const std::vector<U> &v2) {
    std::vector<T> res(v1);
    return res *= v2;
}

template <typename T, typename U, ENABLE_IF_T(std::is_convertible_v<U, T>)>
inline std::vector<T> &operator*=(std::vector<T> &v, const U &u) {
    for (T &e : v) {
        e *= u;
    }
    return v;
}

template <typename T, typename U, ENABLE_IF_T(std::is_convertible_v<U, T>)>
inline std::vector<T> operator*(const std::vector<T> &v, const U &u) {
    std::vector<T> res(v);
    return res *= u;
}

template <typename T, typename U, ENABLE_IF_T(std::is_convertible_v<U, T>)>
inline std::vector<T> operator*(const U &u, const std::vector<T> &v) {
    std::vector<T> res(v);
    return res *= u;
}

template <typename T, typename U>
inline std::vector<T> &assign(std::vector<T> &v1, const std::vector<U> &v2) {
    v1.assign(v2.begin(), v2.end());
    return v1;
}

template <typename T, typename U>
inline std::vector<T> &extend(std::vector<T> &v1, const std::vector<U> &v2) {
    v1.insert(v1.end(), v2.begin(), v2.end());
    return v1;
}

template <typename T, typename U, ENABLE_IF_T(std::is_convertible_v<U, T>)>
inline std::vector<T> &operator|=(std::vector<T> &v1, const std::vector<U> &v2) {
    return extend(v1, v2);
}

template <typename T, typename U, ENABLE_IF_T(std::is_integral_v<U>)>
inline std::vector<T> &operator|=(std::vector<T> &v, const U &u) {
    std::vector<T> w(v);
    v.clear();
    for (int i = 0; i < u; i++) {
        extend(v, w);
    }
    return v;
}

template <typename T, typename U, ENABLE_IF_T(std::is_integral_v<U>)>
inline std::vector<T> operator|(const std::vector<T> &v, const U &u) {
    std::vector<T> res(v);
    return res |= u;
}

template <typename T, typename U, ENABLE_IF_T(std::is_integral_v<U>)>
inline std::vector<T> operator|(const U &u, const std::vector<T> &v) {
    std::vector<T> res(v);
    return res |= u;
}

template <typename T>
inline std::vector<T> abs(const std::vector<T> &v) {
    std::vector<T> ret;
    ret.reserve(v.size());
    for (const T &e : v) ret.push_back(std::abs(e));
    return ret;
}
