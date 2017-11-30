#pragma once
#include <m7/WindowBufferDef.H>
#include <m7/SystemAllocator.H>
#include <m7/ScopeGuard.H>
#include <m7/bitops.H>
#include <m7/assert.H>

namespace m7 {

template <typename T>
    WindowBuffer<T>::WindowBuffer(size_type window_size)
    {
        _init(window_size, [&](size_type i) { new (&_buf[i]) T(); }, false);
    }

template <typename T>
    WindowBuffer<T>::WindowBuffer(size_type window_size, const T& init)
    {
        _init(window_size, [&](size_type i) { new (&_buf[i]) T(init); }, false);
    }


template <typename T>
    WindowBuffer<T>::WindowBuffer(const WindowBuffer& o) {
        _init(o.size(), [&](size_type i) { new (&(*this)[i]) T(o[i]); }, false);
    }

template <typename T>
    WindowBuffer<T>& WindowBuffer<T>::operator=(const WindowBuffer<T>& o) {
        if(this != &o) {
            auto copy = WindowBuffer(o);
            swap(copy);
        }
        return *this;
    }

template <typename T>
    WindowBuffer<T>::WindowBuffer(WindowBuffer<T>&& o) noexcept
    : _buf(o._buf)
    , _mask(o._mask)
    , _p(o._p)
    {
        o._buf = nullptr;
        o._mask = std::numeric_limits<size_type>::max();
        o._p = 0;
    }

template <typename T>
    WindowBuffer<T>& WindowBuffer<T>::operator=(WindowBuffer<T>&& o) noexcept {
        if(this != &o) {
            swap(o);
            o._reset(o.size());
        }
        return *this;
    }

template <typename T>
    void WindowBuffer<T>::swap(WindowBuffer<T>& o) noexcept {
        using std::swap;
        swap(_buf, o._buf);
        swap(_mask, o._mask);
        swap(_p, o._p);
    }

template <typename T>
    WindowBuffer<T>::~WindowBuffer() {
        _reset(size());
    }

template <typename T>
    T& WindowBuffer<T>::operator[](size_type i) {
        M7_ASSERT(i < size());
        return _buf[(_p + i) & _mask];
    }

template <typename T>
    const T& WindowBuffer<T>::operator[](size_type i) const {
        M7_ASSERT(i < size());
        return _buf[(_p + i) & _mask];
    }

template <typename T>
    T& WindowBuffer<T>::front() {
        M7_ASSERT(!empty());
        return _buf[_p];
    }

template <typename T>
    const T& WindowBuffer<T>::front() const {
        M7_ASSERT(!empty());
        return _buf[_p];
    }

template <typename T>
    T& WindowBuffer<T>::back() {
        M7_ASSERT(!empty());
        return _buf[(_p-1) & _mask];
    }


template <typename T>
    const T& WindowBuffer<T>::back() const {
        M7_ASSERT(!empty());
        return _buf[(_p-1) & _mask];
    }

template <typename T>
    typename WindowBuffer<T>::size_type WindowBuffer<T>::size() const {
        return _mask + 1;
    }

template <typename T>
    bool WindowBuffer<T>::empty() const {
        return size() == 0;
    }

template <typename T>
    void WindowBuffer<T>::push_front(T value) {
        auto newp = (_p - 1) & _mask;
        _buf[newp] = std::move(value);
        _p = newp;
    }

template <typename T>
    typename WindowBuffer<T>::iterator WindowBuffer<T>::begin() {
        return iterator(_buf, _mask, _p);
    }

template <typename T>
    typename WindowBuffer<T>::iterator WindowBuffer<T>::end() {
        return iterator(_buf, _mask, _p + size());
    }

template <typename T>
    typename WindowBuffer<T>::const_iterator WindowBuffer<T>::begin() const {
        return cbegin();
    }

template <typename T>
    typename WindowBuffer<T>::const_iterator WindowBuffer<T>::end() const {
        return cend();
    }

template <typename T>
    typename WindowBuffer<T>::const_iterator WindowBuffer<T>::cbegin() const {
        return const_iterator(_buf, _mask, _p);
    }

template <typename T>
    typename WindowBuffer<T>::const_iterator WindowBuffer<T>::cend() const {
        return const_iterator(_buf, _mask, _p + size());
    }

template <typename T>
    typename WindowBuffer<T>::reverse_iterator WindowBuffer<T>::rbegin() {
        return reverse_iterator(end());
    }

template <typename T>
    typename WindowBuffer<T>::reverse_iterator WindowBuffer<T>::rend() {
        return reverse_iterator(begin());
    }

template <typename T>
    typename WindowBuffer<T>::const_reverse_iterator WindowBuffer<T>::rbegin() const {
        return crbegin();
    }

template <typename T>
    typename WindowBuffer<T>::const_reverse_iterator WindowBuffer<T>::rend() const {
        return crend();
    }

template <typename T>
    typename WindowBuffer<T>::const_reverse_iterator WindowBuffer<T>::crbegin() const {
        return const_reverse_iterator(cend());
    }

template <typename T>
    typename WindowBuffer<T>::const_reverse_iterator WindowBuffer<T>::crend() const {
        return const_reverse_iterator(cbegin());
    }

template <typename T>
    template <typename F>
    void WindowBuffer<T>::_init(size_type window_size, F&& make, bool isp2) {
        if(window_size == 0) {
            return;
        }

        if(!isp2) {
            window_size = ceilp2(window_size);
        }

        _buf = SystemAllocator::alloc<T>(window_size);
        _mask = window_size - 1;
        _p = 0;

        size_type i = 0;

        //Cleanup if anything throws
        auto sg = make_scope_guard([&](){ _reset(i); });

        //Construct in backward order (oldest to newest)
        for(; i < window_size; ++i) {
            make(window_size - i -1);
        }

        sg.dismiss();

    }

template <typename T>
    void WindowBuffer<T>::_reset(size_type n) noexcept {
        //Destroy from newest to oldest.
        for(size_type i = size()-n; i < size(); ++i) {
            (*this)[i].~T();
        }
        SystemAllocator::free(_buf);

        _buf = nullptr;
        _mask = std::numeric_limits<size_type>::max();
        _p = 0;
    }


template <typename T>
    WindowBufferIterator<T>& WindowBufferIterator<T>::operator+=(ssize_type i) {
        _i += i;
        return *this;
    }

template <typename T>
    WindowBufferIterator<T>& WindowBufferIterator<T>::operator-=(ssize_type i) {
        _i -= i;
        return *this;
    }

template <typename T>
    WindowBufferIterator<T>& WindowBufferIterator<T>::operator++() {
        ++_i;
        return *this;
    }

template <typename T>
    WindowBufferIterator<T> WindowBufferIterator<T>::operator++(int) {
        auto c = *this;
        ++(*this);
        return c;
    }

template <typename T>
    WindowBufferIterator<T>& WindowBufferIterator<T>::operator--() {
        --_i;
        return *this;
    }

template <typename T>
    WindowBufferIterator<T> WindowBufferIterator<T>::operator--(int) {
        auto c = *this;
        --(*this);
        return c;
    }

template <typename T>
    T& WindowBufferIterator<T>::operator*() const {
        return _buf[_i & _mask];
    }

template <typename T>
    T* WindowBufferIterator<T>::operator->() const {
        return &_buf[_i & _mask];
    }

template <typename T>
    T& WindowBufferIterator<T>::operator[](size_type i) const {
        return _buf[(_i + i) & _mask];
    }

template <typename T>
    bool operator==(WindowBufferIterator<T> l, WindowBufferIterator<T> r) {
        return l._i == r._i;
    }

template <typename T>
    bool operator!=(WindowBufferIterator<T> l, WindowBufferIterator<T> r) {
        return l._i != r._i;
    }

template <typename T>
    bool operator<(WindowBufferIterator<T> l, WindowBufferIterator<T> r) {
        return l._i < r._i;
    }

template <typename T>
    bool operator<=(WindowBufferIterator<T> l, WindowBufferIterator<T> r) {
        return l._i <= r._i;
    }

template <typename T>
    bool operator>(WindowBufferIterator<T> l, WindowBufferIterator<T> r) {
        return l._i > r._i;
    }

template <typename T>
    bool operator>=(WindowBufferIterator<T> l, WindowBufferIterator<T> r) {
        return l._i >= r._i;
    }

template <typename T>
    WindowBufferIterator<T> operator+(WindowBufferIterator<T> l, typename WindowBufferIterator<T>::ssize_type r) {
        l += r;
        return l;
    }

template <typename T>
    WindowBufferIterator<T> operator+(typename WindowBufferIterator<T>::ssize_type l, WindowBufferIterator<T> r) {
        return r + l;
    }

template <typename T>
    WindowBufferIterator<T> operator-(WindowBufferIterator<T> l, typename WindowBufferIterator<T>::ssize_type r) {
         l -= r;
         return l;
    }

template <typename T>
    typename WindowBufferIterator<T>::ssize_type operator-(WindowBufferIterator<T> l, WindowBufferIterator<T> r) {
        return ssize_type(l._i) - ssize_type(r._i);
    }

template <typename T>
    WindowBufferIterator<T>::WindowBufferIterator(T* b, size_type m, size_type i)
    : _buf(b)
      , _mask(m)
      , _i(i)
{
}






} //namespace m7
