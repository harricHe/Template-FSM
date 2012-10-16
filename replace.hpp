#ifndef META_REPLACE_HPP_INCLUDED
#define META_REPLACE_HPP_INCLUDED

#include "list.hpp"
#include "integral.hpp"

namespace meta {
  template <typename List, typename N, typename Value>
  class replace;

  template <typename Head, typename Tail, typename N, typename Value>
  class replace<cons<Head,Tail>, N, Value> {
  public:
    typedef cons<Head, typename replace<Tail, int_<N::value-1>, Value>::type> type;
  };

  template <typename Head, typename Tail, typename Value>
  class replace<cons<Head,Tail>, int_<0>, Value> {
  public:
    typedef cons<Value, Tail> type;
  };
}

#endif
