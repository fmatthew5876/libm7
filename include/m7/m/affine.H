#pragma once
#include <cstddef>
#include <m7/m/mat.H>
#include <m7/m/vec.H>

namespace m7 {
namespace m {

template <typename T, size_t N>
struct Affine;

template <typename T>
using Affine2 = Affine<T, 2>;
template <typename T>
using Affine3 = Affine<T, 3>;

using Affine2f = Affine2<float>;
using Affine2d = Affine2<double>;
using Affine3f = Affine3<float>;
using Affine3d = Affine3<double>;

template <typename T, size_t N>
struct AffineBaseData {
	AffineBaseData() : transform(Mat<T, N>::ident()), translate(0) {}
	union {
		std::array<T, N * N + N> raw_elems;
		struct {
			Mat<T, N> transform;
			Vec<T, N> translate;
		};
	};
};

/// Represents an affine transformation which can be applied to a Vec<T,N>.
template <typename T, size_t N>
struct Affine : public AffineBaseData<T, N> {
	using ScalarT = T;
	static constexpr size_t kNumElements = N * N + N;

	constexpr Affine() = default;

	Mat<T, N + 1> toMatrix() const {
		Mat<T, N + 1> m;
		for (size_t i = 0; i < N; ++i) {
			for (size_t j = 0; j < N; ++j) {
				m[i][j] = this->transform[i][j];
			}
			m[i][N] = 0;
		}
		for (size_t i = 0; i < N; ++i) {
			m[N][i] = this->translate[i];
		}
		m[N][N] = 1;
		return m;
	}
};

/// Apply an affine transformation next to an affine transformation orig.
/// Essentially the same as next.toMat() * orig.toMat().
template <typename T, size_t N>
Affine<T, N> transform(const Affine<T, N>& orig, const Affine<T, N>& next) {
	Affine<T, N> res;
	res.transform = next.transform * orig.transform;
	for (size_t i = 0; i < N; ++i) {
		res.translate[i] =
		    dot(orig.translate.xyz, next.transform.row(i)) +
		    next.traslate[i];
	}
	return res;
}

/// Apply an affine transformation to v.
template <typename T, size_t N>
Vec<T, N> transform(const Vec<T, N>& v, const Affine<T, N>& a) {
	return a.transform * v + a.translate;
}

}  // namespace m
}  // namespace m7
