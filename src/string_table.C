#include <cstring>
#include <m7/string_table.H>

namespace m7 {

void StringTable::clear() noexcept {
	auto* p = _head;
	while (p != nullptr) {
		auto* n = p->next;
		std::free(p);
		p = n;
	}
	_head = nullptr;
}

StringView StringTable::store(StringView s) {
	if (s.empty()) {
		return StringView("");
	}
	static constexpr size_t kPageOverhead = offsetof(Page, data);

	auto len = s.length();
	auto len_z = len + 1;

	Page* pp = nullptr;
	Page* p = nullptr;
	auto* np = _head;

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
		auto alloc_size = std::max(_page_size, len_z + kPageOverhead);
		p = reinterpret_cast<Page*>(std::malloc(alloc_size));
		if (p == nullptr) {
			throw std::bad_alloc();
		}
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

	auto* oldparent = pp;
	auto* page = p;

	// Find the new position for the page.
	while (np != nullptr && p->remain < np->remain) {
		pp = p;
		p = np;
		np = np->next;
	}

	// Splice out of old position
	if (oldparent != nullptr) {
		oldparent->next = page->next;
	} else {
		_head = page->next;
	}
	// Splice into new position
	page->next = np;
	pp->next = page;

	return StringView(ret, s.length());
}

}  // namespace m7
