#pragma once

#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "traits.hpp"

namespace detail {

template <typename T>
inline std::string type_str(const T& t) {
    return "T";
}
template <typename T, std::enable_if_t<not has_repr_v<T>, std::nullptr_t> = nullptr>
inline std::string repr(const T& t) {
    return (std::ostringstream() << type_str(t) << "(" << t << ")").str();
}
template <typename T, std::enable_if_t<has_repr_v<T>, std::nullptr_t> = nullptr>
inline std::string repr(const T& t) {
    return t.repr();
}

inline std::string type_str(const char*) {
    return "char*";
}
inline std::string repr(const char* t) {
    return (std::ostringstream() << "\"" << t << "\"").str();
}

inline std::string type_str(const char&) {
    return "char";
}
inline std::string repr(const char& t) {
    return (std::ostringstream() << "'" << t << "'").str();
}

inline std::string type_str(const int&) {
    return "int";
}
inline std::string repr(const int& t) {
    return std::to_string(t);
}

inline std::string type_str(const long&) {
    return "long";
}
inline std::string repr(const long& t) {
    return std::to_string(t) + "l";
}

inline std::string type_str(const long long&) {
    return "long long";
}
inline std::string repr(const long long& t) {
    return std::to_string(t) + "ll";
}

inline std::string type_str(const unsigned int&) {
    return "unsigned int";
}
inline std::string repr(const unsigned int& t) {
    return std::to_string(t) + "u";
}

inline std::string type_str(const unsigned long&) {
    return "unsigned long";
}
inline std::string repr(const unsigned long& t) {
    return std::to_string(t) + "ul";
}

inline std::string type_str(const unsigned long long&) {
    return "unsigned long long";
}
inline std::string repr(const unsigned long long& t) {
    return std::to_string(t) + "ull";
}

inline std::string type_str(const std::string&) {
    return "std::string";
}
inline std::string repr(const std::string& t) {
    return (std::ostringstream() << type_str(t) << "(\"" << t << "\")").str();
}

inline std::string type_str(const float&) {
    return "float";
}
inline std::string repr(const float& t) {
    return std::to_string(t) + "f";
}

inline std::string type_str(const double&) {
    return "double";
}
inline std::string repr(const double& t) {
    return std::to_string(t);
}

inline std::string type_str(const long double&) {
    return "long double";
}
inline std::string repr(const long double& t) {
    return std::to_string(t) + "l";
}

template <typename T>
inline std::string type_str(const std::vector<T>&) {
    T t;
    return "std::vector<" + type_str(t) + ">";
}
template <typename T>
inline std::string repr(const std::vector<T>& t) {
    std::ostringstream ret;
    ret << type_str(t) << "{";
    for (auto itr = t.begin(); itr != t.end(); itr++) {
        ret << repr(*itr);
        if (itr != --t.end()) {
            ret << ", ";
        }
    }
    ret << "}";
    return ret.str();
}

template <typename T>
inline std::string type_str(const std::set<T>&) {
    T t;
    return "std::set<" + type_str(t) + ">";
}
template <typename T>
inline std::string repr(const std::set<T>& t) {
    std::ostringstream ret;
    ret << type_str(t) << "{";
    for (auto itr = t.begin(); itr != t.end(); itr++) {
        ret << repr(*itr);
        if (itr != --t.end()) {
            ret << ", ";
        }
    }
    ret << "}";
    return ret.str();
}

}  // namespace detail

template <typename T>
inline std::string type_str(const T& t) {
    return detail::type_str(t);
}
template <typename T>
inline std::string repr(const T& t) {
    return detail::repr(t);
}
