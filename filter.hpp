#ifndef META_FILTER_HPP_INCLUDED
#define META_FILTER_HPP_INCLUDED

#include "partition.hpp"

namespace meta {
  template <typename Filter, typename List>
  class filter {
  public:
    typedef typename partition<Filter, List>::ok type;
  };
}

#endif
