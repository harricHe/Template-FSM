#ifndef META_EXEC_HPP_INCLUDED
#define META_EXEC_HPP_INCLUDED

#include "list.hpp"
#include "declare.hpp"

namespace meta {
  template <typename Value>
  class print {
  public:
    template <typename Stream>
    static Stream& proc(Stream& stream) {
      return stream << Value::value;
    }
  };

  template <template <typename Argument> class Proc,
	    typename List>
  class fold_proc;

  template <template <typename Argument> class Proc,
	    typename Head, typename Tail>
  class fold_proc<Proc, cons<Head, Tail> > {
  public:
    template <typename Accu>
    static Accu& proc(Accu& accu) {
      return fold_proc<Proc, Tail>::proc(Proc<Head>::proc(accu));
    }
  };

  template <template <typename Argument> class Proc>
  class fold_proc<Proc,nil> {
  public:
    template <typename Accu>
    static Accu& proc(Accu& accu) {
      return accu;
    }
  };
}

#endif
