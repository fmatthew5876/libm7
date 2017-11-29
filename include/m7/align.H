#pragma once
#include <type_traits>
#include <cstdint>

namespace m7 {

///Returns true if t is aligned to a
///\pre If a is not a power of 2, the result is undefined.
template <typename T,
         typename = std::enable_if_t<std::is_integral_v<T>>>
constexpr bool is_aligned(T t, size_t a) noexcept {
  return ((t & (a-1)) == 0);
}


///Returns true if p is aligned to a
///\pre If a is not a power of 2, the result is undefined.
bool is_aligned(void* p, size_t a) noexcept {
  return is_aligned(uintptr_t(p), a);
}


///Returns the smallest number n when n >= val && is_aligned(n, align).
///\pre If a is not a power of 2, the result is undefined.
template <typename T,
         typename = std::enable_if_t<std::is_integral_v<T>>>
constexpr T align_up(T val, size_t a) noexcept {
  return ((val + (a -1)) & -a);
}


///Returns the closest pointer p' where p' >= p && is_aligned(p, align).
///\pre If a is not a power of 2, the result is undefined.
void* align_up(void* val, size_t a) noexcept {
  return (void*)align_up(uintptr_t(val), a);
}


//Returns the largest number n when n <= val && is_aligned(n, align).
///\pre If a is not a power of 2, the result is undefined.
template <typename T,
         typename = std::enable_if_t<std::is_integral_v<T>>>
constexpr T align_down(T val, size_t a) noexcept {
  return val & -a;
}


//Returns the closest pointer p' where p' <= val && is_aligned(p, align).
///\pre If a is not a power of 2, the result is undefined.
void* align_down(void* val, size_t a) noexcept {
  return (void*)align_down(uintptr_t(val), a);
}


} //namespace m7
