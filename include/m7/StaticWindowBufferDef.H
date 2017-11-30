#pragma once
#include <m7/StaticWindowBufferFwd.H>
#include <m7/WindowIterator.H>
#include <m7/bitops.H>
#include <array>

namespace m7 {

template <typename T, size_t N>
    class StaticWindowBuffer {
        public:
            static_assert(ispow2(N), "N must be a power of 2!");

            ///Type used for size an index calculations.
            using size_type = uint32_t;

            using iterator = WindowIterator<T>;
            using const_iterator = WindowIterator<const T>;
            using reverse_iterator = std::reverse_iterator<iterator>;
            using const_reverse_iterator = std::reverse_iterator<const_iterator>;

            ///Create an empty buffer.
            StaticWindowBuffer() noexcept = default;

            ///Return i'th most recent value.
            ///\pre i < size()
            T& operator[](size_type i);

            ///Return i'th most recent value.
            ///\pre i < size()
            const T& operator[](size_type i) const;

            ///Return most recent value.
            T& front();

            ///Return most recent value.
            const T& front() const;

            ///Return oldest value.
            T& back();

            ///Return oldest value.
            const T& back() const;

            ///Return the size() of this buffer.
            static constexpr size_type size();

            ///true if the buffer is empty.
            static constexpr bool empty();

            ///Add a new T object to the front of the buffer.
            ///The last value is dropped.
            void push_front(T value);

            iterator begin();
            iterator end();

            const_iterator begin() const;
            const_iterator end() const;

            const_iterator cbegin() const;
            const_iterator cend() const;

            reverse_iterator rbegin();
            reverse_iterator rend();

            const_reverse_iterator rbegin() const;
            const_reverse_iterator rend() const;

            const_reverse_iterator crbegin() const;
            const_reverse_iterator crend() const;
        private:
            static constexpr size_type mask();

        private:
            std::array<T,N> _buf = {{}};
            size_type _p = 0;
    };

}
