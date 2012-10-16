#ifndef META_LENGTH_HPP_INCLUDED
#define META_LENGTH_HPP_INCLUDED

#include "fold.hpp"
#include "arithmetic.hpp"
#include "integral.hpp"

namespace meta {
  namespace __length {
    template <typename A, typename B>
    class plus1 {
    public:
      typedef typename plus<int_<1>,B>::type type;
    };
  }

  template <typename LIST>
  class length {
  public:
    typedef typename fold<quote<__length::plus1>,
			  LIST,
			  int_<0> >::type type;
  };
}

#ifdef TESTING

#include "string.hpp"
#include <iostream>

constexpr char test_length_data[] = "hello world";

void test_length() {
  using namespace std;
  using namespace meta;
  typedef string_<test_length_data>::type hw;
  typedef length<hw>::type hwl;
  cout << "length of " << test_length_data << " is " << hwl::value << endl;
}

#endif

#endif
