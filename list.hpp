#ifndef META_LIST_HPP_INCLUDED
#define META_LIST_HPP_INCLUDED

#include "integral.hpp"
#include "bool.hpp"
#include "declare.hpp"

namespace meta {
  class nil {};

  template <typename Head, typename Tail>
  class cons;

  template <typename Head, typename TailH, typename TailT>
  class cons<Head, cons<TailH,TailT> > {
  public:
    typedef Head head;
    typedef cons<TailH,TailT> tail;
  };

  template <typename Head>
  class cons<Head,nil> {
  public:
    typedef Head head;
    typedef nil tail;
  };

  template <typename Stream, typename Head, typename Tail>
  Stream& operator<<(Stream& out, const cons<Head, Tail>&) {
    return out << declare<Head>::value << " :: "
	       << declare<Tail>::value;
  }

  template <typename Stream>
  Stream& operator<<(Stream& out, const nil&) {
    return out << "nil";
  }

  namespace list {
    template <typename... Elements>
    class make;

    template <typename Head, typename... Tail>
    class make<Head, Tail...> {
    public:
      typedef cons<Head, typename make<Tail...>::type > type;
    };

    template <>
    class make<> {
    public:
      typedef nil type;
    };

    template <typename N, typename List>
    class take {
    public:
      typedef nil type;
    };

    template <typename N, typename Head, typename Tail>
    class take<N, cons<Head, Tail> > {
    public:
      typedef cons<Head, typename take<int_<N::value-1>, Tail>::type> type;
    };

    template <typename Head, typename Tail>
    class take<int_<0>, cons<Head, Tail> > {
    public:
      typedef nil type;
    };

    template <typename N, typename List>
    class drop {
    public:
      typedef List type;
    };

    template <typename N, typename Head, typename Tail>
    class drop<N, cons<Head, Tail> > {
    public:
      typedef typename drop<int_<N::value-1>, Tail>::type type;
    };

    template <typename Head, typename Tail>
    class drop<int_<0>, cons<Head, Tail> > {
    public:
      typedef cons<Head, Tail> type;
    };

    template <typename T>
    class is {
    public:
      typedef false_ type;
    };

    template <>
    class is<nil> {
    public:
      typedef true_ type;
    };

    template <typename H, typename T>
    class is<cons<H,T> > {
    public:
      typedef true_ type;
    };
  }
}

#endif
