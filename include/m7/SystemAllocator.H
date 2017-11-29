#include <m7/SystemAllocatorDef.H>
#include <new>
#include <cstddef>

namespace m7 {


void* SystemAllocator::alloc(size_t size_bytes, size_t align) {
    return ::operator new(size_bytes, std::align_val_t(align));
}

template <typename T>
    T* SystemAllocator::alloc(size_t n) {
        return alloc(sizeof(T) * n, alignof(T));
    }

void SystemAllocator::free(void* p, size_t size_bytes, size_t align) {
    ::operator delete(p, size_bytes, std::align_val_t(align));
}

template <typename T>
void SystemAllocator::free(T* p, size_t n) {
    free(p, sizeof(T) * n, alignof(T));
}


}
