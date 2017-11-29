#pragma once
#include <m7/SystemAllocatorFwd.H>

namespace m7 {

class SystemAllocator {
    public:
        ///Allocate memory for n T objects and returns pointer to n uninitialized T's.
        ///\note result must be deleted with free<T>(T*, n).
        template <typename T,
                 std::enable_if_t<!std::is_void_v<T>>>
            static T* alloc(size_t n=1);

        ///Free memory for n T objects.
        ///\pre p must have been allocated with alloc<T>(n).
        template <typename T,
                 std::enable_if_t<!std::is_void_v<T>>>
            static void free(T* p, size_t n=1) noexcept;

        ///Allocate size_bytes memory aligned to aligned.
        ///\note result must be deleted with free(p, size_bytes, align)
        static void* alloc(size_t size_bytes, size_t align);

        ///Free size_bytes memory aligned to aligned.
        ///\pre p must have been allocated with alloc(size_bytes, align).
        static void free(void* p, size_t size_bytes, size_t align) noexcept;

        ///Allocate size_bytes with default alignment.
        ///\note result must be deleted with either free(void*, size_bytes) (preferred) or free(void*).
        static void* alloc(size_t size_bytes);

        ///Free p with known size of size_bytes and default alignment.
        ///\pre p must have been allocated with alloc(size_bytes).
        static void free(void* p, size_t size_bytes) noexcept;

        ///Free p with unknown size and default alignment.
        ///\pre p must have been allocated with alloc(size_bytes).
        static void free(void* p) noexcept;

    private:
};

}

