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

            constexpr StaticArrayView() = default;

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

template <typename T, size_t N, size_t M> bool operator==(StaticArrayView<T, N> l, StaticArrayView<T, M> r);
template <typename T, size_t N, size_t M> bool operator!=(StaticArrayView<T, N> l, StaticArrayView<T, M> r);
template <typename T, size_t N, size_t M> bool operator<(StaticArrayView<T, N> l, StaticArrayView<T, M> r);
template <typename T, size_t N, size_t M> bool operator<=(StaticArrayView<T, N> l, StaticArrayView<T, M> r);
template <typename T, size_t N, size_t M> bool operator>(StaticArrayView<T, N> l, StaticArrayView<T, M> r);
template <typename T, size_t N, size_t M> bool operator>=(StaticArrayView<T, N> l, StaticArrayView<T, M> r);


} //namespace m7
