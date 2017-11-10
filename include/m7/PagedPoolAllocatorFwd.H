#pragma once
#include <memory>
#include <m7/AllocatorDeleterFwd.H>

namespace m7 {

template <typename T> class PagedPoolAllocator;
template <typename T> using PagedPoolAllocatorDeleter = AllocatorDeleter<PagedPoolAllocator<T>>;

template <typename T>
using PagedPoolAllocatorUniquePtr = std::unique_ptr<T, PagedPoolAllocatorDeleter<T>>;

}
