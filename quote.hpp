#ifndef META_QUOTE_HPP_INCLUDED
#define META_QUOTE_HPP_INCLUDED

#include "bool.hpp"
#include "vector.hpp"
#include "wrap.hpp"

namespace meta {
  namespace __quote {
    template <typename T>
    class has_type {
      typedef char True;
      typedef struct {char test[2];} False;

      template <typename Class>
      static False _has(...);

      template <typename Class>
      static True _has(typename Class::type const*);

    public:
      typedef bool_<sizeof(_has<T>(0)) == sizeof(True)> type;
    };
  }

  template <template <typename... Arguments> class Function>
  class quote {
  public:
    template <typename... Arguments>
    class apply {
      typedef Function<Arguments...> function;
    public:
      typedef typename if_<typename __quote::has_type<function>::type,
			   function,
			   wrap<function> >::type::type type;
    };
  };
}

#endif
