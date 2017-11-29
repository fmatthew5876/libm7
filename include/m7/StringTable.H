#pragma once
#include <cstddef>
#include <cstdint>
#include <m7/StringTableDef.H>

namespace m7 {

inline StringTable::StringTable(size_t page_size)
    : _page_size(std::max(page_size, kMinPageSize))
{}

inline StringTable::StringTable(StringTable&& o) noexcept
: _head(o._head)
, _page_size(o._page_size)
{
    o._head = nullptr;
}

inline StringTable& StringTable::operator=(StringTable&& o) noexcept {
    if (this != &o) {
        clear();
        swap(o);
    }
    return *this;
}

inline StringTable::~StringTable() {
    clear();
}

/// Swap operation.
inline void StringTable::swap(StringTable& o) noexcept {
    using std::swap;
    swap(_head, o._head);
    swap(_page_size, o._page_size);
}

}  // namespace m7
