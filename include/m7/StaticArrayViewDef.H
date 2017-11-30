#pragma once
#include <m7/StaticArrayViewFwd.H>
#include <m7/meta.H>
#include <iterator>
#include <array>

namespace m7 {

template <typename T, size_t N>
    class StaticArrayView {
        public:
            using value_type = T;
            using iterator = T*;
            using reverse_iterator = std::reverse_iterator<iterator>;

            StaticArrayView() = delete;

            explicit StaticArrayView(T* b);

            StaticArrayView(const StaticArrayView&) = default;
            StaticArrayView& operator=(const StaticArrayView&) = default;

            template <typename U,
                     typename = std::enable_if_t<meta::isCvConvertible<T, U>>
                     >
            explicit StaticArrayView(StaticArrayView<U,N> v);

            template <typename U,
                     typename = std::enable_if_t<meta::isCvConvertible<T, U>>
                     >
            explicit StaticArrayView(std::array<U, N>& a);

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

            static constexpr bool empty();
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

template <typename T, size_t N, size_t M> bool operator==(StaticArrayView<T, N> l, StaticArrayView<T, M> r);
template <typename T, size_t N, size_t M> bool operator!=(StaticArrayView<T, N> l, StaticArrayView<T, M> r);
template <typename T, size_t N, size_t M> bool operator<(StaticArrayView<T, N> l, StaticArrayView<T, M> r);
template <typename T, size_t N, size_t M> bool operator<=(StaticArrayView<T, N> l, StaticArrayView<T, M> r);
template <typename T, size_t N, size_t M> bool operator>(StaticArrayView<T, N> l, StaticArrayView<T, M> r);
template <typename T, size_t N, size_t M> bool operator>=(StaticArrayView<T, N> l, StaticArrayView<T, M> r);

/// removes M elements from the front of v and returns the new view.
/// \pre M <= v.size()
template <size_t M, typename T, size_t N>
    constexpr StaticArrayView<T, N - M> remove_prefix(StaticArrayView<T, N> v);

/// removes M elements from the back of v and returns the new view.
/// \pre M <= v.size()
template <size_t M, typename T, size_t N>
    constexpr StaticArrayView<T, N - M> remove_suffix(StaticArrayView<T, N> v);

/// removes up to n elements from the front of v and returns the new view.
template <size_t M, typename T, size_t N>
    constexpr StaticArrayView<T, (M < N ? N - M: 0)> remove_prefix_trunc(StaticArrayView<T, N> v);

/// removes up to n elements from the back of v and returns the new view.
template <size_t M, typename T, size_t N>
    constexpr StaticArrayView<T, (M < N ? N - M: 0)> remove_suffix_trunc(StaticArrayView<T, N> v);

/// returns a sub-array starting at pos with size count.
/// \pre pos <= v.size() && pos + count <= v.size()
template <size_t Pos, size_t Count, typename T, size_t N>
    constexpr StaticArrayView<T, Count> slice(StaticArrayView<T, N> v);

/// returns a sub-array starting at pos with up to size count.
/// If pos >= v.size(), returns empty view.
/// If pos + count >= v.size(), returns a truncated view.
template <size_t Pos, size_t Count, typename T, size_t N>
    constexpr StaticArrayView<T, (Pos > N ? 0 : (Pos + Count > N ? N - Pos : Count))> slice_trunc(StaticArrayView<T, N> v);

/// true if inner is a subet of outer.
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
