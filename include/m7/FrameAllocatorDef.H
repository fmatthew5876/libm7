#pragma once
#include <m7/FrameAllocatorFwd.H>
#include <m7/AllocatorDeleterDef.H>

namespace m7 {

class FrameAllocator {
    public:
        explicit FrameAllocator(size_t frame_size_bytes);

        FrameAllocator(const FrameAllocator&) = delete;
        FrameAllocator& operator=(const FrameAllocator&) = delete;

        FrameAllocator(FrameAllocator&&) noexcept;
        FrameAllocator& operator=(FrameAllocator&&) noexcept;

        void swap(FrameAllocator& o) noexcept;

        ~FrameAllocator();

        template <typename T>
            T* alloc();

        void* alloc(size_t size, size_t align);
        void free(void* p) noexcept;

        template <typename T, typename... Args>
            FrameAllocatorUniquePtr<T> make(Args&&...);

        size_t bytes_allocated() const;
        size_t bytes_used() const;
        size_t bytes_free() const;
    private:
        void _reset() noexcept;

    private:
        void* _data = nullptr;
        void* _next = nullptr;
        void* _end = nullptr;
};

} //namespace m7
