#ifndef META_BIND_HPP_INCLUDED
#define META_BIND_HPP_INCLUDED

#include "insert.hpp"
#include "vector.hpp"
#include "list.hpp"
#include "apply.hpp"

namespace meta {
  namespace __bind {
    template <typename Function, typename Tuple>
    class aux {};

    template <typename Function, typename... Arguments>
    class aux<Function, tuple<Arguments...> > {
    public:
      typedef typename apply<Function, Arguments...>::type type;
    };
  }

  template <typename Function, typename Place, typename Value>
  class bind {
  public:
    template <typename... Arguments>
    class apply {
      typedef typename vector<typename insert<Place,
					      Value,
					      typename list::make<Arguments...>::type>::type>::type bound;
    public:
      typedef typename __bind::aux<Function, bound>::type type;
    };
  };
}

#endif
