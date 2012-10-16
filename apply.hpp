#ifndef META_APPLY_HPP_INCLUDED
#define META_APPLY_HPP_INCLUDED

namespace meta {
  template <typename Function, typename... Arguments>
  class apply {
  public:
    typedef typename Function::template apply<Arguments...>::type type;
  };
}

#endif
