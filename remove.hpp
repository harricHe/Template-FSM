#ifndef META_REMOVE_HPP_INCLUDED
#define META_REMOVE_HPP_INCLUDED

#include "bind.hpp"
#include "filter.hpp"
#include "integral.hpp"
#include "bool.hpp"
#include "quote.hpp"

namespace meta {
  template <typename Element, typename Set>
  class remove {
  public:
    typedef typename filter<bind<quote<is_different>, int_<0>, Element>, Set>::type type;
  };
}

#endif
