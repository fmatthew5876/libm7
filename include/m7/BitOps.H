#pragma once

namespace m7 {


//Returns true if t is aligned to a

template <typename Integral>

constexpr bool is_aligned(Integral t, size_t a) noexcept {

  return ((t & (a-1)) == 0);

}

bool is_aligned(void* t, size_t a) noexcept {

  return is_aligned(uintptr_t(t), a);

}



//Returns the smallest number n when n >= val && is_aligned(n, align). align must be a power of 2!

template <typename Integral>

constexpr Integral align_up(Integral val, size_t a) noexcept {

  return ((val + (a -1)) & -a);

}

void* align_up(void* val, size_t a) noexcept {

  return (void*)align_up(uintptr_t(val), a);

}



//Returns the largest number n when n <= val && is_aligned(n, align). align must be a power of 2!

template <typename Integral>

constexpr Integral align_down(Integral val, size_t a) noexcept {

  return val & -a;

}

void* align_down(void* val, size_t a) noexcept {

  return (void*)align_down(uintptr_t(val), a);

}

}
