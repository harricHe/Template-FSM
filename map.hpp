#ifndef META_MAP_HPP_INCLUDED
#define META_MAP_HPP_INCLUDED

#include "list.hpp"
#include "apply.hpp"

namespace meta {
  template <typename Function, typename List>
  class map {
  public:
    typedef cons<typename apply<Function, typename List::head>::type,
		 typename map<Function, typename List::tail>::type> type;
  };

  template <typename Function>
  class map<Function, nil> {
  public:
    typedef nil type;
  };
}

#ifdef TESTING

#include <iostream>
#include "exec.hpp"
#include "string.hpp"
#include "integral.hpp"

constexpr char test_map_data[] = "IfmmpXpsme";

template <typename N>
class test_map_class {
public:
  typedef meta::char_<N::value-1> type;
};

void test_map() {
  using namespace std;
  using namespace meta;
  typedef typename string_<test_map_data>::type hw;
  typedef typename map<quote<test_map_class>, hw>::type hw1;
  fold_proc<print, hw1>::proc(cout) << " = HelloWorld" << endl;
}

#endif

#endif
