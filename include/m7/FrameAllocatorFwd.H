#pragma once
#include <memory>
#include <m7/AllocatorDeleterFwd.H>

namespace m7 {

class FrameAllocator;
using FrameAllocatorDeleter = AllocatorDeleter<FrameAllocator>;

template <typename T>
using FrameAllocatorUniquePtr = std::unique_ptr<T, FrameAllocatorDeleter>;

} //namespace m7
