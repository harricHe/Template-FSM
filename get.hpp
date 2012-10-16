#ifndef META_GET_HPP_INCLUDED
#define META_GET_HPP_INCLUDED

#include "list.hpp"
#include "integral.hpp"

namespace meta {
  template <typename List, typename N>
  class get {
  public:
    typedef typename get<typename List::tail, int_<N::value-1> >::type type;
  };

  template <typename List>
  class get<List, int_<0> > {
  public:
    typedef typename List::head type;
  };

  template <typename... Types>
  class tuple;

  template <typename... Arguments, typename N>
  class get<tuple<Arguments...>, N> {
  public:
    typedef typename get<typename list::make<Arguments...>::type, N>::type type;
  };

  template <typename... Arguments>
  class get<tuple<Arguments...>, int_<0> > {
  public:
    typedef typename get<typename list::make<Arguments...>::type, int_<0> >::type type;
  };
}

#endif
