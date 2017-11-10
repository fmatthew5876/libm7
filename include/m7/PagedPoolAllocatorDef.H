#pragma once

#include <m7/PagedPoolAllocatorFwd.H>
#include <m7/AllocatorDeleterDef.H>
#include <cstddef>

namespace m7 {

template <typename T>
    class PagedPoolAllocator {
        public:
            explicit PagedPoolAllocator(size_t nobjs_per_page);

            PagedPoolAllocator(const PagedPoolAllocator<T>&) = delete;
            PagedPoolAllocator<T>& operator=(const PagedPoolAllocator<T>&) = delete;

            PagedPoolAllocator(PagedPoolAllocator<T>&&) noexcept;
            PagedPoolAllocator<T>& operator=(PagedPoolAllocator<T>&&) noexcept;

            void swap(PagedPoolAllocator<T>& o) noexcept;

            ~PagedPoolAllocator();

            T* alloc();
            void free(T* p) noexcept;

            template <typename... Args>
                PagedPoolAllocatorUniquePtr<T> make(Args&&...);
        private:
            union Slot {
                T obj;
                Slot* freenext;
            };
            struct Page {
                Page* next;
                Slot first_slot;
            };
        private:
            void _alloc_new_page();
            void _reset() noexcept;
            size_t _pagesize_bytes() const noexcept;
        private:
            Page* _pagehead = nullptr;
            Slot* _freehead = nullptr;
            size_t _nobjs_per_page = 0;
    };

} //namespace m7

