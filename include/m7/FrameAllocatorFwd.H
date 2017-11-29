#pragma once
#include <memory>
#include <exception>

namespace m7 {

class FrameAllocator;
class FrameAllocatorDeleter;

template <typename T>
using FrameAllocatorUniquePtr = std::unique_ptr<T, FrameAllocatorDeleter>;

using FrameAllocatorOverflowError = std::runtime_error;

} //namespace m7
