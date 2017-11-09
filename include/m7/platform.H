#pragma once

#define M7_LIKELY(X) __builtin_expect(bool(X), 1)
#define M7_UNLIKELY(X) __builtin_expect(bool(X), 0)

