#include "automaton.hpp"
#include "declare.hpp"
#include <iostream>

using namespace meta::automaton;

typedef typename fsm_char<meta::char_<'a'> >::type a;
typedef typename fsm_char<meta::char_<'b'> >::type b;
typedef typename fsm_or<a,b>::type ab;
typedef typename fsm_seq<ab,ab>::type ab2;
typedef typename fsm_star<ab2>::type ab2s;
typedef typename add_eps_trans<ab2s, meta::int_<4>, meta::int_<11> >::type ab2st;

typedef typename non_deterministic<ab2s>::type result;
typedef typename non_deterministic<typename minimal<result>::type>::type mini;

typedef closure<result,
		epsilon,
		typename meta::list::make<meta::int_<0>,
					  meta::int_<1> >::type>::type c;

int main() {
  std::cout << "FSM:" << std::endl
	    << meta::declare<result>::value << std::endl;
  std::cout << "MINI FSM:" << std::endl
	    << meta::declare<mini>::value << std::endl;
  std::cout << meta::declare<typename meta::vector<c>::type>::value << std::endl;
  return 0;
}
