#pragma once
#include <cmath>
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

#if 0
inline void sincos(float angle, float& s, float& c) {
	::sincosf(angle, &s, &c);
}
inline void sincos(double angle, double& s, double& c) {
	::sincos(angle, &s, &c);
}
#else
void sincos(float angle, float& s, float& c) {
	s = sin(angle);
	c = cos(angle);
}
void sincos(double angle, double& s, double& c) {
	s = sin(angle);
	c = cos(angle);
}

#endif

}  // namespace m
}  // namespace m7
