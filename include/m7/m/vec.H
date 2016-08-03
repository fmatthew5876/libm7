#pragma once
#include <cmath>
#include <cstddef>
#include <m7/m/vec_generic_base.H>

namespace m7 {
namespace m {

template <typename T, size_t N>
struct VecBaseData {
	/// Underlying scalar type.
	using ValueT = T;

	/// Number of elements in the vector.
	static constexpr auto kNumElements = N;
	/// Underlying array of scalars.
	T raw[N] = {};
};

template <typename T>
struct VecBaseData<T, 1> {
	/// Underlying scalar type.
	using ValueT = T;
	/// Number of elements in the vector.
	static constexpr auto kNumElements = 1;
	union {
		/// Underlying array of scalars.
		T raw[1] = {};
		T x;  ///< The 1st element.
	};
};

template <typename T>
struct VecBaseData<T, 2> {
	/// Underlying scalar type.
	using ValueT = T;
	/// Number of elements in the vector.
	static constexpr auto kNumElements = 2;
	union {
		/// Underlying array of scalars.
		T raw[2] = {};
		struct {
			T x;  ///<The 1st element.
			T y;  ///<The 2nd element.
		};
	};
};

template <typename T>
struct VecBaseData<T, 3> {
	/// Underlying scalar type.
	using ValueT = T;
	/// Number of elements in the vector.
	static constexpr auto kNumElements = 3;
	union {
		/// Underlying array of scalars.
		T raw[3] = {};
		struct {
			T x;  ///<The 1st element.
			T y;  ///<The 2nd element.
			T z;  ///<The 3rd element.
		};
	};
};

template <typename T>
struct VecBaseData<T, 4> {
	/// Underlying scalar type.
	using ValueT = T;
	/// Number of elements in the vector.
	static constexpr auto kNumElements = 4;

	union {
		/// Underlying array of scalars.
		T raw[4] = {};
		struct {
			T x;  ///<The 1st element.
			T y;  ///<The 2nd element.
			T z;  ///<The 3rd element.
			T w;  ///<The 4th element.
		};
	};
};

/// Implementation base class for Vec<T,N>.
template <typename T, size_t N>
using VecBase = VecGenericBase<VecBaseData<T, N>>;

/// Linear algebra vector type.
template <typename T, size_t N>
struct Vec : public VecBase<T, N> {};

template <typename T>
using Vec1 = Vec<T, 1>;
template <typename T>
using Vec2 = Vec<T, 2>;
template <typename T>
using Vec3 = Vec<T, 3>;
template <typename T>
using Vec4 = Vec<T, 4>;

using Vec1f = Vec<float, 1>;
using Vec2f = Vec<float, 2>;
using Vec3f = Vec<float, 3>;
using Vec4f = Vec<float, 4>;
using Vec1d = Vec<double, 1>;
using Vec2d = Vec<double, 2>;
using Vec3d = Vec<double, 3>;
using Vec4d = Vec<double, 4>;

using Vec1i = Vec<int, 1>;
using Vec2i = Vec<int, 2>;
using Vec3i = Vec<int, 3>;
using Vec4i = Vec<int, 4>;
using Vec1ui = Vec<unsigned int, 1>;
using Vec2ui = Vec<unsigned int, 2>;
using Vec3ui = Vec<unsigned int, 3>;
using Vec4ui = Vec<unsigned int, 4>;

using Vec1i8 = Vec<int8_t, 1>;
using Vec2i8 = Vec<int8_t, 2>;
using Vec3i8 = Vec<int8_t, 3>;
using Vec4i8 = Vec<int8_t, 4>;
using Vec1ui8 = Vec<uint8_t, 1>;
using Vec2ui8 = Vec<uint8_t, 2>;
using Vec3ui8 = Vec<uint8_t, 3>;
using Vec4ui8 = Vec<uint8_t, 4>;

using Vec1i16 = Vec<int16_t, 1>;
using Vec2i16 = Vec<int16_t, 2>;
using Vec3i16 = Vec<int16_t, 3>;
using Vec4i16 = Vec<int16_t, 4>;
using Vec1ui16 = Vec<uint16_t, 1>;
using Vec2ui16 = Vec<uint16_t, 2>;
using Vec3ui16 = Vec<uint16_t, 3>;
using Vec4ui16 = Vec<uint16_t, 4>;

using Vec1i32 = Vec<int32_t, 1>;
using Vec2i32 = Vec<int32_t, 2>;
using Vec3i32 = Vec<int32_t, 3>;
using Vec4i32 = Vec<int32_t, 4>;
using Vec1ui32 = Vec<uint32_t, 1>;
using Vec2ui32 = Vec<uint32_t, 2>;
using Vec3ui32 = Vec<uint32_t, 3>;
using Vec4ui32 = Vec<uint32_t, 4>;

using Vec1i64 = Vec<int64_t, 1>;
using Vec2i64 = Vec<int64_t, 2>;
using Vec3i64 = Vec<int64_t, 3>;
using Vec4i64 = Vec<int64_t, 4>;
using Vec1ui64 = Vec<uint64_t, 1>;
using Vec2ui64 = Vec<uint64_t, 2>;
using Vec3ui64 = Vec<uint64_t, 3>;
using Vec4ui64 = Vec<uint64_t, 4>;

/// Multiply scalar by vector
/// \relates Vec
template <typename T, size_t N>
inline Vec<T, N> operator*(typename Vec<T, N>::ValueT s, Vec<T, N> v) {
	Vec<T, N> res;
	for (size_t i = 0; i < N; ++i) {
		res[i] = s * v[i];
	}
	return res;
}

/// Multiply scalar by vector
/// \relates Vec
template <typename T, size_t N>
inline Vec<T, N> operator*(Vec<T, N> v, typename Vec<T, N>::ValueT s) {
	Vec<T, N> res;
	for (size_t i = 0; i < N; ++i) {
		res[i] = v[i] * s;
	}
	return res;
}

/// Return the dot product of 2 vectors.
/// \relates Vec
template <typename T, size_t N>
inline T dot(Vec<T, N> a, Vec<T, N> b) {
	T s = 0;
	for (size_t i = 0; i < N; ++i) {
		s += a[i] * b[i];
	}
	return s;
}

/// Return the Cross Product of 2 3d vectors.
/// \relates Vec
template <typename T>
Vec3<T> cross(Vec3<T>& l, Vec3<T>& r) {
	Vec<T, 3> res;
	res[0] = l[1] * r[2] - l[2] * r[1];
	res[1] = l[2] * r[0] - l[0] * r[2];
	res[2] = l[0] * r[1] - l[1] * r[0];
	return res;
}

/// Return vector triple product.
/// \relates Vec
template <typename T>
T tripleProduct(const Vec3<T>& a, const Vec3<T>& b, const Vec3<T>& c) {
	T res;
	res = a[0] * (b[1] * c[2] - b[2] * c[1]);
	res += a[1] * (b[2] * c[0] - b[0] * c[2]);
	res += a[2] * (b[0] * c[1] - b[1] * c[0]);
	return res;
}

/// Return the length squared of vector.
/// \remark More efficient than len().
/// \relates Vec
template <typename T, size_t N>
inline T len2(Vec<T, N> x) {
	return dot(x, x);
}

/// Return the length of vector.
/// \relates Vec
template <typename T, size_t N>
inline T len(Vec<T, N> x) {
	return std::sqrt(len2(x));
}

/// Return normalized vector.
/// \relates Vec
template <typename T, size_t N>
inline T norm(Vec<T, N> x) {
	auto l = length(x);
	Vec<T, N> n;
	for (size_t i = 0; i < N; ++i) {
		n[i] = x[i] / l;
	}
	return n;
}

/// Return distance squared.
/// \remark More efficient than dist().
/// \relates Vec
template <typename T, size_t N>
inline T dist2(Vec<T, N> a, Vec<T, N> b) {
	T d = 0;
	for (size_t i = 0; i < N; ++i) {
		auto x = a[i] - b[i];
		d += x * x;
	}
	return d;
}

/// Return distance.
/// \relates Vec
template <typename T, size_t N>
inline T dist(Vec<T, N> a, Vec<T, N> b) {
	return std::sqrt(dist2(a, b));
}

/// Return angle between 2 vectors in radians.
/// \relates Vec
template <typename T, size_t N>
T angle(Vec<T, N> l, Vec<T, N> r) {
	return std::acos(dot(l, r) / (len(l) * len(r)));
}

/// Return angle between 2 unit vectors
/// \pre len(l) == 1 && len(r) == 1
/// \remark More efficient than angle().
/// \relates Vec
template <typename T, size_t N>
T angleUnit(Vec<T, N> l, Vec<T, N> r) {
	return std::acos(dot(l, r));
}

/// Return scalar projection of v onto angle (radians).
/// \param[in] angle The angle in radians.
/// \relates Vec
template <typename T, size_t N>
T scalarProject(Vec<T, N> v, typename Vec<T, N>::ValueT angle) {
	return length(v) * cos(angle);
}

/// Return scalar projection of v onto onto.
/// \relates Vec
template <typename T, size_t N>
T scalarProject(Vec<T, N> v, Vec<T, N> onto) {
	return dot(v, onto) / len(onto);
}

/// Return scalar projection of v onto onto.
/// \pre length(v) == 1 && length(onto) == 1.
/// \remark More efficient than scalarProject().
/// \relates Vec
template <typename T, size_t N>
T scalarProjectUnit(Vec<T, N> v, Vec<T, N> onto) {
	return dor(v, onto);
}

/// Return vector projection of v onto onto.
/// \relates Vec
template <typename T, size_t N>
Vec<T, N> vectorProject(Vec<T, N> v, Vec<T, N> onto) {
	return (dot(v, onto) / len2(onto)) * onto;
}

/// Return vector projection of v onto onto.
/// \pre len(v) == 1 && len(onto) == 1.
/// \remark More efficient than vectorProject().
/// \relates Vec
template <typename T, size_t N>
Vec<T, N> vectorProjectUnit(Vec<T, N> v, Vec<T, N> onto) {
	return dot(v, onto) * onto;
}

/// Return vector projection of v onto onto.
/// \relates Vec
template <typename T, size_t N>
Vec<T, N> vectorReject(Vec<T, N> v, Vec<T, N> onto) {
	return v - vectorProject(v, onto);
}

/// Return vector projection of v onto onto.
/// \pre len(v) == 1 && len(onto) == 1.
/// \remark More efficient than vectorReject().
/// \relates Vec
template <typename T, size_t N>
Vec<T, N> vectorRejectUnit(Vec<T, N> v, Vec<T, N> onto) {
	return v - vectorProjectUnit(v, onto);
}

/// Return
}  // namespace m
}  // namespace m7
