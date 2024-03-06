#pragma once
#include <array>
#include <iostream>
#include <set>
#include <tuple>
#include <utility>
#include <vector>

namespace tuple_io {
template <typename Tuple, size_t I, typename CharT, typename Traits>
std::basic_istream<CharT, Traits>& read_tuple(std::basic_istream<CharT, Traits>& is, Tuple& t) {
    is >> std::get<I>(t);
    if constexpr (I + 1 < std::tuple_size_v<Tuple>) {
        return read_tuple<Tuple, I + 1>(is, t);
    }
    return is;
}
template <typename Tuple, size_t I, typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>& write_tuple(std::basic_ostream<CharT, Traits>& os, const Tuple& t) {
    os << std::get<I>(t);
    if constexpr (I + 1 < std::tuple_size_v<Tuple>) {
        os << CharT(' ');
        return write_tuple<Tuple, I + 1>(os, t);
    }
    return os;
}
};  // namespace tuple_io

template <typename T1, typename T2, typename CharT, typename Traits>
std::basic_istream<CharT, Traits>& operator>>(std::basic_istream<CharT, Traits>& is, std::pair<T1, T2>& p) {
    is >> p.first >> p.second;
    return is;
}
template <typename... Types, typename CharT, typename Traits>
std::basic_istream<CharT, Traits>& operator>>(std::basic_istream<CharT, Traits>& is, std::tuple<Types...>& p) {
    return tuple_io::read_tuple<std::tuple<Types...>, 0>(is, p);
}
template <typename T, size_t N, typename CharT, typename Traits>
std::basic_istream<CharT, Traits>& operator>>(std::basic_istream<CharT, Traits>& is, std::array<T, N>& a) {
    for (auto& e : a) is >> e;
    return is;
}
template <typename T, typename CharT, typename Traits>
std::basic_istream<CharT, Traits>& operator>>(std::basic_istream<CharT, Traits>& is, std::vector<T>& v) {
    for (auto& e : v) is >> e;
    return is;
}

template <typename T1, typename T2, typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, const std::pair<T1, T2>& p) {
    os << p.first << CharT(' ') << p.second;
    return os;
}
template <typename... Types, typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, const std::tuple<Types...>& p) {
    return tuple_io::write_tuple<std::tuple<Types...>, 0>(os, p);
}
template <typename T, size_t N, typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, const std::array<T, N>& a) {
    for (size_t i = 0; i < N; ++i) {
        if (i) os << CharT(' ');
        os << a[i];
    }
    return os;
}
template <typename T, typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, const std::vector<T>& v) {
    for (size_t i = 0; i < v.size(); ++i) {
        if (i) os << CharT(' ');
        os << v[i];
    }
    return os;
}
template <typename T, typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, const std::set<T>& s) {
    for (auto itr = s.begin(); itr != s.end(); ++itr) {
        if (itr != s.begin()) os << CharT(' ');
        os << *itr;
    }
    return os;
}

/**
 * @brief 空行出力
 */
void print() { std::cout << '\n'; }
/**
 * @brief 出力して改行
 *
 * @tparam T 型
 * @param x 出力する値
 */
template <typename T>
void print(const T& x) { std::cout << x << '\n'; }
/**
 * @brief 空白区切りで出力して改行
 *
 * @tparam T 1つ目の要素の型
 * @tparam Tail 2つ目以降の要素の型
 * @param x 1つ目の要素
 * @param tail 2つ目以降の要素
 */
template <typename T, typename... Tail>
void print(const T& x, const Tail&... tail) {
    std::cout << x << ' ';
    print(tail...);
}

/**
 * @brief 空行出力
 */
void err() { std::cerr << std::endl; }
/**
 * @brief 出力して改行
 *
 * @tparam T 型
 * @param x 出力する値
 */
template <typename T>
void err(const T& x) { std::cerr << x << std::endl; }
/**
 * @brief 空白区切りで出力して改行
 *
 * @tparam T 1つ目の要素の型
 * @tparam Tail 2つ目以降の要素の型
 * @param x 1つ目の要素
 * @param tail 2つ目以降の要素
 */
template <typename T, typename... Tail>
void err(const T& x, const Tail&... tail) {
    std::cerr << x << ' ';
    err(tail...);
}
