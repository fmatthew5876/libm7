#include <cstring>
#include <m7/StringTable.H>
#include <m7/SystemAllocator.H>

namespace m7 {

void StringTable::clear() noexcept {
	auto* p = _head;
	while (p != nullptr) {
		auto* n = p->next;
        //We don't know the size of the page here...
        SystemAllocator::free(p);
		p = n;
	}
	_head = nullptr;
}

std::string_view StringTable::store(std::string_view s) {
	if (s.empty()) {
		return std::string_view("");
	}
	static constexpr size_t kPageOverhead = offsetof(Page, data);

	auto len = s.length();
	auto len_z = len + 1;

	Page* pp = nullptr;
	Page* p = nullptr;
	Page* np = _head;

	// Find the first page (np) too small for the string.
	while (np != nullptr && np->remain >= len_z) {
		pp = p;
		p = np;
		np = np->next;
	}

	char* ret = nullptr;
	if (p == nullptr) {
		// No pages available which can fit the string, so allocate a
		// new one.
        // Oversized strings will always live in their own page.
		auto alloc_size = std::max(_page_size, len_z + kPageOverhead);
		p = reinterpret_cast<Page*>(SystemAllocator::alloc(alloc_size));
		ret = p->data;
		p->remain = alloc_size - kPageOverhead - len_z;

		// splice into list at the head.
		pp = nullptr;
		np = p->next = _head;
		_head = p;
	} else {
		auto off = _page_size - kPageOverhead - p->remain;
		ret = p->data + off;
		p->remain -= len_z;
	}
	std::memcpy(ret, s.data(), s.length());
	ret[s.length()] = '\0';

	auto* const oldparent = pp;
	auto* const page = p;

	// Find the new position for the page.
	while (np != nullptr && page->remain < np->remain) {
		pp = p;
		p = np;
		np = np->next;
	}

    if(page != p) {
        // Splice out of old position
        if (oldparent != nullptr) {
            oldparent->next = page->next;
        } else {
            _head = page->next;
        }

        // Splice into new position
        page->next = np;
        p->next = page;
    }

	return std::string_view(ret, s.length());
}

}  // namespace m7
