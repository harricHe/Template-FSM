#ifndef META_APPEND_HPP_INCLUDED
#define META_APPEND_HPP_INCLUDED

#include "fold.hpp"
#include "quote.hpp"

namespace meta {
  template <typename List1, typename List2>
  class append {
  public:
    typedef typename foldr<quote<cons>, List1, List2>::type type;
  };

}

#ifdef TESTING

#include <iostream>
#include "exec.hpp"
#include "string.hpp"

constexpr char test_append_hello[] = "begin";
constexpr char test_append_world[] = "...end";

void test_append() {
  using namespace std;
  using namespace meta;
  typedef append<typename string_<test_append_hello>::type,
		 typename string_<test_append_world>::type>::type hw;

  cout << test_append_hello << test_append_world << " = ";
  fold_proc<print, hw>::proc(cout) << endl;
}

#endif

#endif
