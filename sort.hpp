#ifndef META_SORT_HPP_INCLUDED
#define META_SORT_HPP_INCLUDED

#include "compare.hpp"
#include "bool.hpp"
#include "list.hpp"
#include "length.hpp"
#include "wrap.hpp"

namespace meta {
  template <typename Compare, typename A, typename B>
  class merge {
  public:
    typedef typename if_<typename apply<Compare, typename A::head, typename B::head>::type,
			 cons<typename A::head, typename merge<Compare, typename A::tail, B>::type>,
			 cons<typename B::head, typename merge<Compare, A, typename B::tail>::type> >::type type;
  };

  template <typename Compare, typename A>
  class merge<Compare, A, nil> {
  public:
    typedef A type;
  };

  template <typename Compare, typename B>
  class merge<Compare, nil, B> {
  public:
    typedef B type;
  };

  template <typename Compare>
  class merge<Compare, nil, nil> {
  public:
    typedef nil type;
  };

  template <typename Compare, typename List>
  class sort;

  namespace __sort {
    template <typename Compare, typename List>
    class aux {
      typedef typename length<List>::type l;
      typedef typename divide<l,int_<2> >::type l2;
      typedef typename list::take<l2, List>::type a;
      typedef typename list::drop<l2, List>::type b;
    public:
      typedef typename merge<Compare,
			     typename sort<Compare, a>::type,
			     typename sort<Compare, b>::type>::type type;
    };
  }

  template <typename Compare, typename List>
  class sort {
  public:
    typedef typename if_<typename compare::le<typename length<List>::type,
					      int_<1> >::type,
			 wrap<List>,
			 __sort::aux<Compare, List> >::type::type type;
  };
}

#ifdef TESTING

#include <iostream>
#include "exec.hpp"
#include "quote.hpp"
#include "compare.hpp"
#include "string.hpp"

constexpr char test_sort_data[] = "0246813579";

void test_sort() {
  using namespace std;
  using namespace meta;
  typedef typename string_<test_sort_data>::type l;
  fold_proc<print, typename sort<quote<compare::lt>, l>::type>::proc(cout) << " = 012345678" << endl;
}

#endif

#endif
