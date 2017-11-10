#include <m7/AllocatorDeleterDef.H>

namespace m7 {

template <typename Alloc>
AllocatorDeleter<Alloc>::AllocatorDeleter(Alloc* alloc)
: _alloc(alloc)
{
}

template <typename Alloc>
template <typename T>
inline void AllocatorDeleter<Alloc>::operator()(T* p) const {
    _alloc->free(p);
}

} //namespace m7
