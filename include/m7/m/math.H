#pragma once
#include <cmath>
#include <m7/config.H>
#include <type_traits>

namespace m7 {

/// Defines math types and functions.
namespace m {

/// isVectorLikeV type trait type.
template <typename T>
struct isVectorLike {
       private:
	static std::false_type _test(...);
	template <typename U,
		  typename ScalarArrayT = decltype(std::declval<U>().elems())>
	static std::true_type _test(U&&);

       public:
	static constexpr bool value = decltype(_test(std::declval<T>()))::value;
};

/// True if T is a matrix or vector type.
template <typename T>
static constexpr bool isVectorLikeV = isVectorLike<T>::value;

/// Result type of sincos() function.
template <typename T>
struct SinCos_t {
	T s = {};
	T c = {};
};

/// Compute both sin and cosine. May be faster on some systems than calling
/// std::sin, and std::cos separately.
template <typename T, typename = std::enable_if_t<std::is_arithmetic<T>::value>>
SinCos_t<T> sincos(T angle) {
	T s, c;
#ifdef M7_HAVE_SINCOS_FUNCTION
	if (std::is_same<T, float>::value) {
		::sincosf(angle, &s, &c);
		return {s, c};
	}
	if (std::is_same<T, double>::value) {
		::sincos(angle, &s, &c);
		return {s, c};
	}
	if (std::is_same<T, long double>::value) {
		::sincosl(angle, &s, &c);
		return {s, c};
	}
#endif
	s = std::sin(angle);
	c = std::cos(angle);
	return {s, c};
}

}  // namespace m
}  // namespace m7
