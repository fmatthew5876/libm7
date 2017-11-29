#pragma once
#include <string_view>
#include <cstddef>
#include <m7/StringTableFwd.H>

namespace m7 {

/// Provides efficient storage for read-only strings. Each string stored within
/// the table is valid until either the table is destroyed or clear() is called.
/// The table stores the strings internally in a linked list of pages. The page
/// size is configurable via the constructor.
class StringTable {
    public:
        /// The minimum allowed page size for string table.
        static constexpr size_t kMinPageSize = 4096;
        /// The default page size for default constructed string table.
        static constexpr size_t kDefaultPageSize = 8182;

        /// Construct with given page size.
        explicit StringTable(size_t page_size = kDefaultPageSize);

        /// Non-copyable.
        StringTable(const StringTable&) = delete;
        /// Non-copyable.
        StringTable& operator=(const StringTable&) = delete;

        /// Transfer ownership.
        /// \post o owns nothing.
        StringTable(StringTable&& o) noexcept;

        /// clear() this, and then transfer ownership.
        /// \post o owns nothing.
        StringTable& operator=(StringTable&& o) noexcept;

        /// Calls clear().
        ~StringTable();

        /// Swap operation.
        void swap(StringTable& o) noexcept;

        /// Make a copy of s and store it within the table. The resulting string
        /// is guaranteed to be null-terminated.
        std::string_view store(std::string_view s);

        /// Free all memory pages stored by this table.
        /// \post invalidates all references to strings stored in this.
        void clear() noexcept;

    private:
        struct Page {
            Page* next = nullptr;
            size_t remain = 0;
            char data[1];
        };
        Page* _head = nullptr;
        size_t _page_size = 0;
};

}
