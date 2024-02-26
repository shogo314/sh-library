#pragma once

#include <iostream>
#include <limits>
#include <type_traits>

/**
 * inf型をもつ整数型
 * Tは符号付き整数であり、2の補数表現で表されることを期待する
 */
template <typename T = int, std::enable_if_t<std::is_integral_v<T> and std::is_signed_v<T>, std::nullptr_t> = nullptr>
struct infint {
   private:
    static_assert(std::numeric_limits<T>::min() + 1 == -std::numeric_limits<T>::max());

    T _v;

    inline constexpr static T _PlusInf = std::numeric_limits<T>::max();       //<! 正の無限大
    inline constexpr static T _MinusInf = std::numeric_limits<T>::min() + 1;  //<! 負の無限大
    inline constexpr static T _NaN = std::numeric_limits<T>::min();           //<! Not a Number

   public:
    constexpr infint() noexcept : _v(0) {}
    constexpr infint(const T& t) noexcept : _v(t) {}
    constexpr infint(const infint& o) noexcept : _v(o._v) {}

    /**
     * 内部表現をそのまま返す
     */
    constexpr T val() const noexcept { return _v; }

    constexpr bool isNaN() const noexcept { return _v == _NaN; }
    constexpr bool isPlusInf() const noexcept { return _v == _PlusInf; }
    constexpr bool isMinusInf() const noexcept { return _v == _MinusInf; }
    constexpr bool isInf() const noexcept { return _v == _PlusInf; }
    constexpr bool isfinite() const noexcept { return _MinusInf < _v and _v < _PlusInf; }

    constexpr const T& operator=(const infint& o) noexcept { return _v = o._v; }
    constexpr const T& operator=(const T& t) noexcept { return _v = t; }

    constexpr T operator+() const noexcept { return _v; }
    constexpr T operator-() const noexcept {
        if (_v == _NaN) return _v;
        return -_v;
    }

    

    /**
     * 正の無限大
     */
    constexpr static T PlusInf() noexcept {
        return _PlusInf;
    }
    /**
     * 負の無限大
     */
    constexpr static T MinusInf() noexcept {
        return _MinusInf;
    }
    /**
     * Not a Number
     */
    constexpr static T NaN() noexcept {
        return _NaN;
    }
    /**
     * 正の無限大(PlusInfと同じ)
     */
    constexpr static T Inf() noexcept {
        return _PlusInf;
    }
    /**
     * 正の無限大でない最大値
     */
    constexpr static T max() noexcept {
        return _PlusInf - 1;
    }
    /**
     * 負の無限大でない最小値
     */
    constexpr static T min() noexcept {
        return _MinusInf + 1;
    }

    friend constexpr bool operator<(const infint& t1, const infint& t2) noexcept {
        if (t1.isNaN() or t2.isNaN()) return false;
        return t1._v < t2._v;
    }
    friend constexpr bool operator>(const infint& t1, const infint& t2) noexcept {
        if (t1.isNaN() or t2.isNaN()) return false;
        return t1._v > t2._v;
    }
    friend constexpr bool operator<=(const infint& t1, const infint& t2) noexcept {
        if (t1.isNaN() or t2.isNaN()) return false;
        return t1._v <= t2._v;
    }
    friend constexpr bool operator>=(const infint& t1, const infint& t2) noexcept {
        if (t1.isNaN() or t2.isNaN()) return false;
        return t1._v >= t2._v;
    }
    friend constexpr bool operator==(const infint& t1, const infint& t2) noexcept {
        return t1._v == t2._v;
    }
    friend constexpr bool operator!=(const infint& t1, const infint& t2) noexcept {
        return t1._v != t2._v;
    }
};
