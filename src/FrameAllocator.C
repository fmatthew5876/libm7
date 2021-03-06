#include <m7/FrameAllocator.H>
#include <m7/align.H>
#include <m7/SystemAllocator.H>
#include <exception>

namespace m7 {

static constexpr auto kFrameAllocatorAlign = alignof(std::max_align_t);

FrameAllocator::FrameAllocator(size_t frame_size_bytes) {
    if(frame_size_bytes == 0) {
        return;
    }
    _data = SystemAllocator::alloc(frame_size_bytes, kFrameAllocatorAlign);
    _next = _data;
    _end = reinterpret_cast<void*>(uintptr_t(_data) + frame_size_bytes);
}

void* FrameAllocator::alloc(size_t size, size_t align) {
    auto* b = align_up(_next, align);
    auto* e = reinterpret_cast<void*>(uintptr_t(b) + size);

    if(e > _end) {
        throw FrameAllocatorOverflowError();
    }
    _next = e;
    return b;
}

void FrameAllocator::_reset() noexcept {
    if(_data != nullptr) {
        SystemAllocator::free(_data, frame_bytes(), kFrameAllocatorAlign);
        _data = _next = _end = nullptr;
    }
}

FrameAllocatorOverflowError::FrameAllocatorOverflowError()
    : Exception("FrameAllocator: Memory Overflow")
{
}


}
