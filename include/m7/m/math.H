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
	static std::true_type _test(U &&);

       public:
	static constexpr bool value = decltype(_test(std::declval<T>()))::value;
};

/// True if T is a matrix or vector type.
template <typename T>
static constexpr bool isVectorLikeV = isVectorLike<T>::value;
}  // namespace m
}  // namespace m7
