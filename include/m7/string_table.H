#pragma once
#include <cstddef>
#include <cstdint>
#include <m7/string_view.H>

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
	StringTable(size_t page_size = 8096)
	    : _page_size(std::max(page_size, kMinPageSize)) {}

	/// Non-copyable.
	StringTable(const StringTable&) = delete;
	/// Non-copyable.
	StringTable& operator=(const StringTable&) = delete;

	/// Transfer ownership.
	StringTable(StringTable&& o) noexcept : _head(o._head),
						_page_size(o._page_size) {
		o._head = nullptr;
	}

	/// Transfer ownership.
	StringTable& operator=(StringTable&& o) noexcept {
		if (this != &o) {
			clear();
			swap(o);
		}
		return *this;
	}

	/// Calls clear().
	~StringTable() { clear(); }

	/// Swap operation.
	void swap(StringTable& o) noexcept {
		using std::swap;
		swap(_head, o._head);
		swap(_page_size, o._page_size);
	}

	/// Make a copy of s and store it within the table. The resulting string
	/// is guaranteed to be null-terminated.
	StringView store(StringView s);

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

}  // namespace m7
