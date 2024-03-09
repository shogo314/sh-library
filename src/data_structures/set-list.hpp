#pragma once
#include <cassert>
#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <list>
#include <map>

template <typename T>
class SetList {
   public:
    using value_type = T;

   private:
    using base_type = std::list<value_type>;
    using base_type_itr = typename std::list<value_type>::iterator;

   public:
    using reference = value_type&;
    using const_reference = const value_type&;
    using difference_type = std::ptrdiff_t;
    using size_type = std::size_t;

    class iterator {
        SetList& setlist;
        base_type_itr& itr;

       public:
        using difference_type = SetList::difference_type;
        using value_type = iterator;
        using pointer = SetList::value_type*;
        using reference = SetList::value_type&;
        using iterator_category = std::bidirectional_iterator_tag;
        
    };

   private:
    std::map<value_type, iterator> m;
    base_type ls;
    iterator _begin, _end;

   public:
    SetList() : m{}, ls{}, _begin{*this, ls.end()}, _end{*this, ls.end()} {}
};
