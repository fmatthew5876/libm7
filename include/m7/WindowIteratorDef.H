#pragma once
#include <m7/WindowIteratorFwd.H>
#include <iterator>
#include <limits>

namespace m7 {

template <typename T>
class WindowIterator
: public std::iterator<std::random_access_iterator_tag,T> {
    public:
        using size_type = uint32_t;
        using ssize_type = std::make_signed_t<size_type>;

        WindowIterator() = default;

        WindowIterator(T* b, size_type m, size_type i);

        WindowIterator& operator+=(ssize_type i);
        WindowIterator& operator-=(ssize_type i);
        WindowIterator& operator++();
        WindowIterator operator++(int);
        WindowIterator& operator--();
        WindowIterator operator--(int);

        T& operator*() const;
        T* operator->() const;
        T& operator[](size_type i) const;

        template <typename U>
        friend bool operator==(WindowIterator<U> l, WindowIterator<U> r);
        template <typename U>
        friend bool operator!=(WindowIterator<U> l, WindowIterator<U> r);
        template <typename U>
        friend bool operator<(WindowIterator<U> l, WindowIterator<U> r);
        template <typename U>
        friend bool operator<=(WindowIterator<U> l, WindowIterator<U> r);
        template <typename U>
        friend bool operator>(WindowIterator<U> l, WindowIterator<U> r);
        template <typename U>
        friend bool operator>=(WindowIterator<U> l, WindowIterator<U> r);

        template <typename U>
        friend WindowIterator<U> operator+(WindowIterator<U> l, typename WindowIterator<U>::ssize_type r);
        template <typename U>
        friend WindowIterator<U> operator+(typename WindowIterator<U>::ssize_type l, WindowIterator<U> r);
        template <typename U>
        friend WindowIterator<U> operator-(WindowIterator<U> l, typename WindowIterator<U>::ssize_type r);
        template <typename U>
        friend typename WindowIterator<U>::ssize_type operator-(WindowIterator<U> l, WindowIterator<U> r);


    private:
        T* _buf = nullptr;
        size_type _mask = std::numeric_limits<size_type>::max();
        size_type _i;
};

}
