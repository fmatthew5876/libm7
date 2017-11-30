#pragma once
#include <m7/StaticArrayViewDef.H>
#include <m7/assert.H>
#include <algorithm>

namespace m7 {

template <typename T, size_t N>
    StaticArrayView<T,N>::StaticArrayView(T* b)
    : _b(b)
    {
        M7_ASSERT(size() == 0 || b != nullptr);
    }

template <typename T, size_t N>
    template <typename U, typename>
    StaticArrayView<T,N>::StaticArrayView(StaticArrayView<U,N> v)
    : _b(v.data())
    {}

template <typename T, size_t N>
    template <typename U, typename>
    StaticArrayView<T,N>::StaticArrayView(std::array<U, N>& a)
    : _b(a.data())
    {
    }

template <typename T, size_t N>
    template <typename U, typename>
    StaticArrayView<T,N>::StaticArrayView(U (&a)[N])
    : _b(a)
    {
    }


/// Constructs a view over the given contiguous range R.
template <typename T, size_t N>
template <typename R, typename>
    StaticArrayView<T,N>::StaticArrayView(R&& r)
    : _b(r.data())
    {
        M7_ASSERT(N <= r.size());
    }


template <typename T, size_t N>
    T& StaticArrayView<T,N>::operator[](size_t i) const {
        M7_ASSERT(i < size());
        return _b[i];
    }

template <typename T, size_t N>
    T& StaticArrayView<T,N>::front() const {
        M7_ASSERT(!empty());
        return *_b;
    }

template <typename T, size_t N>
    T& StaticArrayView<T,N>::back() const {
        M7_ASSERT(!empty());
        return _b[size()-1];
    }

template <typename T, size_t N>
    T* StaticArrayView<T,N>::data() const {
        return _b;
    }

template <typename T, size_t N>
    typename StaticArrayView<T,N>::iterator StaticArrayView<T,N>::begin() const {
        return iterator(_b);
    }

template <typename T, size_t N>
    typename StaticArrayView<T,N>::iterator StaticArrayView<T,N>::end() const {
        return iterator(_b + size());
    }

template <typename T, size_t N>
    typename StaticArrayView<T,N>::iterator StaticArrayView<T,N>::cbegin() const {
        return begin();
    }

template <typename T, size_t N>
    typename StaticArrayView<T,N>::iterator StaticArrayView<T,N>::cend() const {
        return end();
    }

template <typename T, size_t N>
    typename StaticArrayView<T,N>::reverse_iterator StaticArrayView<T,N>::rbegin() const {
        return reverse_iterator(end());
    }
template <typename T, size_t N>
    typename StaticArrayView<T,N>::reverse_iterator StaticArrayView<T,N>::rend() const {
        return reverse_iterator(begin());
    }

template <typename T, size_t N>
    typename StaticArrayView<T,N>::reverse_iterator StaticArrayView<T,N>::crbegin() const {
        return rbegin();
    }

template <typename T, size_t N>
    typename StaticArrayView<T,N>::reverse_iterator StaticArrayView<T,N>::crend() const {
        return rend();
    }

template <typename T, size_t N>
    constexpr bool StaticArrayView<T,N>::empty() {
        return size() == 0;
    }

template <typename T, size_t N>
    constexpr size_t StaticArrayView<T,N>::size() {
        return N;
    }


template <typename T, size_t N, size_t M>
bool operator==(StaticArrayView<T, N> l, StaticArrayView<T, M> r) {
    return std::equal(l.begin(), l.end(), r.begin(), r.end());
}

template <typename T, size_t N, size_t M>
bool operator!=(StaticArrayView<T, N> l, StaticArrayView<T, M> r) {
    return !(l == r);
}

template <typename T, size_t N, size_t M>
bool operator<(StaticArrayView<T, N> l, StaticArrayView<T, M> r) {
    return std::lexicographical_compare(l.begin(), l.end(), r.begin(), r.end());
}

template <typename T, size_t N, size_t M>
bool operator<=(StaticArrayView<T, N> l, StaticArrayView<T, M> r) {
    return !(l > r);
}

template <typename T, size_t N, size_t M>
bool operator>(StaticArrayView<T, N> l, StaticArrayView<T, M> r) {
    return r < l;
}

template <typename T, size_t N, size_t M>
bool operator>=(StaticArrayView<T, N> l, StaticArrayView<T, M> r) {
    return !(l < r);
}

template <size_t M, typename T, size_t N>
    constexpr StaticArrayView<T, N - M> remove_prefix(StaticArrayView<T, N> v) {
        static_assert(M <= N, "Requested prefix is too large!");
        return StaticArrayView<T, N-M>(v.data() + M);
    }

template <size_t M, typename T, size_t N>
    constexpr StaticArrayView<T, N - M> remove_suffix(StaticArrayView<T, N> v) {
        static_assert(M <= N, "Requested prefix is too large!");
        return StaticArrayView<T, N-M>(v.data());
    }

template <size_t M, typename T, size_t N>
    constexpr StaticArrayView<T, (M < N ? N - M: 0)> remove_prefix_trunc(StaticArrayView<T, N> v) {
        return remove_prefix<(M < N ? M: N)>(v);
    }

template <size_t M, typename T, size_t N>
    constexpr StaticArrayView<T, (M < N ? N - M: 0)> remove_suffix_trunc(StaticArrayView<T, N> v) {
        return remove_suffix<(M < N ? M: N)>(v);
    }

template <size_t Pos, size_t Count, typename T, size_t N>
    constexpr StaticArrayView<T, Count> slice(StaticArrayView<T, N> v) {
        static_assert(Pos <= N, "Slice position too large!");
        static_assert(Pos + Count <= N, "Slice end position too large!");

        return StaticArrayView<T, Count>(v.data() + Pos);
    }

template <size_t Pos, size_t Count, typename T, size_t N>
    constexpr StaticArrayView<T, (Pos > N ? 0 : (Pos + Count > N ? N - Pos : Count))> slice_trunc(StaticArrayView<T, N> v) {
        using Res = StaticArrayView<T, (Pos > N ? 0 : (Pos + Count > N ? N - Pos : Count))>;
        return Res(v.data() + std::min(Pos, N));
    }

template <typename T, typename U, size_t N, size_t M, typename>
    constexpr bool is_subset(StaticArrayView<T, N> outer, StaticArrayView<U, M> inner) {
        return inner.begin() >= outer.begin() && inner.end() <= outer.end();
    }

template <typename T, typename U, size_t N, size_t M, typename>
    constexpr bool is_overlap(StaticArrayView<T, N> l, StaticArrayView<U, M> r) {
        return !(l.end() <= r.begin() || r.end() < l.begin());
    }

template <typename T, typename U, size_t N, size_t M, typename>
    constexpr bool is_same(StaticArrayView<T, N> l, StaticArrayView<U, M> r) {
        return l.begin() == r.begin() && l.end() == r.end();
    }



}
