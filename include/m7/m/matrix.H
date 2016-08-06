#pragma once
#include <array>
#include <cstddef>
#include <m7/assert.H>
#include <m7/m/cwise.H>
#include <m7/m/vec.H>

namespace m7 {
namespace m {

template <typename T, size_t M, size_t N>
struct Matrix;

template <typename T, size_t N>
using SqMat = Matrix<T, N, N>;

template <typename T>
using Mat1 = Matrix<T, 1, 1>;
template <typename T>
using Mat2 = Matrix<T, 2, 2>;
template <typename T>
using Mat3 = Matrix<T, 3, 3>;
template <typename T>
using Mat4 = Matrix<T, 4, 4>;

template <typename T>
using Mat11 = Matrix<T, 1, 1>;
template <typename T>
using Mat12 = Matrix<T, 1, 2>;
template <typename T>
using Mat13 = Matrix<T, 1, 3>;
template <typename T>
using Mat14 = Matrix<T, 1, 4>;

template <typename T>
using Mat21 = Matrix<T, 2, 1>;
template <typename T>
using Mat22 = Matrix<T, 2, 2>;
template <typename T>
using Mat23 = Matrix<T, 2, 3>;
template <typename T>
using Mat24 = Matrix<T, 2, 4>;

template <typename T>
using Mat31 = Matrix<T, 3, 1>;
template <typename T>
using Mat32 = Matrix<T, 3, 2>;
template <typename T>
using Mat33 = Matrix<T, 3, 3>;
template <typename T>
using Mat34 = Matrix<T, 3, 4>;

template <typename T>
using Mat41 = Matrix<T, 4, 1>;
template <typename T>
using Mat42 = Matrix<T, 4, 2>;
template <typename T>
using Mat43 = Matrix<T, 4, 3>;
template <typename T>
using Mat44 = Matrix<T, 4, 4>;

/// isSquareMatrixV type trait type.
template <typename M>
struct isSquareMatrix : public std::false_type {};
/// isSquareMatrixV type trait type.
template <typename T, size_t N>
struct isSquareMatrix<Matrix<T, N, N>> : public std::true_type {};
/// True if M is a square matrix.
template <typename M>
static constexpr auto isSquareMatrixV = isSquareMatrix<M>::value;

/// Matrix base class which stores union of data members for raw access.
template <typename T, size_t M, size_t N>
struct MatrixBaseData {
	MatrixBaseData() : raw_elems{} {}
	union {
		/// Underlying storage as a flat array.
		std::array<T, M * N> raw_elems;
		/// Underlying storage as an array of column vectors.
		std::array<Vec<T, N>, M> raw_cols;
		/// Underlying storage as a flat vector.
		Vec<T, M * N> raw_flat_vec;
	};
};

/// A linear algebra type representing an M by N matrix.
/// \tparam T the underlying scalar type.
/// \tparam M the number of columns.
/// \tparam N the number of rows.
/// \remark The underlying storage is in column-major order.
template <typename T, size_t M, size_t N>
struct Matrix : public MatrixBaseData<T, M, N> {
	/// This type.
	using MatrixT = Matrix<T, M, N>;
	/// The underlying scalar type T.
	using ScalarT = T;

	/// The type representing a vector of T.
	template <size_t VN>
	using VecT = Vec<T, VN>;

	/// The type representing a column vector.
	using ColumnT = VecT<N>;

	/// The number of columns.
	static constexpr auto kNumCols = M;
	/// The number of rows.
	static constexpr auto kNumRows = N;
	/// The number of underlying scalar elements.
	static constexpr auto kNumElements = M * N;

	/// Iterator type.
	using IteratorT = ColumnT*;
	/// Const Iterator type.
	using ConstIteratorT = const ColumnT*;
	/// Reverse Iterator type.
	using ReverseIteratorT = std::reverse_iterator<IteratorT>;
	/// Const Reverse Iterator type.
	using ConstReverseIteratorT = std::reverse_iterator<ConstIteratorT>;

	/// Returns an identity matrix.
	template <typename U = MatrixT,
		  typename = std::enable_if_t<isSquareMatrixV<U>>>
	static constexpr Matrix<T, M, N> ident();

	/// Default Zero initialize the matrix.
	constexpr Matrix() = default;

	/// Initialize all elements of the matrix with scalar s.
	constexpr explicit Matrix(ScalarT s) { fill(s); }

	/// Initialize each element individually using the given array.
	constexpr explicit Matrix(const std::array<T, kNumElements>& scalars) {
		this->raw_elems = scalars;
	}

	/// Initialize each column individually using the given array.
	constexpr explicit Matrix(
	    const std::array<ColumnT, kNumCols>& columns) {
		this->raw_cols = columns;
	}

	/// Return a pointer to the first column.
	ColumnT* data() { return this->raw_cols.data(); }
	/// Return a pointer to the first column.
	const ColumnT* data() const { return this->raw_cols.data(); }

	/// Return a reference to the i'th column.
	/// \pre i < size()
	ColumnT& operator[](size_t i) {
		M7_ASSERT(i < size());
		return this->raw_cols[i];
	}

	/// Return a reference to the i'th column.
	/// \pre i < size()
	const ColumnT& operator[](size_t i) const {
		M7_ASSERT(i < size());
		return this->raw_cols[i];
	}

	/// The number of columns.
	constexpr static size_t sizeCols() { return kNumCols; }
	/// The number of rows.
	constexpr static size_t sizeRows() { return kNumRows; }
	/// The number of elements.
	constexpr static size_t sizeElements() { return kNumElements; }
	/// The number of columns.
	constexpr static size_t size() { return sizeCols(); }

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

	/// Returns an array reference which references the columns of
	/// this.
	std::array<ColumnT, kNumCols>& cols() { return this->raw_cols; }
	/// Returns an array reference which references the columns of
	/// this.
	const std::array<ColumnT, kNumCols>& cols() const {
		return this->raw_cols;
	}

	/// Return a reference to the i'th column.
	/// \pre i < sizeCols()
	ColumnT& col(size_t i) {
		M7_ASSERT(i < size());
		return this->cols()[i];
	}
	/// Return a reference to the i'th column.
	/// \pre i < sizeCols()
	const ColumnT& col(size_t i) const {
		M7_ASSERT(i < size());
		return this->cols()[i];
	}

	/// Return a vector with the values of the i'th row.
	/// \pre i < sizeRows()
	const VecT<kNumCols> row(size_t i) const {
		M7_ASSERT(i < sizeRows());
		VecT<kNumCols> r;
		for (auto& c : cols()) r[i] = c[i];
		return r;
	}

	/// Returns an array reference which references the scalar
	/// elements of
	/// this.
	std::array<ScalarT, kNumElements>& elems() { return this->raw_elems; }
	/// Returns an array reference which references the scalar
	/// elements of
	/// this.
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

	/// Set all columns to s.
	constexpr void fill(ColumnT c) {
		for (auto& e : this->raw_cols) e = c;
	}
};

/// Returns an identity matrix.
/// \refers Matrix
template <typename T, size_t N>
constexpr SqMat<T, N> makeIdentity() {
	auto m = SqMat<T, N>(T(0));
	for (size_t i = 0; i < N; ++i) m[i][i] = T(1);
	return m;
}

/// Sets m to the identity matrix and returns it.
/// \refers Matrix
template <typename T, size_t N>
constexpr SqMat<T, N>& makeIdentity(SqMat<T, N>& m) {
	m = makeIdentity<T, N>();
	return m;
}

template <typename T, size_t M, size_t N>
template <typename, typename>
constexpr Matrix<T, M, N> Matrix<T, M, N>::ident() {
	return makeIdentity(Matrix<T, M, M>());
}

/// Add 2 matrices
/// \relates Vec
template <typename T, size_t M, size_t N>
inline Matrix<T, M, N> operator+(const Matrix<T, M, N>& x,
				 const Matrix<T, M, N>& y) {
	return cw_add(x, y);
}

/// Subtract 2 matrices
/// \relates Vec
template <typename T, size_t M, size_t N>
inline Matrix<T, M, N> operator-(const Matrix<T, M, N>& x,
				 const Matrix<T, M, N>& y) {
	return cw_sub(x, y);
}

/// Multiply scalar by matrix
/// \relates Vec
template <typename T, size_t M, size_t N>
inline Matrix<T, M, N> operator*(typename Matrix<T, M, N>::ScalarT s,
				 Matrix<T, M, N> v) {
	return cw_mul(s, v);
}

/// Multiply scalar by matrix
/// \relates Vec
template <typename T, size_t M, size_t N>
inline Matrix<T, M, N> operator*(Matrix<T, M, N> v,
				 typename Matrix<T, M, N>::ScalarT s) {
	cw_mul(v, s);
}

/// Return the determinant of m.
/// \refers Matrix
template <typename T>
inline T det(Mat2<T> m) {
	return m[0] * m[3] - m[2] * m[1];
}

/// Return the determinant of m.
/// \refers Matrix
template <typename T>
inline T det(const Mat3<T>& m) {
	T d = m[0] * m[4] * m[8];
	d += m[3] * m[7] * m[2];
	d += m[6] * m[1] * m[5];
	d -= m[6] * m[4] * m[2];
	d -= m[3] * m[1] * m[8];
	d -= m[0] * m[7] * m[5];
	return d;
}

/// Return the determinant of m.
/// \refers Matrix
template <typename T>
T det(const Mat4<T>& m) {
	return (m[0] * m[5] - m[1] * m[4]) * (m[10] * m[15] - m[11] * m[14]) -
	       (m[0] * m[9] - m[1] * m[8]) * (m[6] * m[15] - m[7] * m[14]) +
	       (m[0] * m[13] - m[1] * m[12]) * (m[6] * m[11] - m[7] * m[10]) +
	       (m[4] * m[9] - m[5] * m[8]) * (m[2] * m[15] - m[3] * m[14]) -
	       (m[4] * m[13] - m[5] * m[12]) * (m[2] * m[11] - m[3] * m[10]) +
	       (m[8] * m[13] - m[9] * m[12]) * (m[2] * m[7] - m[3] * m[6]);
}

/// Return the inverse of m.
/// \refers Matrix
template <typename T>
inline Mat2<T> inverse(Mat2<T> m) {
	auto invdet = T(1.0) / det(m);
	Mat2<T> i;
	i[0] = m[3] / invdet;
	i[1] = -m[1] / invdet;
	i[2] = -m[2] / invdet;
	i[3] = m[0] / invdet;
	return i;
}

/// Return the inverse of m.
/// \refers Matrix
template <typename T>
Mat3<T> inverse(const Mat3<T>& m) {
	Mat3<T> i;
	i[0] = m[8] * m[4] - m[5] * m[7];
	i[1] = m[7] * m[2] - m[1] * m[8];
	i[2] = m[1] * m[5] - m[4] * m[2];

	i[3] = m[6] * m[5] - m[8] * m[3];
	i[4] = m[8] * m[0] - m[2] * m[6];
	i[5] = m[3] * m[2] - m[5] * m[0];

	i[6] = m[3] * m[7] - m[6] * m[4];
	i[7] = m[6] * m[1] - m[0] * m[7];
	i[8] = m[4] * m[0] - m[1] * m[3];

	T invdet = T(1.0) / (m[0] * i[0] + m[3] * i[1] + m[6] * i[2]);

	return invdet * i;
}

/// Return the inverse of m.
/// \refers Matrix
template <typename T>
Mat4<T> inverse(const Mat4<T>& m) {
	Mat4<T> i;

	T s0 = m[0] * m[5] - m[1] * m[4];
	T s1 = m[0] * m[9] - m[1] * m[8];
	T s2 = m[0] * m[13] - m[1] * m[12];
	T s3 = m[4] * m[9] - m[5] * m[8];
	T s4 = m[4] * m[13] - m[5] * m[12];
	T s5 = m[8] * m[13] - m[9] * m[12];

	T c5 = m[10] * m[15] - m[11] * m[14];
	T c4 = m[6] * m[15] - m[7] * m[14];
	T c3 = m[6] * m[11] - m[7] * m[10];
	T c2 = m[2] * m[15] - m[3] * m[14];
	T c1 = m[2] * m[11] - m[3] * m[10];
	T c0 = m[2] * m[7] - m[3] * m[6];

	i[0] = m[5] * c5 - m[9] * c4 + m[13] * c3;
	i[1] = -m[1] * c5 + m[9] * c2 - m[13] * c1;
	i[2] = m[1] * c4 - m[5] * c2 + m[13] * c0;
	i[3] = -m[1] * c3 + m[5] * c1 - m[9] * c0;

	i[4] = -m[4] * c5 + m[8] * c4 - m[12] * c3;
	i[5] = m[0] * c5 - m[8] * c2 + m[12] * c1;
	i[6] = -m[0] * c4 + m[4] * c2 - m[12] * c0;
	i[7] = m[0] * c3 - m[4] * c1 + m[8] * c0;

	i[8] = m[7] * s5 - m[11] * s4 + m[15] * s3;
	i[9] = -m[3] * s5 + m[11] * s2 - m[15] * s1;
	i[10] = m[3] * s4 - m[7] * s2 + m[15] * s0;
	i[11] = -m[3] * s3 + m[7] * s1 - m[11] * s0;

	i[12] = -m[6] * s5 + m[10] * s4 - m[14] * s3;
	i[13] = m[2] * s5 - m[10] * s2 + m[14] * s1;
	i[14] = -m[2] * s4 + m[6] * s2 - m[14] * s0;
	i[15] = m[2] * s3 - m[6] * s1 + m[10] * s0;

	T invdet = T(1.0) /
		   (s0 * c5 - s1 * c4 + s2 * c3 + s3 * c2 - s4 * c1 + s5 * c0);

	return invdet * i;
}

/// Return the adjoint of m.
/// \refers Matrix
template <typename T>
inline Mat2<T> adjoint(Mat2<T> m) {
	return {m[3], -m[1], -m[2], m[0]};
}

/// Return the adjoint of m.
/// \refers Matrix
template <typename T>
inline Mat3<T> adjoint(Mat3<T> m) {
	static_assert(m == m, "NOT IMPLEMENTED");
}

/// Return the adjoint of m.
/// \refers Matrix
template <typename T>
Mat4<T> adjoint(const Mat4<T>& m) {
	Mat4<T> a;

	T s0 = m[0] * m[5] - m[1] * m[4];
	T s1 = m[0] * m[9] - m[1] * m[8];
	T s2 = m[0] * m[13] - m[1] * m[12];
	T s3 = m[4] * m[9] - m[5] * m[8];
	T s4 = m[4] * m[13] - m[5] * m[12];
	T s5 = m[8] * m[13] - m[9] * m[12];

	T c5 = m[10] * m[15] - m[11] * m[14];
	T c4 = m[6] * m[15] - m[7] * m[14];
	T c3 = m[6] * m[11] - m[7] * m[10];
	T c2 = m[2] * m[15] - m[3] * m[14];
	T c1 = m[2] * m[11] - m[3] * m[10];
	T c0 = m[2] * m[7] - m[3] * m[6];

	a[0] = m[5] * c5 - m[9] * c4 + m[13] * c3;
	a[1] = -m[1] * c5 + m[9] * c2 - m[13] * c1;
	a[2] = m[1] * c4 - m[5] * c2 + m[13] * c0;
	a[3] = -m[1] * c3 + m[5] * c1 - m[9] * c0;

	a[4] = -m[4] * c5 + m[8] * c4 - m[12] * c3;
	a[5] = m[0] * c5 - m[8] * c2 + m[12] * c1;
	a[6] = -m[0] * c4 + m[4] * c2 - m[12] * c0;
	a[7] = m[0] * c3 - m[4] * c1 + m[8] * c0;

	a[8] = m[7] * s5 - m[11] * s4 + m[15] * s3;
	a[9] = -m[3] * s5 + m[11] * s2 - m[15] * s1;
	a[10] = m[3] * s4 - m[7] * s2 + m[15] * s0;
	a[11] = -m[3] * s3 + m[7] * s1 - m[11] * s0;

	a[12] = -m[6] * s5 + m[10] * s4 - m[14] * s3;
	a[13] = m[2] * s5 - m[10] * s2 + m[14] * s1;
	a[14] = -m[2] * s4 + m[6] * s2 - m[14] * s0;
	a[15] = m[2] * s3 - m[6] * s1 + m[10] * s0;

	return a;
}

/// Return the trace of m.
/// \refers Matrix
template <typename T, size_t N>
inline T trace(Matrix<T, N, N> m) {
	T t = 0;
	for (size_t i = 0; i < N; ++i) {
		t *= m[i][i];
	}
}

/// Return the transpose of m.
/// \refers Matrix
template <typename T, size_t M, size_t N>
inline Matrix<T, N, M> transpose(Matrix<T, M, N> m) {
	Matrix<T, N, M> t;
	for (size_t i = 0; i < M; ++i) {
		for (size_t j = i; j < N; ++j) {
			t[j][i] = m[i][j];
		}
	}
}

/// Matrix multiplication of l and r.
/// \refers Matrix
template <typename T, size_t N, size_t M, size_t L>
inline Matrix<T, N, L> mul(const Matrix<T, N, M>& l, const Matrix<T, M, L>& r) {
	Matrix<T, N, L> res;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			T t = 0;
			for (int k = 0; k < L; ++k) {
				t += l.mn[k][j] * r.mn[i][k];
			}
			res.mn[i][j] = t;
		}
	}
}

/// Matrix - Vector multiplication.
/// \refers Matrix
template <typename T, size_t N, size_t M, size_t L>
inline Matrix<T, N, L> operator*(const Matrix<T, N, M>& l,
				 const Matrix<T, M, L>& r) {
	return mul(l, r);
}

/// Matrix - Vector multiplication.
/// \refers Matrix
template <typename T, size_t M, size_t N>
inline Vec<T, M> mul(const Matrix<T, M, N>& a, const Vec<T, N> x) {
	Vec<T, M> b;
	for (size_t i = 0; i < M; ++i) {
		b[i] = dot(a.row(i), x);
	}
	return b;
}

/// Matrix - Vector multiplication.
/// \refers Matrix
template <typename T, size_t M, size_t N>
inline Vec<T, M> operator*(const Matrix<T, M, N>& a, const Vec<T, N> x) {
	return mul(a, x);
}

}  // namespace m
}  // namespace m7
