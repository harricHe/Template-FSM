#ifndef META_INTEGRAL_HPP_INCLUDED
#define META_INTEGRAL_HPP_INCLUDED

namespace meta {
  template <typename Type, Type Value>
  class integral_ {
  public:
    typedef Type value_type;
    static const Type value = Value;
  };

  template <bool Value>
  class bool_ : public integral_<bool, Value> {};

  template <int Value>
  class int_ : public integral_<int, Value> {};

  template <char Value>
  class char_ : public integral_<char, Value> {};

  template <typename Stream, typename Type, Type Value>
  Stream& operator<<(Stream& out, const integral_<Type, Value>&) {
      return out << Value;
  }
}

#endif
