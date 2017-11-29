#pragma once
#include <m7/FrameAllocatorDef.H>
#include <m7/ScopeGuard.H>

namespace m7 {

template <typename T>
void FrameAllocatorDeleter::operator()(T* p) const {
    p->~T();
    //FrameAllocator has no free() method.
}

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
    inline T* FrameAllocator::alloc(size_t n) {
        void* p = alloc(sizeof(T) * n, alignof(T));
        return reinterpret_cast<T*>(p);
    }

template <typename T, typename... Args>
inline FrameAllocatorUniquePtr<T> FrameAllocator::make(Args&&... args) {
    auto* oldnext = _next;
    auto* p = this->template alloc<T>();

    //On error, reset the next pointer so that the memory is available for reuse.
    auto sg = make_scope_guard([&]() {
            _next = oldnext;
            });

    new (p) T(std::forward<Args>(args)...);
    auto up = FrameAllocatorUniquePtr<T>(p, FrameAllocatorDeleter());

    sg.dismiss();
    return up;
}


inline size_t FrameAllocator::frame_bytes() const {
    return uintptr_t(_end) - uintptr_t(_data);
}

inline size_t FrameAllocator::bytes_used() const {
    return uintptr_t(_next) - uintptr_t(_data);
}

inline size_t FrameAllocator::bytes_free() const {
    return uintptr_t(_end) - uintptr_t(_next);
}

} //namespace m7
