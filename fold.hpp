#ifndef META_FOLD_HPP_INCLUDED
#define META_FOLD_HPP_INCLUDED

#include "apply.hpp"
#include "list.hpp"

namespace meta {
  template <typename Function, typename List, typename Accu>
  class fold {
  public:
    typedef typename fold<Function,
			  typename List::tail,
			  typename apply<Function,
					 typename List::head,
					 Accu>::type>::type type;
  };

  template <typename Function, typename Accu>
  class fold<Function, nil, Accu> {
  public:
    typedef Accu type;
  };

  template <typename Function, typename List, typename Accu>
  class foldr {
  public:
    typedef typename apply<Function,
			   typename List::head,
			   typename foldr<Function, typename List::tail, Accu>::type>::type type;
  };

  template <typename Function, typename Accu>
  class foldr<Function, nil, Accu> {
  public:
    typedef Accu type;
  };
}

#endif
