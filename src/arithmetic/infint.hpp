#pragma once

#include <limits>
#include <type_traits>

/**
 * @brief infを持つ整数型
 * T_MIN + 1 == -T_MIN を要求する
 */
template <class T = int, std::enable_if_t<std::is_integral_v<T> and std::is_signed_v<T>, std::nullptr_t> = nullptr>
struct Infint {
    static_assert(std::numeric_limits<T>::min() + 1 == -std::numeric_limits<T>::max());

    inline constexpr static T T_MAX = std::numeric_limits<T>::max();
    inline constexpr static T T_MIN = std::numeric_limits<T>::min();

   public:
    inline constexpr static T PlusInf = T_MAX;       //!< ∞
    inline constexpr static T MinusInf = T_MIN + 1;  //!< -∞
    inline constexpr static T MAX = PlusInf - 1;     //!< 有限値の最大
    inline constexpr static T MIN = MinusInf + 1;    //!< 有限値の最小
    inline constexpr static T NaN = T_MIN;           //!< Not a Number
    inline constexpr static T Inf = PlusInf;         //!< ∞

    T val_;

    constexpr Infint() noexcept : val_(0) {}
    constexpr Infint(const T& t) noexcept : val_(t) {}
    constexpr Infint(const Infint& t) noexcept = default;
    /**
     * 内部の表現をそのまま返す
     */
    constexpr T val() const noexcept {
        return val_;
    }
    constexpr operator long long int() const {
        return val_;
    }
    constexpr bool isNaN() const noexcept {
        return val_ == NaN;
    }
    /**
     * 有限値かどうか
     */
    constexpr bool isfinite() const noexcept {
        return MinusInf < val_ and val_ < PlusInf;
    }
    constexpr bool isPlusInf() const noexcept {
        return val_ == PlusInf;
    }
    constexpr bool isMinusInf() const noexcept {
        return val_ == MinusInf;
    }
    constexpr Infint operator+() const noexcept {
        return val_;
    }
    constexpr Infint operator-() const noexcept {
        if (val_ == NaN)
            return val_;
        else
            return -val_;
    }
    constexpr T& operator*=(const T& o) noexcept {
        if (val_ == NaN) {
            return *this;
        }
        if (o.val_ == NaN) {
            val_ = NaN;
            return *this;
        }
        if (val_ == 0) {
            if (o.isfinite()) {
                val_ = NaN;
            }
            return *this;
        }
        if (o.val_ == 0) {
            if (isfinite()) {
                val_ = NaN;
            } else {
                val_ = 0;
            }
            return *this;
        }
        if (not isfinite() or not o.isfinite()) {
            if ((val_ > 0) ^ (o.val_ > 0)) {
                val_ = MinusInf;
            } else {
                val_ = PlusInf;
            }
            return *this;
        }
        if (val_ > 0) {
            if (o.val_ > 0) {
                if (val_ > MAX / o.val_) {
                    val_ = PlusInf;
                    return *this;
                }
            } else {
                if (o.val_ < MIN / val_) {
                    val_ = MinusInf;
                    return *this;
                }
            }
        } else {
            if (o.val_ > 0) {
                if (val_ < MIN / o.val_) {
                    val_ = MinusInf;
                    return *this;
                }
            } else {
                if (o.val_ < MAX / val_) {
                    val_ = PlusInf;
                    return *this;
                }
            }
        }
        val_ *= o.val_;
        return *this;
    }
    constexpr T& operator/=(const T& o) noexcept {
        if (val_ == NaN) {
            return *this;
        }
        if (o.val_ == NaN) {
            val_ = NaN;
            return *this;
        }
        if (o.val_ == 0) {
            val_ = NaN;
            return *this;
        }
        if (isPlusInf()) {
            if (!o.isfinete()) {
                val_ = NaN;
            } else if (o.val < 0) {
                val_ = MinusInf;
            }
            return *this;
        }
        if (isMinusInf()) {
            if (!o.isfinete()) {
                val_ = NaN;
            } else if (o.val < 0) {
                val_ = PlusInf;
            }
            return *this;
        }
        if (not isfinite() or not o.isfinite()) {
            if ((val_ > 0) ^ (o.val_ > 0)) {
                val_ = MinusInf;
            } else {
                val_ = PlusInf;
            }
            return *this;
        }
        if (val_ > 0) {
            if (o.val_ > 0) {
                if (val_ > MAX / o.val_) {
                    val_ = PlusInf;
                    return *this;
                }
            } else {
                if (o.val_ < MIN / val_) {
                    val_ = MinusInf;
                    return *this;
                }
            }
        } else {
            if (o.val_ > 0) {
                if (val_ < MIN / o.val_) {
                    val_ = MinusInf;
                    return *this;
                }
            } else {
                if (o.val_ < MAX / val_) {
                    val_ = PlusInf;
                    return *this;
                }
            }
        }
        val_ *= o.val_;
        return *this;
    }
};
