#ifndef META_PARTITION_HPP_INCLUDED
#define META_PARTITION_HPP_INCLUDED

#include "list.hpp"
#include "bool.hpp"
#include "apply.hpp"

namespace meta {
  template <typename Filter, typename List>
  class partition;

  template <typename Filter, typename Head, typename Tail>
  class partition<Filter, cons<Head,Tail> > {
    typedef partition<Filter,Tail> next;
  public:
    typedef typename if_<typename apply<Filter, Head>::type,
			 cons<Head, typename next::ok>,
			 typename next::ok>::type ok;
    typedef typename if_<typename apply<Filter, Head>::type,
			 typename next::ko,
			 cons<Head, typename next::ko> >::type ko;
  };

  template <typename Filter>
  class partition<Filter, nil> {
  public:
    typedef nil ok;
    typedef nil ko;
  };
}

#endif
