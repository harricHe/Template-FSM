#ifndef META_HAS_HPP_INCLUDED
#define META_HAS_HPP_INCLUDED

#define META_HAS_HPP_CREATE_MEMBER_DETECTOR(X)                               \
template<typename T>                                                         \
class has_##X {                                                              \
    typedef char one[1];                                                     \
    typedef char two[2];                                                     \
                                                                             \
    struct Fallback { int X; };						     \
    struct Derived : T, Fallback {};					     \
    template<typename U, U> struct helper;				     \
                                                                             \
    template<typename U> static one & func(helper<int Fallback::*, &U::X>*); \
    template<typename U> static two & func(...);                             \
  public:                                                                    \
    typedef bool_<sizeof(func<Derived>(0)) == sizeof(two)> type;             \
};

#include "bool.hpp"

namespace meta {
  META_HAS_HPP_CREATE_MEMBER_DETECTOR(value);
}

#undef META_HAS_HPP_CREATE_MEMBER_DETECTOR

#ifdef TESTING

#include <iostream>

class test_has_failure {};

void test_has() {
  using namespace std;
  using namespace meta;
  cout << (has_value<true_>::type::value ? "success ok" : "failure KO") << endl;
  cout << (has_value<test_has_failure>::type::value ? "success KO" : "failure ok") << endl;
}

#endif

#endif
