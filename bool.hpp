#ifndef META_BOOL_HPP_INCLUDED
#define META_BOOL_HPP_INCLUDED

#include "integral.hpp"

namespace meta {
  typedef bool_<true> true_;
  typedef bool_<false> false_;

  template <typename If, typename Then, typename Else>
  class if_ {};

  template <typename Then, typename Else>
  class if_<true_, Then, Else> {
  public:
    typedef Then type;
  };

  template <typename Then, typename Else>
  class if_<false_, Then, Else> {
  public:
    typedef Else type;
  };

  template <typename T>
  class not_ {
  public:
    typedef bool_<!T::value> type;
  };

  template <typename A, typename B>
  class is_same {
  public:
    typedef false_ type;
  };

  template <typename A>
  class is_same<A,A> {
  public:
    typedef true_ type;
  };

  template <typename A, typename B>
  class is_different {
  public:
    typedef typename not_<typename is_same<A,B>::type>::type type;
  };

  template <typename A, typename B>
  class and_ {
  public:
    typedef false_ type;
  };

  template <>
  class and_<true_,true_> {
  public:
    typedef true_ type;
  };

  template <typename A, typename B>
  class or_ {
  public:
    typedef true_ type;
  };

  template <>
  class or_<false_,false_> {
  public:
    typedef false_ type;
  };
}

#endif
