#ifndef META_COMPOSE_HPP_INCLUDED
#define META_COMPOSE_HPP_INCLUDED

#include "apply.hpp"

namespace meta {
  template <typename Function1, typename Function2>
  class compose {
  public:
    template <typename Argument>
    class apply {
    public:
      typedef typename meta::apply<Function1, typename meta::apply<Function2, Argument>::type>::type type;
    };
  };
}

#endif
