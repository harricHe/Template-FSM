#ifndef META_COMPARE_HPP_INCLUDED
#define META_COMPARE_HPP_INCLUDED

#include "bool.hpp"

namespace meta {
  namespace compare {
    template <typename A, typename B>
    class lt {
    public:
      typedef bool_<(A::value < B::value)> type;
    };

    template <typename A, typename B>
    class le {
    public:
      typedef bool_<(A::value <= B::value)> type;
    };

    template <typename A, typename B>
    class gt {
    public:
      typedef bool_<(A::value > B::value)> type;
    };

    template <typename A, typename B>
    class ge {
    public:
      typedef bool_<(A::value >= B::value)> type;
    };
  }
}

#endif
