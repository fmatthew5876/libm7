#pragma once
#include <m7/ArrayViewFwd.H>
#include <m7/meta.H>
#include <iterator>

namespace m7 {

template <typename T>
    class ArrayView {
        public:
            using value_type = T;
            using iterator = T*;
            using reverse_iterator = std::reverse_iterator<iterator>;

            ArrayView() = default;

            ArrayView(T* b, size_t n);

            template <typename R,
                     typename = std::enable_if_t<
                         meta::isContiguousRange<std::remove_reference_t<R>>
                         && meta::isCvConvertible<T, meta::rangeValueType<std::remove_reference_t<R>>>
                         >
                         >
                explicit ArrayView(R&& r);

            ArrayView(const ArrayView&) = default;
            ArrayView& operator=(const ArrayView&) = default;

            T& operator[](size_t i) const;

            T& front() const;
            T& back() const;

            T* data() const;

            iterator begin() const;
            iterator end() const;

            iterator cbegin() const;
            iterator cend() const;

            reverse_iterator rbegin() const;
            reverse_iterator rend() const;

            reverse_iterator crbegin() const;
            reverse_iterator crend() const;

            bool empty() const;
            size_t size() const;

            void remove_prefix(size_t n);
            void remove_suffix(size_t n);

        private:
            T* _b = nullptr;
            T* _e = nullptr;
    };

template <typename T>
    using CArrayView = ArrayView<const T>;

template <typename T>
ArrayView(T* b, size_t n) -> ArrayView<T>;

template <typename R>
ArrayView(R&& r) -> ArrayView<std::remove_pointer_t<meta::dataType<std::remove_reference_t<R>>>>;

template <typename T> bool operator==(ArrayView<T> l, ArrayView<T> r);
template <typename T> bool operator!=(ArrayView<T> l, ArrayView<T> r);
template <typename T> bool operator<(ArrayView<T> l, ArrayView<T> r);
template <typename T> bool operator<=(ArrayView<T> l, ArrayView<T> r);
template <typename T> bool operator>(ArrayView<T> l, ArrayView<T> r);
template <typename T> bool operator>=(ArrayView<T> l, ArrayView<T> r);

}
