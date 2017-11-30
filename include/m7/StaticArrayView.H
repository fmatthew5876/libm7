#pragma once
#include <m7/StaticArrayViewDef.H>
#include <m7/assert.H>
#include <algorithm>

namespace m7 {

template <typename T, size_t N>
    StaticArrayView<T,N>::StaticArrayView(T* b)
    : _b(b)
    {}

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


}
