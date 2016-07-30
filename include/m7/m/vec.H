#pragma once
#include <cstddef>
#include <m7/m/vec_generic_base.H>

namespace m7 {
namespace m {

template <typename T, size_t N>
struct VecBaseData {
	using ValueT = T;
	static constexpr auto kNumElements = N;
	T raw[N] = {};
};

template <typename T>
struct VecBaseData<T, 1> {
	using ValueT = T;
	static constexpr auto kNumElements = 1;
	union {
		T raw[1] = {};
		T x;
	};
};

template <typename T>
struct VecBaseData<T, 2> {
	using ValueT = T;
	static constexpr auto kNumElements = 2;
	union {
		T raw[2] = {};
		struct {
			T x;
			T y;
		};
	};
};

template <typename T>
struct VecBaseData<T, 3> {
	using ValueT = T;
	static constexpr auto kNumElements = 3;
	union {
		T raw[3] = {};
		struct {
			T x;
			T y;
			T z;
		};
	};
};

template <typename T>
struct VecBaseData<T, 4> {
	using ValueT = T;
	static constexpr auto kNumElements = 4;

	union {
		T raw[4] = {};
		struct {
			T x;
			T y;
			T z;
			T w;
		};
	};
};

template <typename T, size_t N>
using VecBase = VecGenericBase<VecBaseData<T, N>>;

template <typename T, size_t N>
struct Vec : public VecBase<T, N> {};

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

}  // namespace m
}  // namespace m7
