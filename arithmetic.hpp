#ifndef META_ARITHMETIC_HPP_INCLUDED
#define META_ARITHMETIC_HPP_INCLUDED

#include "quote.hpp"
#include "list.hpp"
#include "fold.hpp"
#include "integral.hpp"

namespace meta {
  template <typename... Arguments>
  class plus {
  public:
    typedef typename fold<quote<plus>,
			  typename list::make<Arguments...>::type,
			  int_<0> >::type type;
  };

  template <typename A, typename B>
  class plus<A, B> {
  public:
    typedef int_<A::value + B::value> type;
  };

  template <typename A, typename B>
  class minus {
  public:
    typedef int_<A::value - B::value> type;
  };

  template <typename... Arguments>
  class multiply {
  public:
    typedef typename fold<quote<multiply>,
			  typename list::make<Arguments...>::type,
			  int_<1> >::type type;
  };

  template <typename A, typename B>
  class multiply<A, B> {
  public:
    typedef int_<A::value * B::value> type;
  };

  template <typename A, typename B>
  class divide {
  public:
    typedef int_<A::value / B::value> type;
  };

  template <typename A, typename B>
  class modulo {
  public:
    typedef int_<A::value % B::value> type;
  };
}

#endif
