#pragma once
#include <array>
#include <cstddef>
#include <type_traits>

template <typename T, size_t K = 1, std::enable_if_t<K >= 1, std::nullptr_t> = nullptr>
struct MaxCounter {
    using key_type = T;
    using mapped_type = long long;
    inline constexpr static size_t k = K;
    
};
