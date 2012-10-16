#ifndef META_REVERSE_HPP_INCLUDED
#define META_REVERSE_HPP_INCLUDED

#include "fold.hpp"
#include "quote.hpp"
#include "list.hpp"

namespace meta {
  template <template <typename... Arguments> class Function>
  class quote;

  template <typename List>
  class reverse {
  public:
    typedef typename fold<quote<cons>,
			  List,
			  nil>::type type;
  };
}

#endif
