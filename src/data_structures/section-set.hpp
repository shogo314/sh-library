#pragma once
#include <functional>
#include <set>
template <typename T = long long, class Compare = std::less<T>>
class SectionSet {
   public:
    using value_type = T;
    inline constexpr static auto comp = Compare();

    std::set<std::pair<T, T>> data;
    SectionSet() = default;
    
};
