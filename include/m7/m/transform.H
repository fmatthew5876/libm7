#pragma once
#include <m7/m/mat.H>

namespace m7 {
namespace m {

/// Create a matrix which scales vector coordinates by s.
template <typename T, size_t N>
Mat<T, N> makeScaleMatrix(Vec<T, N> s) {
	Mat<T, N> m;
	for (size_t i = 0; i < N; ++i) {
		m[i][i] = s[i];
	}
	return m;
}

/// Create a 2d rotation matrix on angle (radians).
template <typename T>
Mat2<T> make2dRotationMatrix(T angle) {
	T s, c;
	sincos(angle, s, c);

	Mat2<T> m;
	m[0][0] = c;
	m[0][1] = -s;
	m[1][0] = s;
	m[1][1] = c;
	return m;
}

/// Create a 3d rotation matrix on angle (radians) around unit axis.
/// \pre len(axis) == 1.
template <typename T>
Mat3<T> make3dRotationMatrix(T angle, Vec3<T> axis) {
	auto x = axis.x;
	auto y = axis.y;
	auto z = axis.z;
	T s, c;
	sincos(angle, s, c);

	Mat3<T> m;

	m[0][0] = x * x * (1 - c) + c;
	m[0][1] = x * y * (1 - c) + z * s;
	m[0][2] = x * z * (1 - c) - y * s;

	m[1][0] = y * x * (1 - c) - z * s;
	m[1][1] = y * y * (1 - c) + c;
	m[1][2] = z * y * (1 - c) - x * s;

	m[2][0] = z * x * (1 - c) + y * s;
	m[2][1] = y * z * (1 - c) - x * s;
	m[2][2] = z * z * (1 - c) + c;
	return m;
}

/// Create a 3d rotation matrix on angle (radians) around X axis.
template <typename T>
Mat3<T> make3dRotationMatrixX(T angle) {
	T s, c;
	sincos(angle, s, c);

	auto m = Mat3<T>::ident();
	m[1][1] = c;
	m[1][2] = s;

	m[2][1] = -s;
	m[2][2] = c;

	return m;
}

/// Create a 3d rotation matrix on angle (radians) around Y axis.
template <typename T>
Mat3<T> make3dRotationMatrixY(T angle) {
	T s, c;
	sincos(angle, s, c);

	auto m = Mat3<T>::ident();
	m[0][0] = c;
	m[0][2] = -s;

	m[2][0] = s;
	m[2][2] = c;

	return m;
}

/// Create a 3d rotation matrix on angle (radians) around Z axis.
template <typename T>
Mat3<T> make3dRotationMatrixZ(T angle) {
	T s, c;
	sincos(angle, s, c);

	auto m = Mat3<T>::ident();
	m[0][0] = c;
	m[0][1] = s;

	m[1][0] = -s;
	m[1][1] = c;

	return m;
}

/// Create a 2d shear matrix with shear factor k.x and k.y.
template <typename T>
Mat2<T> makeShearMatrix(Vec2<T> k) {
	Mat2<T> m;
	m[0][0] = 1;
	m[0][1] = k.y;
	m[1][0] = 1;
	m[1][1] = k.x;
	return m;
}

/// Create a 3d shear matrix with shear kx, ky, and kz.
/// \remark kx.x, ky.y, and kz.z are not used.
template <typename T>
Mat3<T> makeShearMatrix(Vec3<T> kx, Vec3<T> ky, Vec3<T> kz) {
	Mat3<T> m;

	m[0][0] = 1;
	m[0][1] = kx.y;
	m[0][2] = kx.z;

	m[1][0] = ky.x;
	m[1][1] = 1;
	m[1][2] = ky.z;

	m[2][0] = kz.x;
	m[2][1] = kz.y;
	m[2][2] = 1;
	return m;
}

/// Creates a matrix which can translate a point.
template <typename T, size_t N>
Mat<T, N + 1> makeTranslationMatrix(const Vec<T, N>& t) {
	auto m = Mat<T, N + 1>::ident();
	for (size_t i = 0; i < N; ++i) {
		m[N][i] = t[i];
	}
	return m;
}

/// Create a matrix which reflects 2d points across a line which crosses zero.
/// \param line a unit vector in the direction of the line.
/// \pre len(line) == 1.
template <typename T>
Mat2<T> makeLineZeroReflectionMatrix(const Vec2<T>& line) {
	auto x = line.x;
	auto y = line.y;

	Mat2<T> m;
	m[0][0] = (x * x - y * y);
	m[0][1] = (T(2) * x * y);
	m[1][0] = m[0][1];
	m[1][1] = -m[0][0];

	return m;
}

/// Create a matrix which reflects 3d points across the plane ax + by + cz = 0.
/// \param plane Represents the plane coefficients a, b, and c.
template <typename T>
Mat3<T> makePlaneZeroReflectionMatrix(const Vec3<T>& plane) {
	auto a = plane.x;
	auto b = plane.y;
	auto c = plane.z;
	Mat3<T> m;

	m[0][0] = T(1) - T(2) * a * a;
	m[0][1] = -T(2) * a * b;
	m[0][2] = -T(2) * a * c;

	m[1][0] = -T(2) * a * b;
	m[1][1] = T(1) - T(2) * b * b;
	m[1][2] = -T(2) * b * c;

	m[2][0] = -T(2) * a * c;
	m[2][1] = -T(2) * b * c;
	m[2][2] = T(1) - T(2) * c * c;

	return m;
}

template <typename T>
Mat4<T> makeLookAt(const Vec3<T>& eye, const Vec3<T>& center,
		   const Vec3<T>& up) {}

template <typename T>
Mat4<T> makePickMatrix(const Vec2<T>& center, const Vec2<T>& delta,
		       const Vec4i& viewport) {}

/// Rotate a 2d vector by angle.
template <typename T>
Vec2<T> rotate(const Vec2<T>& v, T angle) {
	return makeRotationMatrix(angle) * v;
}

/// Rotate a 3d vector by the given angle about axis unit vector.
/// \pre len(axis) == 1
template <typename T>
Vec3<T> rotate(const Vec3<T>& v, T angle, const Vec3<T>& axis) {
	makeRotationMatrix(angle, axis) * v;
}

/// rotate a 3d vector by the given angle about the x axis.
/// \pre len(axis) == 1
template <typename T>
Vec3<T> rotateX(const Vec3<T>& v, T angle) {
	return rotate(v, angle, Vec3<T>({{1, 0, 0}}));
}

/// rotate a 3d vector by the given angle about the y axis.
/// \pre len(axis) == 1
template <typename T>
Vec3<T> rotateY(const Vec3<T>& v, T angle) {
	return rotate(v, angle, Vec3<T>({{0, 1, 0}}));
}

/// rotate a 3d vector by the given angle about the z axis.
/// \pre len(axis) == 1
template <typename T>
Vec3<T> rotateZ(const Vec3<T>& v, T angle) {
	return rotate(v, angle, Vec3<T>({{0, 0, 1}}));
}

/// Scale a vector.
template <typename T, size_t N>
Vec<T, N> scale(const Vec<T, N>& v, const Vec<T, N>& s) {
	return cw_mul(v, s);
}

/// Scale a vector by a constant.
template <typename T, size_t N>
Vec<T, N> scale(const Vec<T, N>& v, typename Vec<T, N>::ScalarT s) {
	return cw_mul(v, s);
}

/// Translate a vector.
template <typename T, size_t N>
Vec<T, N> translate(const Vec<T, N>& v, const Vec<T, N>& t) {
	return cw_add(v, t);
}

/// Shear a vector.
template <typename T, size_t N>
Vec2<T> shear(const Vec2<T>& v, const Vec2<T>& s) {
	return makeShearMatrix(s) * v;
}

/// Shear a vector.
template <typename T>
Vec3<T> makeShearMatrix(Vec3<T> v, Vec3<T> kx, Vec3<T> ky, Vec3<T> kz) {
	makeShearMatrix(kx, ky, kz) * v;
}

/// Reflect a 3d vector through a line crossing zero.
/// \param line a unit vector in the direction of the line.
/// \pre len(line) == 1
template <typename T>
Vec2<T> reflectLineZero(const Vec2<T>& v, const Vec2<T>& line) {
	return makeLineZeroReflectionMatrix(line) * v;
}

/// Reflect a 3d vector through the plane ax + by + cz = 0.
/// \param plane Represents the plane coefficients a, b, and c.
template <typename T>
Vec3<T> reflectPlaneZero(const Vec3<T>& v, const Vec3<T>& plane) {
	return makePlaneZeroReflectionMatrix(plane) * v;
}

template <typename T>
Vec3<T> project(const Vec3<T>& obj, const Mat4<T>& modelview,
		const Mat4<T>& projection, const Vec4i& viewport) {
	Vec4<T> win = projection * modelview * Vec4<T>(obj, 1);
	win[0] = viewport[0] + viewport[2] * (win[0] + 1) / T(2.0);
	win[1] = viewport[1] + viewport[3] * (win[1] + 1) / T(2.0);
	win[2] = (win[2] + 1) / T(2.0);
	return win.xyz;
}

template <typename T>
Vec3<T> unProject(const Vec3<T>& win, const Mat4<T>& modelview,
		  const Mat4<T>& projection, const Vec4i& viewport) {
	Vec4<T> obj;
	obj[0] = ((T(2.0) * (win[0] - viewport[0])) / viewport[2]) - 1;
	obj[1] = ((T(2.0) * (win[1] - viewport[1])) / viewport[3]) - 1;
	obj[2] = T(2.0) * win[2] - 1;
	obj[3] = 1;
	obj = inverse(projection * modelview) * obj;
	return obj.xyz;
}

}  // namespace m
}  // namespace m7
