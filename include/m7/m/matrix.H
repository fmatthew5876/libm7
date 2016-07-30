#pragma once
#include <cstddef>
#include <m7/m/vec.H>

namespace m7 {
namespace m {

template <typename T, size_t M, size_t N>
struct MatBaseData {
	using ValueT = T;
	static constexpr auto kNumElements = M * N;
	static constexpr auto kNumCols = M;
	static constexpr auto kNumRows = N;

	union {
		T raw[kNumElements] = {};
		struct {
			Vec<T, N> col[M];
		};
	};
};

template <typename T, size_t M, size_t N>
using MatrixBase = VecGenericBase<MatBaseData<T, M, N>>;

template <typename T, size_t M, size_t N = M>
struct Matrix : public MatrixBase<T, M, N> {};

}  // namespace m
}  // namespace m7
