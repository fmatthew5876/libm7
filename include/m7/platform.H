#pragma once

#if defined(__GNUC__)

#define M7_LIKELY(X) __builtin_expect(bool(X), 1)
#define M7_UNLIKELY(X) __builtin_expect(bool(X), 0)

#else

#define M7_LIKELY(X)
#define M7_UNLIKELY(X)

#endif

