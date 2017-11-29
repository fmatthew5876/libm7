#include <m7/SystemAllocatorDef.H>
#include <new>
#include <cstddef>

namespace m7 {

template <typename T,
         std::enable_if_t<!std::is_void_v<T>>>
    inline T* SystemAllocator::alloc(size_t n) {
        return alloc(sizeof(T) * n, alignof(T));
    }

template <typename T,
         std::enable_if_t<!std::is_void_v<T>>>
inline void SystemAllocator::free(T* p, size_t n) noexcept {
    void* raw_p = p;
    free(raw_p, sizeof(T) * n, alignof(T));
}

inline void* SystemAllocator::alloc(size_t size_bytes, size_t align) {
    return ::operator new(size_bytes, std::align_val_t(align));
}

inline void SystemAllocator::free(void* p, size_t size_bytes, size_t align) noexcept {
    ::operator delete(p, size_bytes, std::align_val_t(align));
}

inline void* SystemAllocator::alloc(size_t size_bytes) {
    return ::operator new(size_bytes);
}

inline void SystemAllocator::free(void* p, size_t size_bytes) noexcept {
    ::operator delete(p, size_bytes);
}

inline void SystemAllocator::free(void* p) noexcept {
    ::operator delete(p);
}




}
