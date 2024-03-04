#pragma once
#include <array>
#include <initializer_list>
#include <map>
#include <set>
#include <string_view>
#include <type_traits>
#include <vector>

template <typename Tp, typename Nm = long long, std::enable_if_t<std::is_integral_v<Nm>, std::nullptr_t> = nullptr>
struct Counter : private std::map<Tp, Nm> {
    using std::map<Tp, Nm>::map;
    using std::map<Tp, Nm>::operator=;

    using std::map<Tp, Nm>::begin;
    using std::map<Tp, Nm>::cbegin;
    using std::map<Tp, Nm>::end;
    using std::map<Tp, Nm>::cend;
    using std::map<Tp, Nm>::rbegin;
    using std::map<Tp, Nm>::crbegin;
    using std::map<Tp, Nm>::rend;
    using std::map<Tp, Nm>::crend;

    using std::map<Tp, Nm>::empty;
    using std::map<Tp, Nm>::size;
    using std::map<Tp, Nm>::max_size;

    using std::map<Tp, Nm>::clear;
    using std::map<Tp, Nm>::insert;
    using std::map<Tp, Nm>::insert_or_assign;
    using std::map<Tp, Nm>::emplace;
    using std::map<Tp, Nm>::emplace_hint;
    using std::map<Tp, Nm>::try_emplace;
    using std::map<Tp, Nm>::erase;

    using std::map<Tp, Nm>::operator[];
    using std::map<Tp, Nm>::at;
    using std::map<Tp, Nm>::count;
    using std::map<Tp, Nm>::find;
    // using std::map<Tp, Nm>::contains; C++20
    using std::map<Tp, Nm>::equal_range;
    using std::map<Tp, Nm>::lower_bound;
    using std::map<Tp, Nm>::upper_bound;

    using std::map<Tp, Nm>::key_type;
    using std::map<Tp, Nm>::value_type;

    using std::map<Tp, Nm>::iterator;
    using std::map<Tp, Nm>::pointer;
    using std::map<Tp, Nm>::reference;

    Counter(const std::vector<Tp>& v) : std::map<Tp, Nm>() {
        for (const auto& i : v) {
            this->operator[](i)++;
        }
    }
    template <size_t N>
    Counter(const std::array<Tp, N>& v) : std::map<Tp, Nm>() {
        for (const auto& i : v) {
            this->operator[](i)++;
        }
    }
    Counter(const std::set<Tp>& v) : std::map<Tp, Nm>() {
        for (const auto& i : v) {
            this->operator[](i)++;
        }
    }
    template <std::enable_if_t<std::is_same_v<char, Tp>, std::nullptr_t> = nullptr>
    Counter(const std::string_view& s) : std::map<Tp, Nm>() {
        for (const auto& c : s) {
            this->operator[](c)++;
        }
    }

    bool contains(const Tp& x) const {
        return find(x) != end();
    }
};
