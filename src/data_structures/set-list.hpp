#include <cassert>
#include <initializer_list>
#include <iterator>
#include <map>
template <typename T>
class SetList {
   public:
    using value_type = T;
    class iterator {
        SetList& setlist;
        using value_type = T;
    };

   private:
    map<value_type, iterator> m;
    iterator _begin, _end;

   public:
    SetList() : _begin() {}
};
