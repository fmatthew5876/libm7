#pragma once
#include <array>
#include <cstddef>
#include <iterator>
#include <m7/assert.H>
#include <utility>

namespace m7 {
namespace m {

template <typename T, size_t N>
struct DefaultVecGenericBaseData {
	using ValueT = T;
	static constexpr size_t kNumElements = N;

	T raw[N] = {};
};

template <typename VecGenericBaseData>
struct VecGenericBase : VecGenericBaseData {
	using ValueT = typename VecGenericBaseData::ValueT;
	using iterator = ValueT*;
	using const_iterator = const ValueT*;
	using reverse_iterator = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;

	static constexpr size_t kNumElements = VecGenericBaseData::kNumElements;

	using VecGenericBaseData::raw;

	using VecGenericBaseData::VecGenericBaseData;

	/// Default initialize all elements to 0.
	constexpr VecGenericBase() = default;

	/// Default initialize all elements to s.
	constexpr explicit VecGenericBase(ValueT s) { fill(s); }

	/// Initialize element by element using the given array.
	constexpr explicit VecGenericBase(
	    std::array<ValueT, kNumElements> init) {
		for (size_t i = 0; i < size(); ++i) {
			raw[i] = std::move(init[i]);
		}
	}

	void swap(VecGenericBase& o) noexcept {
		using std::swap;
		for (size_t i = 0; i < size(); ++i) {
			swap((*this)[i], o[i]);
		}
	}

	ValueT* data() { return raw; }
	const ValueT* data() const { return raw; }

	ValueT& operator[](size_t i) {
		M7_ASSERT(i < size());
		return raw[i];
	}

	const ValueT& operator[](size_t i) const {
		M7_ASSERT(i < size());
		return raw[i];
	}

	constexpr static size_t size() { return kNumElements; }

	iterator begin() { return data(); }
	iterator end() { return data() + size(); }

	const_iterator begin() const { return data(); }
	const_iterator end() const { return data() + size(); }

	const_iterator cbegin() const { return begin(); }
	const_iterator cend() const { return end(); }

	reverse_iterator rbegin() { return reverse_iterator(end()); }
	reverse_iterator rend() { return reverse_iterator(begin()); }

	const_reverse_iterator rbegin() const {
		return reverse_iterator(end());
	}
	const_reverse_iterator rend() const {
		return reverse_iterator(begin());
	}

	const_reverse_iterator crbegin() const { return rbegin(); }
	const_reverse_iterator crend() const { return rend(); }

	void fill(ValueT value) {
		for (auto& v : *this) v = value;
	}
};

/// Swap operator
template <typename D>
inline void swap(const VecGenericBase<D>& l,
		 const VecGenericBase<D>& r) noexcept {
	l.swap(r);
}

/// Elementwise compare eq
template <typename D>
inline bool operator==(const VecGenericBase<D>& l,
		       const VecGenericBase<D>& r) noexcept {
	return std::equal(l.begin(), l.end(), r.begin());
}

/// Elementwise compare ne
template <typename D>
inline bool operator!=(const VecGenericBase<D>& l,
		       const VecGenericBase<D>& r) noexcept {
	return !(l == r);
}

#if 0
template <typename D, typename F>
void cmpwiseUnaryOp(VecGenericBase<D>& out, const VecGenericBase<D>& in,
		    F&& f) {
	for (size_t i = 0; i < out.size(); ++i) {
		out[i] = f(in[i]);
	}
}

template <typename D, typename F>
void cmpwiseBinaryOp(const VecGenericBase<D>& out, const VecGenericBase<D>& l,
		     const VecGenericBase<D>& r, F&& f) {
	for (size_t i = 0; i < out.size(); ++i) {
		out[i] = f(l, r);
	}
}

template <typename D, typename F>
void cmpwiseUnaryPlus(VecGenericBase<D>& out, const VecGenericBase<D>& in) {
	out = in;
}

template <typename D, typename F>
void cmpwiseNeg(VecGenericBase<D>& out, const VecGenericBase<D>& in) {
	cmpwiseUnaryOp(out, in, [](auto v) { return -v; });
}

template <typename D, typename F>
void cmpwiseBitwiseNot(VecGenericBase<D>& out, const VecGenericBase<D>& in) {
	cmpwiseUnaryOp(out, in, [](auto v) { return ~v; });
}

template <typename D, typename F>
void cmpwiseNot(VecGenericBase<D>& out, const VecGenericBase<D>& in) {
	cmpwiseUnaryOp(out, in, [](auto v) { return !v; });
}
#endif

}  // namespace m
}  // namespace m7

namespace std {
template <typename D>
class tuple_size<m7::m::VecGenericBase<D>>
    : public integral_constant<size_t, m7::m::VecGenericBase<D>::kNumElements> {
};

template <size_t I, typename D>
class tuple_element<I, m7::m::VecGenericBase<D>> {
	static_assert(I < m7::m::VecGenericBase<D>::kNumElements,
		      "I is out of bounds!");
	using type = typename m7::m::VecGenericBase<D>::ValueT;
};

template <size_t I, typename D, typename = std::enable_if_t<std::less<>(
				    I, m7::m::VecGenericBase<D>::kNumElements)>>
constexpr typename m7::m::VecGenericBase<D>::ValueT& get(
    m7::m::VecGenericBase<D>& v) {
	return v[I];
}

template <size_t I, typename D, typename = std::enable_if_t<std::less<>(
				    I, m7::m::VecGenericBase<D>::kNumElements)>>
constexpr const typename m7::m::VecGenericBase<D>::ValueT& get(
    const m7::m::VecGenericBase<D>& v) {
	return v[I];
}

template <size_t I, typename D, typename = std::enable_if_t<std::less<>(
				    I, m7::m::VecGenericBase<D>::kNumElements)>>
constexpr typename m7::m::VecGenericBase<D>::ValueT&& get(
    m7::m::VecGenericBase<D>&& v) {
	return v[I];
}

template <size_t I, typename D, typename = std::enable_if_t<std::less<>(
				    I, m7::m::VecGenericBase<D>::kNumElements)>>
constexpr const typename m7::m::VecGenericBase<D>::ValueT&& get(
    const m7::m::VecGenericBase<D>&& v) {
	return v[I];
}

}  // namespace std
