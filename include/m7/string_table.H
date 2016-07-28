#pragma once
#include <cstddef>
#include <cstdint>
#include <m7/string_view.H>

namespace m7 {

class StringTable {
       public:
	static constexpr size_t kMinPageSize = 4096;
	static constexpr size_t kDefaultPageSize = 8182;

	StringTable(size_t page_size = 8096)
	    : _page_size(std::max(page_size, kMinPageSize)) {}
	StringTable(const StringTable&) = delete;
	StringTable& operator=(const StringTable&) = delete;

	StringTable(StringTable&& o) noexcept : _head(o._head),
						_page_size(o._page_size) {
		o._head = nullptr;
	}
	StringTable& operator=(StringTable&& o) noexcept {
		if (this != &o) {
			clear();
			swap(o);
		}
		return *this;
	}
	~StringTable() { clear(); }

	void swap(StringTable& o) noexcept {
		using std::swap;
		swap(_head, o._head);
		swap(_page_size, o._page_size);
	}

	StringView store(StringView s);
	void clear() noexcept;

       private:
	struct Page {
		Page* next = nullptr;
		size_t remain = 0;
		char data[1];
	};
	Page* _head = nullptr;
	size_t _page_size = 0;

       private:
};

}  // namespace m7
