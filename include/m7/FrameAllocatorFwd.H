#pragma once
#include <memory>
#include <m7/AllocatorDeleterFwd.H>
#include <exception>

namespace m7 {

class FrameAllocator;
using FrameAllocatorDeleter = AllocatorDeleter<FrameAllocator>;

template <typename T>
using FrameAllocatorUniquePtr = std::unique_ptr<T, FrameAllocatorDeleter>;

using FrameAllocatorOverflowError = std::runtime_error;

} //namespace m7
