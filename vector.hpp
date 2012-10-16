#ifndef META_VECTOR_HPP_INCLUDED
#define META_VECTOR_HPP_INCLUDED

#include "list.hpp"
#include "fold.hpp"
#include "quote.hpp"
#include "reverse.hpp"
#include "declare.hpp"

namespace meta {
  template <typename... Types>
  class tuple {};

  namespace __print_tuple {
    template <typename... Arguments>
    class aux {
    public:
      template <typename Accu>
      static Accu& proc(Accu& accu) {
	return accu;
      }
    };

    template <typename Head, typename... Arguments>
    class aux<Head, Arguments...> {
    public:
      template <typename Accu>
      static Accu& proc(Accu& accu) {
	return aux<Arguments...>::proc(accu << " " << declare<Head>::value);
      }
    };
  }

  template <typename Stream, typename... Types>
  Stream& operator<<(Stream& out, const tuple<Types...>&) {
    return __print_tuple::aux<Types...>::proc(out << "[") << " ]";
  }

  namespace __vector {
    template <typename A, typename TUPLE>
    class aux;

    template <typename A, typename... Types>
    class aux<A, tuple<Types...> > {
    public:
      typedef tuple<A, Types...> type;
    };
  }

  template <typename List>
  class vector {
  public:
    typedef typename fold<quote<__vector::aux>,
			  typename reverse<List>::type,
			  tuple<> >::type type;
  };
}

#endif
