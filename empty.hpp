#ifndef META_EMPTY_HPP_INCLUDED
#define META_EMPTY_HPP_INCLUDED

#include "list.hpp"
#include "bool.hpp"

namespace meta {
  template <typename List>
  class empty {
  public:
    typedef typename is_same<List,nil>::type type;
  };
}

#endif
