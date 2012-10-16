#define TESTING

#include <iostream>
#include "arithmetic.hpp"
#include "list.hpp"
#include "exec.hpp"
#include "string.hpp"
#include "integral.hpp"
#include "add.hpp"
#include "append.hpp"
#include "remove.hpp"
#include "insert.hpp"
#include "map.hpp"
#include "length.hpp"
#include "compare.hpp"
#include "sort.hpp"
#include "has.hpp"

using namespace meta;
using namespace std;

constexpr char hello[] = "hello ";
constexpr char world[] = "world!";

int main() {
  test_insert();
  test_add();
  test_map();
  test_append();
  test_length();
  test_sort();
  test_has();

  cout << "6 = " << meta::plus<int_<1>, int_<2>, int_<3> >::type::value << endl;
  cout << "6 = " << meta::multiply<int_<1>, int_<2>, int_<3> >::type::value << endl;

  typedef reverse<typename fold<quote<add>,
				typename append<typename string_<hello>::type,
						typename string_<world>::type>::type,
				nil>::type>::type hw;

  typedef meta::remove<char_<'w'>, hw>::type hw2;

  //typedef sort<quote<compare::le>, cons<char_<'X'>, nil> >::type hw3;
  typedef sort<quote<compare::le>, hw>::type hw3;

  fold_proc<print, hw>::proc(cout) << endl;
  fold_proc<print, hw2>::proc(cout) << endl;
  fold_proc<print, hw3>::proc(cout) << endl;

  // string shw = "hello world! sdf";
  // string::iterator shwb = shw.begin();
  // string::iterator shwe = shw.end();
  // cout << "parsing " << parsers::make<hw>::type::match(shwb,shwe) << endl;

  return 0;
}
