#pragma once
#include <m7/SystemAllocatorFwd.H>

namespace m7 {

class SystemAllocator {
    public:
        static void* alloc(size_t size_bytes, size_t align);
        template <typename T>
            static T* alloc(size_t n=1);

        static void free(void* p, size_t size_bytes, size_t align);
        template <typename T>
            void free(T* p, size_t n=1);
    private:
};

}

