#ifndef META_INSERT_HPP_INCLUDED
#define META_INSERT_HPP_INCLUDED

#include "list.hpp"
#include "integral.hpp"

namespace meta {
  template <typename N, typename Value, typename List>
  class insert {
  public:
    typedef cons<typename List::head,
		 typename insert<int_<N::value-1>, Value, typename List::tail>::type> type;
  };

  template <typename Value, typename List>
  class insert<int_<0>, Value, List> {
  public:
    typedef cons<Value, List> type;
  };
}

#ifdef TESTING

#include <iostream>
#include "exec.hpp"
#include "string.hpp"

constexpr char test_insert_data[] = "hllo world!";

void test_insert() {
  using namespace std;
  using namespace meta;
  typedef typename string_<test_insert_data>::type hw;
  typedef typename insert<int_<1>, char_<'e'>, hw>::type hw1;
  fold_proc<print, hw1>::proc(cout) << " = hello world!" << endl;
}

#endif

#endif
