#pragma once
#include <m7/StaticArrayViewFwd.H>
#include <m7/meta.H>
#include <iterator>
#include <array>

namespace m7 {

/// A view over a contiguous range of data with a static size.
template <typename T, size_t N>
    class StaticArrayView {
        public:
            using value_type = T;
            using iterator = T*;
            using reverse_iterator = std::reverse_iterator<iterator>;

            StaticArrayView() = delete;

            /// Constructs a view over [b, b + N)
            /// \pre n == 0 || b != nullptr
            /// \pre [b, b + n) must be a valid memory range.
            explicit StaticArrayView(T* b);

            /// Copy a view.
            StaticArrayView(const StaticArrayView&) = default;

            /// Copy a view.
            StaticArrayView& operator=(const StaticArrayView&) = default;

            /// Create view from other view.
            template <typename U,
                     typename = std::enable_if_t<meta::isCvConvertible<T, U>>
                     >
            explicit StaticArrayView(StaticArrayView<U,N> v);

            /// Create view from array.
            template <typename U,
                     typename = std::enable_if_t<meta::isCvConvertible<T, U>>
                     >
            explicit StaticArrayView(std::array<U, N>& a);

            /// Create view from C array.
            template <typename U,
                     typename = std::enable_if_t<meta::isCvConvertible<T, U>>
                     >
            explicit StaticArrayView(U (&a)[N]);

            /// Constructs a view over the given contiguous range R.
            /// \pre N < r.size().
            template <typename R,
                     typename = std::enable_if_t<
                         meta::isContiguousRange<std::remove_reference_t<R>>
                         && meta::isCvConvertible<T, meta::rangeValueType<std::remove_reference_t<R>>>
                         >
                         >
                explicit StaticArrayView(R&& r);

            /// Return the i'th element.
            /// \pre i < size()
            T& operator[](size_t i) const;

            /// Return the first element.
            /// \pre !empty()
            T& front() const;

            /// Return the last element.
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
            static constexpr bool empty();

            /// number of objects spanned by the view.
            static constexpr size_t size();

        private:
            T* _b = nullptr;
    };

template <typename T, size_t N>
StaticArrayView(std::array<T, N>& a) -> StaticArrayView<T, N>;

template <typename T, size_t N>
StaticArrayView(T (&a)[N]) -> StaticArrayView<T, N>;

#if 0
template <size_t N, typename R>
StaticArrayView(R&&) -> StaticArrayView<std::remove_pointer_t<meta::dataType<std::remove_reference_t<R>>>, N>;
#endif

/// true if the underlying ranges are equal.
template <typename T, size_t N, size_t M> bool operator==(StaticArrayView<T, N> l, StaticArrayView<T, M> r);

/// true if the underlying ranges are not equal.
template <typename T, size_t N, size_t M> bool operator!=(StaticArrayView<T, N> l, StaticArrayView<T, M> r);

/// lexicographical comparison on the underlying ranges.
template <typename T, size_t N, size_t M> bool operator<(StaticArrayView<T, N> l, StaticArrayView<T, M> r);

/// lexicographical comparison on the underlying ranges.
template <typename T, size_t N, size_t M> bool operator<=(StaticArrayView<T, N> l, StaticArrayView<T, M> r);

/// lexicographical comparison on the underlying ranges.
template <typename T, size_t N, size_t M> bool operator>(StaticArrayView<T, N> l, StaticArrayView<T, M> r);

/// lexicographical comparison on the underlying ranges.
template <typename T, size_t N, size_t M> bool operator>=(StaticArrayView<T, N> l, StaticArrayView<T, M> r);

/// removes M elements from the front of v and returns the new view.
/// \pre M <= v.size()
template <size_t M, typename T, size_t N>
    constexpr StaticArrayView<T, N - M> remove_prefix(StaticArrayView<T, N> v);

/// removes M elements from the back of v and returns the new view.
/// \pre M <= v.size()
template <size_t M, typename T, size_t N>
    constexpr StaticArrayView<T, N - M> remove_suffix(StaticArrayView<T, N> v);

/// removes up to M elements from the front of v and returns the new view.
template <size_t M, typename T, size_t N>
    constexpr StaticArrayView<T, (M < N ? N - M: 0)> remove_prefix_trunc(StaticArrayView<T, N> v);

/// removes up to M elements from the back of v and returns the new view.
template <size_t M, typename T, size_t N>
    constexpr StaticArrayView<T, (M < N ? N - M: 0)> remove_suffix_trunc(StaticArrayView<T, N> v);

/// returns a sub-array starting at Pos with size Count.
/// \pre Pos <= v.size() && Pos + Count <= v.size()
template <size_t Pos, size_t Count, typename T, size_t N>
    constexpr StaticArrayView<T, Count> slice(StaticArrayView<T, N> v);

/// returns a sub-array starting at Pos with up to size Count.
/// If Pos >= v.size(), returns empty view starting at v.end().
/// If Pos + Count >= v.size(), returns a truncated view.
template <size_t Pos, size_t Count, typename T, size_t N>
    constexpr StaticArrayView<T, (Pos > N ? 0 : (Pos + Count > N ? N - Pos : Count))> slice_trunc(StaticArrayView<T, N> v);

/// true if inner is a subset of outer.
template <typename T, typename U, size_t N, size_t M,
         typename = std::enable_if_t<std::is_same_v<std::remove_cv<T>,std::remove_cv<U>>
             >>
    constexpr bool is_subset(StaticArrayView<T, N> outer, StaticArrayView<U, M> inner);

/// true if l and r overlap over at least one object.
template <typename T, typename U, size_t N, size_t M,
         typename = std::enable_if_t<std::is_same_v<std::remove_cv<T>,std::remove_cv<U>>
             >>
    constexpr bool is_overlap(StaticArrayView<T, N> l, StaticArrayView<U, M> r);

/// true if l and r refer to exactly the same range.
template <typename T, typename U, size_t N, size_t M,
         typename = std::enable_if_t<std::is_same_v<std::remove_cv<T>,std::remove_cv<U>>
             >>
    constexpr bool is_same(StaticArrayView<T, N> l, StaticArrayView<U, M> r);



} //namespace m7
