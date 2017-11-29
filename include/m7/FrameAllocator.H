#pragma once
#include <m7/ScopeGuard.H>
#include <m7/FrameAllocatorDef.H>
#include <m7/AllocatorDeleter.H>

namespace m7 {

inline FrameAllocator::FrameAllocator(FrameAllocator&& o) noexcept
    : _data(o._data)
    , _next(o._next)
    , _end(o._end)
    {
    }

inline FrameAllocator& FrameAllocator::operator=(FrameAllocator&& o) noexcept {
    if(this != &o) {
        _reset();
        this->swap(o);
    }
    return *this;
}

void FrameAllocator::swap(FrameAllocator& o) noexcept {
    using std::swap;
    swap(_data, o._data);
    swap(_next, o._next);
    swap(_end, o._end);
}

FrameAllocator::~FrameAllocator() {
    _reset();
}


template <typename T>
    inline T* FrameAllocator::alloc() {
        void* p = alloc(sizeof(T), alignof(T));
        return reinterpret_cast<T*>(p);
    }

inline void FrameAllocator::free(void*) noexcept {
}

template <typename T, typename... Args>
inline FrameAllocatorUniquePtr<T> FrameAllocator::make(Args&&... args) {
    auto* p = this->template alloc<T>();
    auto sg = makeScopeGuard([&]() { this->free(p); });
    new (p) T(std::forward<Args>(args)...);
    sg.dismiss();
    return FrameAllocatorUniquePtr<T>(p, FrameAllocatorDeleter(this));
}


inline size_t FrameAllocator::bytes_allocated() const {
    return uintptr_t(_end) - uintptr_t(_data);
}

inline size_t FrameAllocator::bytes_used() const {
    return uintptr_t(_next) - uintptr_t(_data);
}

inline size_t FrameAllocator::bytes_free() const {
    return uintptr_t(_end) - uintptr_t(_next);
}

} //namespace m7
