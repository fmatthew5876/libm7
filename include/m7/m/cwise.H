#pragma once
#include <m7/m/math.H>
#include <m7/type_traits.H>

namespace m7 {
namespace m {

/// Component-wise T(x).
template <typename T, typename S, size_t... I,
	  template <typename, size_t...> class V,
	  typename = std::enable_if_t<isVectorLikeV<V<S, I...>>>>
constexpr auto cw_convert(V<S, I...>&& v) {
	V<T, I...> c;
	for (size_t i = 0; i < v.sizeElements(); ++i) {
		c[i] = T(v[i]);
	}
	return c;
}

/// Component-wise f(x).
template <
    typename F, template <typename, size_t...> class V, typename ScalarIn,
    size_t... I, typename VecIn = V<ScalarIn, I...>,
    typename ScalarOut = decltype(std::declval<F>()(std::declval<VecIn>())),
    typename VecOut = V<ScalarOut, I...>,
    typename = std::enable_if_t<isVectorLikeV<VecIn>>>
auto cw_map(const VecIn& x, F&& f) {
	V<ScalarOut, I...> y;
	for (size_t i = 0; i < y.sizeElements(); ++i) {
		y[i] = f(x);
	}
	return y;
}

/// Component-wise f(x,y).
template <
    typename F, template <typename, size_t...> class V, typename ScalarIn,
    size_t... I, typename VecIn = V<ScalarIn, I...>,
    typename ScalarOut = decltype(std::declval<F>()(std::declval<VecIn>())),
    typename VecOut = V<ScalarOut, I...>,
    typename = std::enable_if_t<isVectorLikeV<VecIn>>>
auto cw_map(const VecIn& x, const VecIn& y, F&& f) {
	V<ScalarOut, I...> z;
	for (size_t i = 0; i < z.sizeElements(); ++i) {
		z[i] = f(x, y);
	}
	return z;
}

/// Component-wise f(x,y,z).
template <
    typename F, template <typename, size_t...> class V, typename ScalarIn,
    size_t... I, typename VecIn = V<ScalarIn, I...>,
    typename ScalarOut = decltype(std::declval<F>()(std::declval<VecIn>())),
    typename VecOut = V<ScalarOut, I...>,
    typename = std::enable_if_t<isVectorLikeV<VecIn>>>
auto cw_map(const VecIn& x, const VecIn& y, const VecIn& z, F&& f) {
	V<ScalarOut, I...> w;
	for (size_t i = 0; i < w.sizeElements(); ++i) {
		w[i] = f(x, y, z);
	}
	return w;
}

/// Component-wise +x.
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_plus(const V& x) {
	return cw_map(x, [](auto x) { return +x; });
}

/// Component-wise -x.
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_neg(const V& x) {
	return cw_map(x, [](auto x) { return -x; });
}

/// Component-wise ~x.
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_bitnot(const V& x) {
	return cw_map(x, [](auto x) { return ~x; });
}

/// Component-wise x + y.
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_add(const V& x, const V& y) {
	return cw_map(x, y, [](auto x, auto y) { return x + y; });
}

/// Component-wise x + y.
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_add(const V& x, const typename V::ScalarT y) {
	return cw_map(x, [y](auto x) { return x + y; });
}

/// Component-wise x + y.
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_add(const typename V::ScalarT x, const V& y) {
	return cw_map(y, [x](auto y) { return x + y; });
}

/// Component-wise x - y.
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_sub(const V& x, const V& y) {
	return cw_map(x, y, [](auto x, auto y) { return x - y; });
}

/// Component-wise x - y.
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_sub(const V& x, const typename V::ScalarT y) {
	return cw_map(x, [y](auto x) { return x - y; });
}

/// Component-wise x - y.
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_sub(const typename V::ScalarT x, const V& y) {
	return cw_map(y, [x](auto y) { return x - y; });
}

/// Component-wise x * y.
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_mul(const V& x, const V& y) {
	return cw_map(x, y, [](auto x, auto y) { return x * y; });
}

/// Component-wise x * y.
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_mul(const V& x, const typename V::ScalarT y) {
	return cw_map(x, [y](auto x) { return x * y; });
}

/// Component-wise x * y.
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_mul(const typename V::ScalarT x, const V& y) {
	return cw_map(y, [x](auto y) { return x * y; });
}

/// Component-wise x / y.
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_div(const V& x, const V& y) {
	return cw_map(x, y, [](auto x, auto y) { return x / y; });
}

/// Component-wise x / y.
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_div(const V& x, const typename V::ScalarT y) {
	return cw_map(x, [y](auto x) { return x / y; });
}

/// Component-wise x / y.
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_div(const typename V::ScalarT x, const V& y) {
	return cw_map(y, [x](auto y) { return x / y; });
}

/// Component-wise x % y.
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_mod(const V& x, const V& y) {
	return cw_map(x, y, [](auto x, auto y) { return x % y; });
}

/// Component-wise x % y.
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_mod(const V& x, const typename V::ScalarT y) {
	return cw_map(x, [y](auto x) { return x % y; });
}

/// Component-wise x % y.
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_mod(const typename V::ScalarT x, const V& y) {
	return cw_map(y, [x](auto y) { return x % y; });
}

/// Component-wise x & y.
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_bitand(const V& x, const V& y) {
	return cw_map(x, y, [](auto x, auto y) { return x & y; });
}

/// Component-wise x & y.
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_bitand(const V& x, const typename V::ScalarT y) {
	return cw_map(x, [y](auto x) { return x & y; });
}

/// Component-wise x & y.
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_bitand(const typename V::ScalarT x, const V& y) {
	return cw_map(y, [x](auto y) { return x & y; });
}

/// Component-wise x | y.
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_bitor(const V& x, const V& y) {
	return cw_map(x, y, [](auto x, auto y) { return x | y; });
}

/// Component-wise x | y.
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_bitor(const V& x, const typename V::ScalarT y) {
	return cw_map(x, [y](auto x) { return x | y; });
}

/// Component-wise x | y.
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_bitor(const typename V::ScalarT x, const V& y) {
	return cw_map(y, [x](auto y) { return x | y; });
}

/// Component-wise x ^ y.
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_bitxor(const V& x, const V& y) {
	return cw_map(x, y, [](auto x, auto y) { return x ^ y; });
}

/// Component-wise x ^ y.
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_bitxor(const V& x, const typename V::ScalarT y) {
	return cw_map(x, [y](auto x) { return x ^ y; });
}

/// Component-wise x ^ y.
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_bitxor(const typename V::ScalarT x, const V& y) {
	return cw_map(y, [x](auto y) { return x ^ y; });
}

/// Component-wise x << y.
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_bitshl(const V& x, const V& y) {
	return cw_map(x, y, [](auto x, auto y) { return x << y; });
}

/// Component-wise x << y.
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_bitshl(const V& x, const typename V::ScalarT y) {
	return cw_map(x, [y](auto x) { return x << y; });
}

/// Component-wise x << y.
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_bitshl(const typename V::ScalarT x, const V& y) {
	return cw_map(y, [x](auto y) { return x << y; });
}

/// Component-wise x >> y.
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_bitshlr(const V& x, const V& y) {
	return cw_map(x, y, [](auto x, auto y) { return x >> y; });
}

/// Component-wise x >> y.
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_bitshr(const V& x, const typename V::ScalarT y) {
	return cw_map(x, [y](auto x) { return x >> y; });
}

/// Component-wise x >> y.
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_bitshr(const typename V::ScalarT x, const V& y) {
	return cw_map(y, [x](auto y) { return x >> y; });
}

/// Component-wise !x.
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_not(const V& x) {
	return cw_map(x, [](auto x) { return !x; });
}

/// Component-wise x && y.
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_and(const V& x, const V& y) {
	return cw_map(x, y, [](auto x, auto y) { return x && y; });
}

/// Component-wise x && y.
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_and(const V& x, const typename V::ScalarT y) {
	return cw_map(x, [y](auto x) { return x && y; });
}

/// Component-wise x && y.
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_and(const typename V::ScalarT x, const V& y) {
	return cw_map(y, [x](auto y) { return x && y; });
}

/// Component-wise x || y.
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_or(const V& x, const V& y) {
	return cw_map(x, y, [](auto x, auto y) { return x || y; });
}

/// Component-wise x || y.
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_or(const V& x, const typename V::ScalarT y) {
	return cw_map(x, [y](auto x) { return x || y; });
}

/// Component-wise x || y.
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_or(const typename V::ScalarT x, const V& y) {
	return cw_map(y, [x](auto y) { return x || y; });
}

/// Component-wise x == y.
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_eq(const V& x, const V& y) {
	return cw_map(x, y, [](auto x, auto y) { return x == y; });
}

/// Component-wise x == y.
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_eq(const V& x, const typename V::ScalarT y) {
	return cw_map(x, [y](auto x) { return x == y; });
}

/// Component-wise x == y.
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_eq(const typename V::ScalarT x, const V& y) {
	return cw_map(y, [x](auto y) { return x == y; });
}

/// Component-wise x != y.
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_ne(const V& x, const V& y) {
	return cw_map(x, y, [](auto x, auto y) { return x != y; });
}

/// Component-wise x != y.
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_ne(const V& x, const typename V::ScalarT y) {
	return cw_map(x, [y](auto x) { return x != y; });
}

/// Component-wise x != y.
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_ne(const typename V::ScalarT x, const V& y) {
	return cw_map(y, [x](auto y) { return x != y; });
}

/// Component-wise x < y.
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_lt(const V& x, const V& y) {
	return cw_map(x, y, [](auto x, auto y) { return x < y; });
}

/// Component-wise x < y.
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_lt(const V& x, const typename V::ScalarT y) {
	return cw_map(x, [y](auto x) { return x < y; });
}

/// Component-wise x < y.
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_lt(const typename V::ScalarT x, const V& y) {
	return cw_map(y, [x](auto y) { return x < y; });
}

/// Component-wise x <= y.
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_le(const V& x, const V& y) {
	return cw_map(x, y, [](auto x, auto y) { return x <= y; });
}

/// Component-wise x <= y.
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_le(const V& x, const typename V::ScalarT y) {
	return cw_map(x, [y](auto x) { return x <= y; });
}

/// Component-wise x <= y.
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_le(const typename V::ScalarT x, const V& y) {
	return cw_map(y, [x](auto y) { return x <= y; });
}

/// Component-wise x > y.
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_gt(const V& x, const V& y) {
	return cw_map(x, y, [](auto x, auto y) { return x > y; });
}

/// Component-wise x > y.
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_gt(const V& x, const typename V::ScalarT y) {
	return cw_map(x, [y](auto x) { return x > y; });
}

/// Component-wise x > y.
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_gt(const typename V::ScalarT x, const V& y) {
	return cw_map(y, [x](auto y) { return x > y; });
}

/// Component-wise x >= y.
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_ge(const V& x, const V& y) {
	return cw_map(x, y, [](auto x, auto y) { return x >= y; });
}

/// Component-wise x >= y.
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_ge(const V& x, const typename V::ScalarT y) {
	return cw_map(x, [y](auto x) { return x >= y; });
}

/// Component-wise x >= y.
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_ge(const typename V::ScalarT x, const V& y) {
	return cw_map(y, [x](auto y) { return x >= y; });
}

/// Component-wise std::abs(x)
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_abs(const V& x) {
	return cw_map(x, [](auto x) { return std::abs(x); });
}

/// Component-wise std::exp(x)
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_exp(const V& x) {
	return cw_map(x, [](auto x) { return std::exp(x); });
}

/// Component-wise std::exp2(x)
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_exp2(const V& x) {
	return cw_map(x, [](auto x) { return std::exp2(x); });
}

/// Component-wise std::expm1(x)
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_expm1(const V& x) {
	return cw_map(x, [](auto x) { return std::expm1(x); });
}

/// Component-wise std::log(x)
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_log(const V& x) {
	return cw_map(x, [](auto x) { return std::log(x); });
}

/// Component-wise std::log10(x)
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_log10(const V& x) {
	return cw_map(x, [](auto x) { return std::log10(x); });
}

/// Component-wise std::log2(x)
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_log2(const V& x) {
	return cw_map(x, [](auto x) { return std::log2(x); });
}

/// Component-wise std::log2(x)
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_log1p(const V& x) {
	return cw_map(x, [](auto x) { return std::log1p(x); });
}

/// Component-wise std::pow(base, exp)
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_pow(const V& base, const V& exp) {
	return cw_map(base, exp, [](auto b, auto e) { return std::pow(b, e); });
}

/// Component-wise std::pow(base, exp)
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_pow(const V& base, typename V::ScalarT exp) {
	return cw_map(base, [exp](auto b) { return std::pow(b, exp); });
}

/// Component-wise std::pow(base, exp)
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_pow(typename V::ScalarT base, const V& exp) {
	return cw_map(exp, [base](auto e) { return std::pow(base, e); });
}

/// Component-wise std::sqrt(x)
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_sqrt(const V& x) {
	return cw_map(x, [](auto x) { return std::sqrt(x); });
}

/// Component-wise std::cbrt(x)
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_cbrt(const V& x) {
	return cw_map(x, [](auto x) { return std::cbrt(x); });
}

/// Component-wise std::sin(x)
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_sin(const V& x) {
	return cw_map(x, [](auto x) { return std::sin(x); });
}

/// Component-wise std::cos(x)
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_cos(const V& x) {
	return cw_map(x, [](auto x) { return std::cos(x); });
}

/// Component-wise std::tan(x)
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_tan(const V& x) {
	return cw_map(x, [](auto x) { return std::tan(x); });
}

/// Component-wise std::asin(x)
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_asin(const V& x) {
	return cw_map(x, [](auto x) { return std::asin(x); });
}

/// Component-wise std::acos(x)
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_acos(const V& x) {
	return cw_map(x, [](auto x) { return std::acos(x); });
}

/// Component-wise std::atan(x)
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_atan(const V& x) {
	return cw_map(x, [](auto x) { return std::atan(x); });
}

/// Component-wise std::atan2(x, y)
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_atan2(const V& x, const V& y) {
	return cw_map(x, y, [](auto x, auto y) { return std::atan2(x, y); });
}

/// Component-wise std::atan2(x, y)
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_atan2(const V& x, typename V::ScalarT y) {
	return cw_map(x, [y](auto x) { return std::atan2(x, y); });
}

/// Component-wise std::atan2(x, y)
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_atan2(typename V::ScalarT x, const V& y) {
	return cw_map(y, [x](auto y) { return std::atan2(x, y); });
}

/// Component-wise std::sinh(x)
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_sinh(const V& x) {
	return cw_map(x, [](auto x) { return std::sinh(x); });
}

/// Component-wise std::cosh(x)
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_cosh(const V& x) {
	return cw_map(x, [](auto x) { return std::cosh(x); });
}

/// Component-wise std::tanh(x)
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_tanh(const V& x) {
	return cw_map(x, [](auto x) { return std::tanh(x); });
}

/// Component-wise std::fmod(x, y)
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_fmod(const V& x, const V& y) {
	return cw_map(x, y, [](auto x, auto y) { return std::fmod(x, y); });
}

/// Component-wise std::fmod(x, y)
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_fmod(const V& x, typename V::ScalarT y) {
	return cw_map(x, [y](auto x) { return std::fmod(x, y); });
}

/// Component-wise std::fmod(x, y)
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_fmod(typename V::ScalarT x, const V& y) {
	return cw_map(y, [x](auto y) { return std::fmod(x, y); });
}

/// Component-wise std::remainder(x, y)
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_remainder(const V& x, const V& y) {
	return cw_map(x, y,
		      [](auto x, auto y) { return std::remainder(x, y); });
}

/// Component-wise std::remainder(x, y)
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_remainder(const V& x, typename V::ScalarT y) {
	return cw_map(x, [y](auto x) { return std::remainder(x, y); });
}

/// Component-wise std::remainder(x, y)
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_remainder(typename V::ScalarT x, const V& y) {
	return cw_map(y, [x](auto y) { return std::remainder(x, y); });
}

/// Component-wise std::fmin(x, y)
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_fmin(const V& x, const V& y) {
	return cw_map(x, y, [](auto x, auto y) { return std::fmin(x, y); });
}

/// Component-wise std::fmin(x, y)
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_fmin(const V& x, typename V::ScalarT y) {
	return cw_map(x, [y](auto x) { return std::fmin(x, y); });
}

/// Component-wise std::fmin(x, y)
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_fmin(typename V::ScalarT x, const V& y) {
	return cw_map(y, [x](auto y) { return std::fmin(x, y); });
}

/// Component-wise std::fmax(x, y)
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_fmax(const V& x, const V& y) {
	return cw_map(x, y, [](auto x, auto y) { return std::fmax(x, y); });
}

/// Component-wise std::fmax(x, y)
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_fmax(const V& x, typename V::ScalarT y) {
	return cw_map(x, [y](auto x) { return std::fmax(x, y); });
}

/// Component-wise std::fmax(x, y)
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_fmax(typename V::ScalarT x, const V& y) {
	return cw_map(y, [x](auto y) { return std::fmax(x, y); });
}

/// Component-wise std::erf(x)
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_erf(const V& x) {
	return cw_map(x, [](auto x) { return std::erf(x); });
}

/// Component-wise std::erfc(x)
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_erfc(const V& x) {
	return cw_map(x, [](auto x) { return std::erfc(x); });
}

/// Component-wise std::tgamma(x)
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_tgamma(const V& x) {
	return cw_map(x, [](auto x) { return std::tgamma(x); });
}

/// Component-wise std::lgamma(x)
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_lgamma(const V& x) {
	return cw_map(x, [](auto x) { return std::lgamma(x); });
}

/// Component-wise std::lgamma(x)
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_ceil(const V& x) {
	return cw_map(x, [](auto x) { return std::ceil(x); });
}

/// Component-wise std::lgamma(x)
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_floor(const V& x) {
	return cw_map(x, [](auto x) { return std::floor(x); });
}

/// Component-wise std::trunc(x)
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_trunc(const V& x) {
	return cw_map(x, [](auto x) { return std::trunc(x); });
}

/// Component-wise std::fpclassify(x)
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_fpclassify(const V& x) {
	return cw_map(x, [](auto x) { return std::fpclassify(x); });
}

/// Component-wise std::isfinite(x)
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_isfinite(const V& x) {
	return cw_map(x, [](auto x) { return std::isfinite(x); });
}

/// Component-wise std::isinf(x)
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_isinf(const V& x) {
	return cw_map(x, [](auto x) { return std::isinf(x); });
}

/// Component-wise std::isnan(x)
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_isnan(const V& x) {
	return cw_map(x, [](auto x) { return std::isnan(x); });
}

/// Component-wise std::signbit(x)
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_signbit(const V& x) {
	return cw_map(x, [](auto x) { return std::signbit(x); });
}

/// Component-wise std::isgreater(x)
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_isgreater(const V& x) {
	return cw_map(x, [](auto x) { return std::isgreater(x); });
}

/// Component-wise std::isgreaterequal(x)
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_isgreaterequal(const V& x) {
	return cw_map(x, [](auto x) { return std::isgreaterequal(x); });
}

/// Component-wise std::isless(x)
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_isless(const V& x) {
	return cw_map(x, [](auto x) { return std::isless(x); });
}

/// Component-wise std::isless(x)
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_islessequal(const V& x) {
	return cw_map(x, [](auto x) { return std::islessequal(x); });
}

/// Component-wise std::islessgreater(x)
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_islessgreater(const V& x) {
	return cw_map(x, [](auto x) { return std::islessgreater(x); });
}

/// Component-wise std::isunordered(x)
template <typename V, typename = std::enable_if_t<isVectorLikeV<V>>>
auto cw_isunordered(const V& x) {
	return cw_map(x, [](auto x) { return std::isunordered(x); });
}

}  // namespace m
}  // namespace m7
