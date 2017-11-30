#pragma once
#include <m7/WindowIteratorDef.H>

namespace m7 {

template <typename T>
    WindowIterator<T>::WindowIterator(T* b, size_type m, size_type i)
    : _buf(b)
      , _mask(m)
      , _i(i)
{
}

template <typename T>
    WindowIterator<T>& WindowIterator<T>::operator+=(ssize_type i) {
        _i += i;
        return *this;
    }

template <typename T>
    WindowIterator<T>& WindowIterator<T>::operator-=(ssize_type i) {
        _i -= i;
        return *this;
    }

template <typename T>
    WindowIterator<T>& WindowIterator<T>::operator++() {
        ++_i;
        return *this;
    }

template <typename T>
    WindowIterator<T> WindowIterator<T>::operator++(int) {
        auto c = *this;
        ++(*this);
        return c;
    }

template <typename T>
    WindowIterator<T>& WindowIterator<T>::operator--() {
        --_i;
        return *this;
    }

template <typename T>
    WindowIterator<T> WindowIterator<T>::operator--(int) {
        auto c = *this;
        --(*this);
        return c;
    }

template <typename T>
    T& WindowIterator<T>::operator*() const {
        return _buf[_i & _mask];
    }

template <typename T>
    T* WindowIterator<T>::operator->() const {
        return &_buf[_i & _mask];
    }

template <typename T>
    T& WindowIterator<T>::operator[](size_type i) const {
        return _buf[(_i + i) & _mask];
    }

template <typename T>
    bool operator==(WindowIterator<T> l, WindowIterator<T> r) {
        return l._i == r._i;
    }

template <typename T>
    bool operator!=(WindowIterator<T> l, WindowIterator<T> r) {
        return l._i != r._i;
    }

template <typename T>
    bool operator<(WindowIterator<T> l, WindowIterator<T> r) {
        return l._i < r._i;
    }

template <typename T>
    bool operator<=(WindowIterator<T> l, WindowIterator<T> r) {
        return l._i <= r._i;
    }

template <typename T>
    bool operator>(WindowIterator<T> l, WindowIterator<T> r) {
        return l._i > r._i;
    }

template <typename T>
    bool operator>=(WindowIterator<T> l, WindowIterator<T> r) {
        return l._i >= r._i;
    }

template <typename T>
    WindowIterator<T> operator+(WindowIterator<T> l, typename WindowIterator<T>::ssize_type r) {
        l += r;
        return l;
    }

template <typename T>
    WindowIterator<T> operator+(typename WindowIterator<T>::ssize_type l, WindowIterator<T> r) {
        return r + l;
    }

template <typename T>
    WindowIterator<T> operator-(WindowIterator<T> l, typename WindowIterator<T>::ssize_type r) {
         l -= r;
         return l;
    }

template <typename T>
    typename WindowIterator<T>::ssize_type operator-(WindowIterator<T> l, WindowIterator<T> r) {
        using ssize_type = typename WindowIterator<T>::size_type;
        return ssize_type(l._i) - ssize_type(r._i);
    }


} //namespace m7
