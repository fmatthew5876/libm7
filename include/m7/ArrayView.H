#pragma once
#include <m7/ArrayViewDef.H>
#include <m7/assert.H>
#include <algorithm>

namespace m7 {

template <typename T>
    ArrayView<T>::ArrayView(T* b, size_t n)
    : _b(b)
      , _e(b + n)
{
    M7_ASSERT(size() == 0 || b != nullptr);
}

template <typename T>
template <typename R, typename>
         ArrayView<T>::ArrayView(R&& r)
{
    using std::data;
    using std::size;
    _b = data(r);
    _e = _b + size(r);
}

template <typename T>
T& ArrayView<T>::operator[](size_t i) const {
    M7_ASSERT(i < size());
    return _b[i];
}

template <typename T>
T& ArrayView<T>::front() const {
    M7_ASSERT(!empty());
    return *_b;
}
template <typename T>
T& ArrayView<T>::back() const {
    M7_ASSERT(!empty());
    return *(_e - 1);
}

template <typename T>
T* ArrayView<T>::data() const {
    return _b;
}

template <typename T>
typename ArrayView<T>::iterator ArrayView<T>::begin() const {
    return iterator(_b);
}

template <typename T>
typename ArrayView<T>::iterator ArrayView<T>::end() const {
    return iterator(_e);
}

template <typename T>
typename ArrayView<T>::iterator ArrayView<T>::cbegin() const {
    return begin();
}

template <typename T>
typename ArrayView<T>::iterator ArrayView<T>::cend() const {
    return end();
}

template <typename T>
typename ArrayView<T>::reverse_iterator ArrayView<T>::rbegin() const {
    return reverse_iterator(end());
}

template <typename T>
typename ArrayView<T>::reverse_iterator ArrayView<T>::rend() const {
    return reverse_iterator(begin());
}

template <typename T>
typename ArrayView<T>::reverse_iterator ArrayView<T>::crbegin() const {
    return rbegin();
}

template <typename T>
typename ArrayView<T>::reverse_iterator ArrayView<T>::crend() const {
    return rend();
}

template <typename T>
bool ArrayView<T>::empty() const {
    return _b == _e;
}

template <typename T>
size_t ArrayView<T>::size() const {
    return _e - _b;
}

template <typename T>
void ArrayView<T>::remove_prefix(size_t n) {
    M7_ASSERT(n < size());
    _b += n;
}

template <typename T>
void ArrayView<T>::remove_suffix(size_t n) {
    M7_ASSERT(n < size());
    _e -= n;
}

template <typename T>
void ArrayView<T>::remove_prefix_trunc(size_t n) {
    remove_prefix(std::min(n, size()));
}

template <typename T>
void ArrayView<T>::remove_suffix_trunc(size_t n) {
    remove_suffix(std::min(n, size()));
}

template <typename T>
bool operator==(ArrayView<T> l, ArrayView<T> r) {
    return std::equal(l.begin(), l.end(), r.begin(), r.end());
}

template <typename T>
bool operator!=(ArrayView<T> l, ArrayView<T> r) {
    return !(l == r);
}

template <typename T>
bool operator<(ArrayView<T> l, ArrayView<T> r) {
    return std::lexicographical_compare(l.begin(), l.end(), r.begin(), r.end());
}

template <typename T>
bool operator<=(ArrayView<T> l, ArrayView<T> r) {
    return !(l > r);
}

template <typename T>
bool operator>(ArrayView<T> l, ArrayView<T> r) {
    return r < l;
}

template <typename T>
bool operator>=(ArrayView<T> l, ArrayView<T> r) {
    return !(l < r);
}

template <typename T>
    ArrayView<T> remove_prefix(ArrayView<T> v, size_t n) {
        v.remove_prefix(n);
        return v;
    }

template <typename T>
    ArrayView<T> remove_suffix(ArrayView<T> v, size_t n) {
        v.remove_suffix(n);
        return v;
    }

template <typename T>
    ArrayView<T> remove_prefix_trunc(ArrayView<T> v, size_t n) {
        v.remove_prefix_trunc(n);
        return v;
    }

template <typename T>
    ArrayView<T> remove_suffix_trunc(ArrayView<T> v, size_t n) {
        v.remove_suffix_trunc(n);
        return v;
    }

template <typename T>
    ArrayView<T> slice(ArrayView<T> v, size_t pos, size_t count) {
        M7_ASSERT(pos <= v.size());
        M7_ASSERT(pos + count <= v.size());

        return ArrayView<T>(v.data() + pos, count);
    }

template <typename T>
    ArrayView<T> slice_trunc(ArrayView<T> v, size_t pos, size_t count) {
        pos = std::min(pos, v.size());
        count = std::min(count, v.size() - pos);

        return ArrayView<T>(v.data() + pos, count);
    }

template <typename T, typename U, typename>
    bool is_subset(ArrayView<T> outer, ArrayView<U> inner) {
        return inner.begin() >= outer.begin() && inner.end() <= outer.end();
    }

template <typename T, typename U, typename>
    bool is_overlap(ArrayView<T> l, ArrayView<U> r) {
        return !(l.end() <= r.begin() || r.end() < l.begin());
    }

template <typename T, typename U, typename>
    bool is_same(ArrayView<T> l, ArrayView<U> r) {
        return l.begin() == r.begin() && l.end() == r.end();
    }


}
