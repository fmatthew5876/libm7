#pragma once
#include <m7/WindowBufferFwd.H>
#include <m7/WindowIteratorFwd.H>
#include <m7/bitops.H>
#include <iterator>

namespace m7 {

///A circular buffer of fixed size. 
template <typename T>
class WindowBuffer {
    public:
        ///Type used for size an index calculations.
        using size_type = uint32_t;

        using iterator = WindowIterator<T>;
        using const_iterator = WindowIterator<const T>;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

        ///Create an empty buffer.
        explicit WindowBuffer() noexcept = default;

        ///Create a buffer of *at least* window_size T objects.
        ///Each T object in the initial buffer will be default constructed.
        ///If window_size == 0, does no allocations and creates an empty buffer.
        ///\note The resulting size() of this may end up larger than the requested window_size.
        explicit WindowBuffer(size_type window_size);

        ///Create a buffer of *at least* window_size T objects.
        ///Each T object in the initial buffer will be copy constructed from init.
        ///If window_size == 0, does no allocations and creates an empty buffer.
        ///\note The resulting size() of this may end up larger than the requested window_size.
        explicit WindowBuffer(size_type window_size, const T& init);

        ///Copy buffer from o
        WindowBuffer(const WindowBuffer& o);

        ///Destroy this and then copy buffer from o.
        WindowBuffer& operator=(const WindowBuffer& o);

        ///Move buffer from o
        ///\post o is empty.
        WindowBuffer(WindowBuffer&& o) noexcept;

        ///Destroy this and then move buffer from o.
        ///\post o is empty.
        WindowBuffer& operator=(WindowBuffer&& o) noexcept;

        ///Swap 2 buffers.
        void swap(WindowBuffer&) noexcept;

        ///Destroy the buffer.
        ~WindowBuffer();

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
        size_type size() const;

        ///true if the buffer is empty.
        bool empty() const;

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
        template <typename F>
            void _init(size_type window_size, F&& make, bool isp2);
        void _reset(size_type n) noexcept;

    private:
        T* _buf = nullptr;
        size_type _mask = std::numeric_limits<size_type>::max();
        size_type _p = 0;
};

} //namespace m7
