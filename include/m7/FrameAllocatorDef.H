#pragma once
#include <m7/FrameAllocatorFwd.H>
#include <m7/AllocatorDeleterDef.H>

namespace m7 {

class FrameAllocator {
    public:
        ///If frame_size_bytes == 0, does nothing.
        ///Otherwise, allocates frame_size_bytes bytes from m7::SystemAllocator to create the frame.
        explicit FrameAllocator(size_t frame_size_bytes);

        FrameAllocator(const FrameAllocator&) = delete;
        FrameAllocator& operator=(const FrameAllocator&) = delete;

        ///This takes ownership of the memory managed by o.
        FrameAllocator(FrameAllocator&& o) noexcept;

        ///This takes ownership of the memory managed by o.
        FrameAllocator& operator=(FrameAllocator&& o) noexcept;

        ///Swap ownership of frames between this and o.
        void swap(FrameAllocator& o) noexcept;

        ///Frees all memory used by the underlying frame.
        ///Will not destroy any objects that were allocated by this.
        ~FrameAllocator();

        ///Allocates and returns a pointer to n uninitialized T objects.
        ///\throw FrameAllocatorOverflowError if there is not enough space remaining to satisfy the allocation.
        template <typename T>
            T* alloc(size_t n=1);

        ///Allocates and returns a void pointer to size bytes aligned at align.
        ///\throw FrameAllocatorOverflowError if there is not enough space remaining to satisfy the allocation.
        void* alloc(size_t size, size_t align);

        ///Does nothing.
        void free(void* p) noexcept;

        ///Create a unique_ptr.
        template <typename T, typename... Args>
            FrameAllocatorUniquePtr<T> make(Args&&...);

        ///The size of the underlying frame in bytes.
        size_t frame_bytes() const;

        ///Number of bytes allocated from this frame.
        size_t bytes_used() const;

        ///Number of bytes remaining for future allocations from this frame.
        size_t bytes_free() const;
    private:
        void _reset() noexcept;

    private:
        void* _data = nullptr;
        void* _next = nullptr;
        void* _end = nullptr;
};

} //namespace m7
