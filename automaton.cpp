#include "automaton.hpp"
#include "declare.hpp"
#include <iostream>

using namespace meta::automaton;
using namespace meta::automaton::operators;

typedef predefined::number result;

typedef typename minimal<result>::type mini;

int main() {
  std::cout << "FSM:" << std::endl
	    << meta::declare<result>::value << std::endl;
  std::cout << "MINI FSM:" << std::endl
	    << meta::declare<mini>::value << std::endl;
  return 0;
}
