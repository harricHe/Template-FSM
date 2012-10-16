#ifndef META_ASSOC_HPP_INCLUDED
#define META_ASSOC_HPP_INCLUDED

#include "wrap.hpp"
#include "list.hpp"

namespace meta {
  class not_found;

  template <typename... Types>
  class tuple;

  template <typename Type, typename List>
  class assoc {
  public:
    typedef not_found type;
  };

  template <typename Type, typename A, typename B, typename Tail>
  class assoc<Type, cons<tuple<A, B>, Tail> > {
  public:
    typedef typename if_<typename is_same<A, Type>::type,
			 wrap<B>,
			 assoc<Type, Tail> >::type::type type;
  };
}

#endif
