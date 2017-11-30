#pragma once
#include <m7/StaticWindowBufferDef.H>
#include <m7/WindowIterator.H>
#include <m7/assert.H>

namespace m7 {

template <typename T, size_t N>
    T& StaticWindowBuffer<T,N>::operator[](size_type i) {
        M7_ASSERT(i < size());
        return _buf[(_p + i) & mask()];
    }

template <typename T, size_t N>
    const T& StaticWindowBuffer<T,N>::operator[](size_type i) const {
        M7_ASSERT(i < size());
        return _buf[(_p + i) & mask()];
    }

template <typename T, size_t N>
    T& StaticWindowBuffer<T,N>::front() {
        M7_ASSERT(!empty());
        return _buf[_p];
    }

template <typename T, size_t N>
    const T& StaticWindowBuffer<T,N>::front() const {
        M7_ASSERT(!empty());
        return _buf[_p];
    }

template <typename T, size_t N>
    T& StaticWindowBuffer<T,N>::back() {
        M7_ASSERT(!empty());
        return _buf[(_p-1) & mask()];
    }


template <typename T, size_t N>
    const T& StaticWindowBuffer<T,N>::back() const {
        M7_ASSERT(!empty());
        return _buf[(_p-1) & mask()];
    }

template <typename T, size_t N>
    constexpr typename StaticWindowBuffer<T,N>::size_type StaticWindowBuffer<T,N>::size() {
        return N;
    }

template <typename T, size_t N>
    constexpr bool StaticWindowBuffer<T,N>::empty() {
        return size() == 0;
    }

template <typename T, size_t N>
    void StaticWindowBuffer<T,N>::push_front(T value) {
        auto newp = (_p - 1) & mask();
        _buf[newp] = std::move(value);
        _p = newp;
    }

template <typename T, size_t N>
    typename StaticWindowBuffer<T,N>::iterator StaticWindowBuffer<T,N>::begin() {
        return iterator(_buf.data(), mask(), _p);
    }

template <typename T, size_t N>
    typename StaticWindowBuffer<T,N>::iterator StaticWindowBuffer<T,N>::end() {
        return iterator(_buf.data(), mask(), _p + size());
    }

template <typename T, size_t N>
    typename StaticWindowBuffer<T,N>::const_iterator StaticWindowBuffer<T,N>::begin() const {
        return cbegin();
    }

template <typename T, size_t N>
    typename StaticWindowBuffer<T,N>::const_iterator StaticWindowBuffer<T,N>::end() const {
        return cend();
    }

template <typename T, size_t N>
    typename StaticWindowBuffer<T,N>::const_iterator StaticWindowBuffer<T,N>::cbegin() const {
        return const_iterator(_buf.data(), mask(), _p);
    }

template <typename T, size_t N>
    typename StaticWindowBuffer<T,N>::const_iterator StaticWindowBuffer<T,N>::cend() const {
        return const_iterator(_buf.data(), mask(), _p + size());
    }

template <typename T, size_t N>
    typename StaticWindowBuffer<T,N>::reverse_iterator StaticWindowBuffer<T,N>::rbegin() {
        return reverse_iterator(end());
    }

template <typename T, size_t N>
    typename StaticWindowBuffer<T,N>::reverse_iterator StaticWindowBuffer<T,N>::rend() {
        return reverse_iterator(begin());
    }

template <typename T, size_t N>
    typename StaticWindowBuffer<T,N>::const_reverse_iterator StaticWindowBuffer<T,N>::rbegin() const {
        return crbegin();
    }

template <typename T, size_t N>
    typename StaticWindowBuffer<T,N>::const_reverse_iterator StaticWindowBuffer<T,N>::rend() const {
        return crend();
    }

template <typename T, size_t N>
    typename StaticWindowBuffer<T,N>::const_reverse_iterator StaticWindowBuffer<T,N>::crbegin() const {
        return const_reverse_iterator(cend());
    }

template <typename T, size_t N>
    typename StaticWindowBuffer<T,N>::const_reverse_iterator StaticWindowBuffer<T,N>::crend() const {
        return const_reverse_iterator(cbegin());
    }

template <typename T, size_t N>
    constexpr typename StaticWindowBuffer<T,N>::size_type StaticWindowBuffer<T,N>::mask() {
        return N - 1;
    }

}
