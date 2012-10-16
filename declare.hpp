#ifndef META_DECLARE_HPP_INCLUDED
#define META_DECLARE_HPP_INCLUDED

namespace meta {
  template <typename Type>
  class declare {
  public:
    static Type const value;
  };

  template <typename Type>
  const Type declare<Type>::value;
}

#endif
