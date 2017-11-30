#pragma once
#include <m7/ArrayViewFwd.H>
#include <m7/meta.H>
#include <iterator>

namespace m7 {

/// A view over a contiguous range of memory.
template <typename T>
    class ArrayView {
        public:
            using value_type = T;
            using iterator = T*;
            using reverse_iterator = std::reverse_iterator<iterator>;

            /// Constructs an empty view.
            ArrayView() = default;

            /// Constructs a view over [b, b + n)
            /// \pre n == 0 || b != nullptr
            /// \pre [b, b + n) must be a valid memory range.
            ArrayView(T* b, size_t n);

            /// Constructs a view over the given contiguous range R.
            template <typename R,
                     typename = std::enable_if_t<
                         meta::isContiguousRange<std::remove_reference_t<R>>
                         && meta::isCvConvertible<T, meta::rangeValueType<std::remove_reference_t<R>>>
                         >
                         >
                explicit ArrayView(R&& r);

            /// Copies a view.
            ArrayView(const ArrayView&) = default;

            /// Copies a view.
            ArrayView& operator=(const ArrayView&) = default;

            /// Returns i'th element from view.
            /// \pre i < size().
            T& operator[](size_t i) const;

            /// Returns first element from the view.
            /// \pre !empty()
            T& front() const;

            /// Returns last element from the view.
            /// \pre !empty()
            T& back() const;

            /// Returns pointer to first element in the view.
            T* data() const;

            /// Iterator to the beginning.
            iterator begin() const;

            /// Iterator to the end.
            iterator end() const;

            /// Iterator to the beginning.
            iterator cbegin() const;

            /// Iterator to the end.
            iterator cend() const;

            /// Reverse Iterator begin.
            reverse_iterator rbegin() const;

            /// Reverse Iterator end.
            reverse_iterator rend() const;

            /// Reverse Iterator begin.
            reverse_iterator crbegin() const;

            /// Reverse Iterator end.
            reverse_iterator crend() const;

            /// true if the view is empty.
            bool empty() const;

            /// number of objects spanned by the view.
            size_t size() const;

            /// Shrinks the view by removing the first n elements.
            /// \pre n < size()
            void remove_prefix(size_t n);

            /// Shrinks the view by removing the last n elements.
            /// \pre n < size()
            void remove_suffix(size_t n);

            /// Shrinks the view by removing up to the first n elements.
            void remove_prefix_trunc(size_t n);

            /// Shrinks the view by removing up to the last n elements.
            void remove_suffix_trunc(size_t n);

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

/// true if the underlying ranges are equal.
template <typename T> bool operator==(ArrayView<T> l, ArrayView<T> r);

/// true if the underlying ranges are not equal.
template <typename T> bool operator!=(ArrayView<T> l, ArrayView<T> r);

/// lexicographical comparison on the underlying ranges.
template <typename T> bool operator<(ArrayView<T> l, ArrayView<T> r);

/// lexicographical comparison on the underlying ranges.
template <typename T> bool operator<=(ArrayView<T> l, ArrayView<T> r);

/// lexicographical comparison on the underlying ranges.
template <typename T> bool operator>(ArrayView<T> l, ArrayView<T> r);

/// lexicographical comparison on the underlying ranges.
template <typename T> bool operator>=(ArrayView<T> l, ArrayView<T> r);

/// removes n elements from the front of v and returns the new view.
/// \pre n <= v.size()
template <typename T>
    ArrayView<T> remove_prefix(ArrayView<T> v, size_t n);

/// removes n elements from the back of v and returns the new view.
/// \pre n <= v.size()
template <typename T>
    ArrayView<T> remove_suffix(ArrayView<T> v, size_t n);

/// removes up to n elements from the front of v and returns the new view.
template <typename T>
    ArrayView<T> remove_prefix_trunc(ArrayView<T> v, size_t n);

/// removes up to n elements from the back of v and returns the new view.
template <typename T>
    ArrayView<T> remove_suffix_trunc(ArrayView<T> v, size_t n);

/// returns a sub-array starting at pos with size count.
/// \pre pos <= v.size() && pos + count <= v.size()
template <typename T>
    ArrayView<T> slice(ArrayView<T> v, size_t pos, size_t count);

/// returns a sub-array starting at pos with up to size count.
/// If pos >= v.size(), returns empty view starting at v.end().
/// If pos + count >= v.size(), returns a truncated view.
template <typename T>
    ArrayView<T> slice_trunc(ArrayView<T> v, size_t pos, size_t count);

/// true if inner is a subset of outer.
template <typename T, typename U,
         typename = std::enable_if_t<std::is_same_v<std::remove_cv<T>,std::remove_cv<U>>
             >>
    bool is_subset(ArrayView<T> outer, ArrayView<U> inner);

/// true if l and r overlap over at least one object.
template <typename T, typename U,
         typename = std::enable_if_t<std::is_same_v<std::remove_cv<T>,std::remove_cv<U>>
             >>
    bool is_overlap(ArrayView<T> l, ArrayView<U> r);

/// true if l and r refer to exactly the same range.
template <typename T, typename U,
         typename = std::enable_if_t<std::is_same_v<std::remove_cv<T>,std::remove_cv<U>>
             >>
    bool is_same(ArrayView<T> l, ArrayView<U> r);

}
