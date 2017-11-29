#pragma once
#include <cassert>

namespace m7 {

#if M7_ENABLE_ASSERT
#define M7_ASSERT(X) assert(X)
#else
#define M7_ASSERT(X)
#endif

}  // namespace m7
