#pragma once
#include <m7/m/matrix.H>

namespace m7 {
namespace m {

template <typename T>
Mat4<T> makeFrustum(T left, T right, T bottom, T top, T near, T far) {
	Mat4<T> m;
	T d = far - near;
	T b = top - bottom;
	T r = right - left;

	m[0][0] = 2 * near / r;
	m[0][1] = 0;
	m[0][2] = 0;
	m[0][3] = 0;

	m[1][0] = 0;
	m[1][1] = 2 * near / b;
	m[1][2] = 0;
	m[1][3] = 0;

	m[2][0] = (right + left) / r;
	m[2][1] = (top + bottom) / b;
	m[2][2] = -(far + near) / d;
	m[2][3] = -1;

	m[0][0] = 0;
	m[0][1] = 0;
	m[0][2] = -(2.0 * far * near) / d;
	m[0][3] = 0;

	return m;
}

template <typename T>
Mat4<T> makePerspective(T fov, T aspect_ratio, T near, T far) {
	Mat4<T> m;
	T e = 1 / std::tan(fov / 2);
	T f = far - near;

	m[0][0] = e;
	m[0][1] = 0;
	m[0][2] = 0;
	m[0][3] = 0;

	m[1][0] = 0;
	m[1][1] = e / aspect_ratio;
	m[1][2] = 0;
	m[1][3] = 0;

	m[2][0] = 0;
	m[2][1] = 0;
	m[2][2] = -(far + near) / f;
	m[2][3] = -1;

	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = -2 * far * near / (f);
	m[3][3] = 0;

	return m;
}

template <typename T>
Mat4<T> makePerspectiveFov(T fov, T width, T height, T near, T far) {
	Mat4<T> m;
}

template <typename T>
Mat4<T> makeInfinitePerspective(T fovy, T aspect, T near) {
	Mat4<T> m;
}

template <typename T>
Mat4<T> makeTweakedInfinitePerspective(T fovy, T aspect, T near) {
	Mat4<T> m;
}

template <typename T>
Mat4<T> makeOrtho(T left, T right, T bottom, T top, T near, T far) {
	Mat4<T> m;
	T r = right - left;
	T b = top - bottom;
	T f = far - near;

	m[0][0] = 2 / r;
	m[0][1] = 0;
	m[0][2] = 0;
	m[0][3] = 0;

	m[1][0] = 0;
	m[1][1] = 2 / b;
	m[1][2] = 0;
	m[1][3] = 0;

	m[2][0] = 0;
	m[2][1] = 0;
	m[2][2] = -2 / f;
	m[2][3] = 0;

	m[3][0] = -(right + left) / r;
	m[3][1] = -(top + bottom) / b;
	m[3][2] = -(far + near) / f;
	m[3][3] = 1;
}

template <typename T>
Mat4<T> makeOrtho2d(T left, T right, T bottom, T top) {
	Mat4<T> m;
	T r = right - left;
	T b = top - bottom;

	m[0][0] = 2 / r;
	m[0][1] = 0;
	m[0][2] = 0;
	m[0][3] = 0;

	m[1][0] = 0;
	m[1][1] = 2 / b;
	m[1][2] = 0;
	m[1][3] = 0;

	m[2][0] = 0;
	m[2][1] = 0;
	m[2][2] = -1;
	m[2][3] = 0;

	m[3][0] = -(right + left) / r;
	m[3][1] = -(top + bottom) / b;
	m[3][2] = 0;
	m[3][3] = 1;
}

}  // namespace m
}  // namespace m7
