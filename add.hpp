#ifndef META_ADD_HPP_INCLUDED
#define META_ADD_HPP_INCLUDED

#include "member.hpp"
#include "bool.hpp"
#include "list.hpp"

namespace meta {
  template <typename Element, typename Set>
  class add {
  public:
    typedef typename if_<typename member<Element, Set>::type,
			 Set,
			 cons<Element,Set> >::type type;
  };
}

#ifdef TESTING

#include <iostream>
#include "exec.hpp"
#include "string.hpp"

constexpr char test_add_data[] = "hello world";

void test_add() {
  using namespace std;
  using namespace meta;
  typedef typename string_<test_add_data>::type hw;
  typedef typename add<char_<'X'>, hw>::type hw1;
  typedef typename add<char_<'o'>, hw>::type hw2;
  fold_proc<print, hw1>::proc(cout) << " = Xhello world" << endl;
  fold_proc<print, hw2>::proc(cout) << " = hello world" << endl;
}

#endif

#endif
