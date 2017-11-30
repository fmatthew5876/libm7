#pragma once
#include <cstddef>

namespace m7 {

template <typename T, size_t N>
    class StaticArrayView;

template <typename T, size_t N>
    using CStaticArrayView = StaticArrayView<const T,N>;

}
