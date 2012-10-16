#ifndef META_IDENTITY_HPP_INCLUDED
#define META_IDENTITY_HPP_INCLUDED

namespace meta {
  class identity {
  public:
    template <typename Type>
    class apply {
    public:
      typedef Type type;
    };
  };
}

#endif
