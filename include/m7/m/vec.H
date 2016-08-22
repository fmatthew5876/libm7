#pragma once
#include <cmath>
#include <cstddef>
#include <iterator>
#include <m7/assert.H>
#include <m7/m/cwise.H>

namespace m7 {
namespace m {

template <typename T, size_t N>
struct Vec;

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

template <typename T, size_t N>
struct VecBaseData {
	VecBaseData() : raw_elems{} {}
	union {
		/// Underlying storage as a flat array.
		std::array<T, N> raw_elems;
		Vec4<T> xyzw;  ///< 1st, 2nd, 3rd, and 4th elements.
		struct {
			Vec3<T> xyz;  ///< 1st, 2nd, and 3rd elements.
			T w;	  ///< 4th element.
		};
		struct {
			Vec2<T> xy;  ///< 1st and 2nd elements.
			union {
				T z;	 ///< 3rd element.
				Vec2<T> zw;  ///< 3rd and 4th elements.
			};
		};
		struct {
			T x;  ///< 1st element.
			union {
				T y;	  ///< 2nd element.
				Vec2<T> yz;   ///< 2nd and 3rd elements.
				Vec3<T> yzw;  ///< 2nd, 3rd, and 4th elements.
			};
		};
	};
};

template <typename T>
struct VecBaseData<T, 4> {
	VecBaseData() : raw_elems{} {}
	union {
		/// Underlying storage as a flat array.
		std::array<T, 4> raw_elems = {};
		struct {
			Vec3<T> xyz;  ///< 1st, 2nd, and 3rd elements.
			T w;	  ///< 4th element.
		};
		struct {
			Vec2<T> xy;  ///< 1st and 2nd elements.
			union {
				T z;	 ///< 3rd element.
				Vec2<T> zw;  ///< 3rd and 4th elements.
			};
		};
		struct {
			T x;  ///< 1st element.
			union {
				T y;	  ///< 2nd element.
				Vec2<T> yz;   ///< 2nd and 3rd elements.
				Vec3<T> yzw;  ///< 2nd, 3rd, and 4th elements.
			};
		};
	};
};

template <typename T>
struct VecBaseData<T, 3> {
	VecBaseData() : raw_elems{} {}
	union {
		/// Underlying storage as a flat array.
		std::array<T, 3> raw_elems = {};
		struct {
			Vec2<T> xy;  ///< 1st and 2nd elements.
			T z;	 ///< 3rd element.
		};
		struct {
			T x;  ///< 1st element.
			union {
				T y;	 ///< 2nd element.
				Vec2<T> yz;  ///< 2nd and 3rd elements.
			};
		};
	};
};

template <typename T>
struct VecBaseData<T, 2> {
	VecBaseData() : raw_elems{} {}
	union {
		/// Underlying storage as a flat array.
		std::array<T, 2> raw_elems = {};
		struct {
			T x;  ///< 1st element.
			T y;  ///< 2nd element.
		};
	};
};

template <typename T>
struct VecBaseData<T, 1> {
	VecBaseData() : raw_elems{} {}
	union {
		/// Underlying storage as a flat array.
		std::array<T, 1> raw_elems = {};
		T x;  ///< 1st element.
	};
};

/// Linear algebra vector type.
template <typename T, size_t N>
struct Vec : public VecBaseData<T, N> {
	/// The underlying scalar type T.
	using ScalarT = T;

	/// The type representing a vector of T.
	using VecT = Vec<T, N>;

	/// The number of underlying scalar elements.
	static constexpr auto kNumElements = N;

	/// Iterator type.
	using IteratorT = ScalarT*;
	/// Const Iterator type.
	using ConstIteratorT = const ScalarT*;
	/// Reverse Iterator type.
	using ReverseIteratorT = std::reverse_iterator<IteratorT>;
	/// Const Reverse Iterator type.
	using ConstReverseIteratorT = std::reverse_iterator<ConstIteratorT>;

	/// Default Zero initialize..
	constexpr Vec() = default;

	/// Initialize all elements with scalar s.
	constexpr explicit Vec(ScalarT s) { fill(s); }

	/// Initialize each element individually using the given array.
	constexpr explicit Vec(const std::array<T, kNumElements>& scalars) {
		this->raw_elems = scalars;
	}

	/// Return a pointer to the first column.
	ScalarT* data() { return this->raw_elems.data(); }
	/// Return a pointer to the first column.
	const ScalarT* data() const { return this->raw_elems.data(); }

	/// Return a reference to the i'th column.
	/// \pre i < size()
	ScalarT& operator[](size_t i) {
		M7_ASSERT(i < size());
		return this->raw_elems[i];
	}

	/// Return a reference to the i'th column.
	/// \pre i < size()
	const ScalarT& operator[](size_t i) const {
		M7_ASSERT(i < size());
		return this->raw_elems[i];
	}

	/// The number of elements.
	constexpr static size_t sizeElements() { return kNumElements; }
	/// The number of elements.
	constexpr static size_t size() { return sizeElements(); }

	/// Iterator to the beginning.
	IteratorT begin() { return data(); }
	/// Iterator to the end.
	IteratorT end() { return data() + size(); }

	/// Iterator to the beginning.
	ConstIteratorT begin() const { return data(); }
	/// Iterator to the end.
	ConstIteratorT end() const { return data() + size(); }

	/// Iterator to the beginning.
	ConstIteratorT cbegin() const { return begin(); }
	/// Iterator to the end.
	ConstIteratorT cend() const { return end(); }

	/// Reverse Iterator to the end.
	ReverseIteratorT rbegin() { return ReverseIteratorT(end()); }
	/// Reverse Iterator to the beginning.
	ReverseIteratorT rend() { return ReverseIteratorT(begin()); }

	/// Reverse Iterator to the end.
	ConstReverseIteratorT rbegin() const {
		return ConstReverseIteratorT(end());
	}
	/// Reverse Iterator to the beginning.
	ConstReverseIteratorT rend() const {
		return ConstReverseIteratorT(begin());
	}

	/// Reverse Iterator to the end.
	ConstReverseIteratorT crbegin() const { return rbegin(); }
	/// Reverse Iterator to the beginning.
	ConstReverseIteratorT crend() const { return rend(); }

	/// Returns an array reference which references the scalar
	/// elements of this.
	std::array<ScalarT, kNumElements>& elems() { return this->raw_elems; }
	/// Returns an array reference which references the scalar
	/// elements of this.
	const std::array<ScalarT, kNumElements>& elems() const {
		return this->raw_elems;
	}

	/// Return a reference to the i'th element.
	/// \pre i < sizeElements()
	ScalarT& elem(size_t i) {
		M7_ASSERT(i < sizeElements());
		return this->elems()[i];
	}

	/// Return a reference to the i'th element.
	/// \pre i < sizeElements()
	const ScalarT& elem(size_t i) const {
		M7_ASSERT(i < sizeElements());
		return this->elems()[i];
	}

	/// Set all elements to s.
	constexpr void fill(ScalarT s) {
		for (auto& e : this->raw_elems) e = s;
	}
};

/// Add 2 vectors
/// \relates Vec
template <typename T, size_t N>
inline Vec<T, N> operator+(const Vec<T, N>& x, const Vec<T, N>& y) {
	return cw_add(x, y);
}

/// Subtract 2 vectors
/// \relates Vec
template <typename T, size_t N>
inline Vec<T, N> operator-(const Vec<T, N>& x, const Vec<T, N>& y) {
	return cw_sub(x, y);
}

/// Multiply scalar by vector
/// \relates Vec
template <typename T, size_t N>
inline Vec<T, N> operator*(typename Vec<T, N>::ScalarT s, const Vec<T, N>& v) {
	return cw_mul(s, v);
}

/// Multiply scalar by vector
/// \relates Vec
template <typename T, size_t N>
inline Vec<T, N> operator*(const Vec<T, N>& v, typename Vec<T, N>::ScalarT s) {
	return cw_mul(v, s);
}

/// Return the dot product of 2 vectors.
/// \relates Vec
template <typename T, size_t N>
inline T dot(const Vec<T, N>& a, const Vec<T, N>& b) {
	T s = 0;
	for (size_t i = 0; i < N; ++i) {
		s += a[i] * b[i];
	}
	return s;
}

/// Return the Cross Product of 2 3d vectors.
/// \relates Vec
template <typename T>
Vec3<T> cross(const Vec3<T>& l, const Vec3<T>& r) {
	Vec3<T> res;
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
inline T len2(const Vec<T, N>& x) {
	return dot(x, x);
}

/// Return the length of vector.
/// \relates Vec
template <typename T, size_t N>
inline T len(const Vec<T, N>& x) {
	return std::sqrt(len2(x));
}

/// Return normalized vector.
/// \relates Vec
template <typename T, size_t N>
inline T norm(const Vec<T, N>& x) {
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
inline T dist2(const Vec<T, N>& a, const Vec<T, N>& b) {
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
inline T dist(const Vec<T, N>& a, const Vec<T, N>& b) {
	return std::sqrt(dist2(a, b));
}

/// Return angle between 2 vectors in radians.
/// \relates Vec
template <typename T, size_t N>
T angle(const Vec<T, N>& l, const Vec<T, N>& r) {
	return std::acos(dot(l, r) / (len(l) * len(r)));
}

/// Return angle between 2 unit vectors
/// \pre len(l) == 1 && len(r) == 1
/// \remark More efficient than angle().
/// \relates Vec
template <typename T, size_t N>
T angleUnit(const Vec<T, N>& l, const Vec<T, N>& r) {
	return std::acos(dot(l, r));
}

/// Return scalar projection of v onto angle (radians).
/// \relates Vec
template <typename T, size_t N>
T scalarProject(const Vec<T, N>& v, typename Vec<T, N>::ScalarT angle) {
	return length(v) * cos(angle);
}

/// Return scalar projection of v onto q.
/// \relates Vec
template <typename T, size_t N>
T scalarProject(const Vec<T, N>& v, const Vec<T, N>& q) {
	return dot(v, q) / len(q);
}

/// Return scalar projection of v onto q.
/// \pre length(q) == 1.
/// \remark More efficient than scalarProject().
/// \relates Vec
template <typename T, size_t N>
T scalarProjectUnit(const Vec<T, N>& v, const Vec<T, N>& q) {
	return dot(v, q);
}

/// Return vector projection of v onto q.
/// \relates Vec
template <typename T, size_t N>
Vec<T, N> vectorProject(const Vec<T, N>& v, const Vec<T, N>& q) {
	return (dot(v, q) / len2(q)) * q;
}

/// Return vector projection of v onto q.
/// \pre len(q) == 1.
/// \remark More efficient than vectorProject().
/// \relates Vec
template <typename T, size_t N>
Vec<T, N> vectorProjectUnit(const Vec<T, N>& v, const Vec<T, N>& q) {
	return dot(v, q) * q;
}

/// Return vector projection of v onto q.
/// \relates Vec
template <typename T, size_t N>
Vec<T, N> vectorReject(const Vec<T, N>& v, const Vec<T, N>& q) {
	return v - vectorProject(v, q);
}

/// Return vector projection of v onto q.
/// \pre len(q) == 1.
/// \remark More efficient than vectorReject().
/// \relates Vec
template <typename T, size_t N>
Vec<T, N> vectorRejectUnit(const Vec<T, N>& v, const Vec<T, N>& q) {
	return v - vectorProjectUnit(v, q);
}

/// Return
}  // namespace m
}  // namespace m7
