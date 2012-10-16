#ifndef META_MEMBER_HPP_INCLUDED
#define META_MEMBER_HPP_INCLUDED

#include "wrap.hpp"
#include "bool.hpp"
#include "list.hpp"

namespace meta {
  template <typename T, typename List>
  class member;

  template <typename T, typename Head, typename Tail>
  class member<T,cons<Head,Tail> > {
  public:
    typedef typename if_<typename is_same<T,Head>::type,
			 wrap<true_>,
			 member<T,Tail> >::type::type type;
  };

  template <typename T>
  class member<T,nil> {
  public:
    typedef false_ type;
  };
}

#endif
