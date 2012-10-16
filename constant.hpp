#ifndef META_CONSTANT_HPP_INCLUDED
#define META_CONSTANT_HPP_INCLUDED

namespace meta {
  template <typename Type>
  class constant {
  public:
    template <typename Argument>
    class apply {
    public:
      typedef Type type;
    };
  };
}

#endif
