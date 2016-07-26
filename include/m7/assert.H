#pragma once
#include <cassert>
#include <m7/exception.H>

namespace m7 {

#if M7_ENABLE_ASSERT
#define M7_ASSERT(X) assert(X)
#else
#define M7_ASSERT(X)
#endif

}  // namespace m7
