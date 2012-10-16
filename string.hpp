#ifndef META_STRING_HPP_INCLUDED
#define META_STRING_HPP_INCLUDED

#include "identity.hpp"
#include "integral.hpp"
#include "list.hpp"
#include "bool.hpp"

namespace meta {
  namespace __string {
    template <unsigned int C, const char Value[]>
    class aux;

    template <unsigned int C, const char Value[]>
    class aux2 {
    public:
      typedef cons<char_<Value[C]>, typename aux<C+1, Value>::type> type;
    };

    template <unsigned int C, const char Value[]>
    class aux {
    public:
      typedef typename if_<bool_<Value[C]==0>,
			   identity::apply<nil>,
			   aux2<C,Value> >::type::type type;
    };
  }

  template <const char Value[]>
  class string_ {
  public:
    typedef typename __string::aux<0, Value>::type type;
  };
}

#endif
