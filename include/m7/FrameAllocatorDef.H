#pragma once
#include <m7/FrameAllocatorFwd.H>
#include <m7/Exception.H>

namespace m7 {


//An allocator which allocates a single large block of memory on construction
//and then hands out chunks in order from beginning to end as requested by alloc().
//If the sequence of alloc() requests overflow the end of the frame an exception will be thrown.
//There is no free() method as memory used by the frame can never be reclaimed once allocated.
class FrameAllocator {
    public:
        ///If frame_size_bytes == 0, does nothing.
        ///Otherwise, allocates frame_size_bytes bytes from m7::SystemAllocator to create the frame.
        explicit FrameAllocator(size_t frame_size_bytes);

        FrameAllocator(const FrameAllocator&) = delete;
        FrameAllocator& operator=(const FrameAllocator&) = delete;

        ///This takes ownership of the memory managed by o.
        FrameAllocator(FrameAllocator&& o) noexcept;

        ///Destroys the frame currently owned by this.
        ///This takes ownership of the memory managed by o.
        FrameAllocator& operator=(FrameAllocator&& o) noexcept;

        ///Swap ownership of frames between this and o.
        void swap(FrameAllocator& o) noexcept;

        ///Destroys the frame currently owned by this.
        ///\note Will not destroy any objects that were allocated by this.
        ~FrameAllocator();

        ///Allocates and returns a pointer to n uninitialized T objects.
        ///\throw m7::FrameAllocatorOverflowError if there is not enough space remaining to satisfy the allocation.
        template <typename T>
            T* alloc(size_t n=1);

        ///Allocates and returns a void pointer to size bytes aligned at align.
        ///\throw m7::FrameAllocatorOverflowError if there is not enough space remaining to satisfy the allocation.
        void* alloc(size_t size, size_t align);

        ///Allocate and construct a T, returning it as a FrameAllocatorUniquePtr.
        ///\throw m7::FrameAllocatorOverflowError if there is not enough space remaining to satisfy the allocation.
        ///\post If the constructor to T throws, the memory will be reclaimed by
        ///      the underlying frame before the exception is propagated out.
        ///\note This memory reclaiming behavior is not possible from calling alloc() manually.
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

///Custom deleter for FrameAllocator.
class FrameAllocatorDeleter {
    public:
        template <typename T>
            void operator()(T* p) const;
    private:
};

//Exception class thrown when FrameAllocator::alloc() fails.
class FrameAllocatorOverflowError : public Exception {
    public:
        FrameAllocatorOverflowError();
    private:
};

} //namespace m7
