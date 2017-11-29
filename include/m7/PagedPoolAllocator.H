#pragma once
#include <m7/PagedPoolAllocatorDef.H>
#include <m7/SystemAllocator.H>
#include <m7/AllocatorDeleter.H>
#include <m7/ScopeGuard.H>
#include <m7/platform.H>

namespace m7 {

template <typename T>
    PagedPoolAllocator<T>::PagedPoolAllocator(size_t nobjs_per_page)
    : _nobjs_per_page(nobjs_per_page) {
    }

template <typename T>
    PagedPoolAllocator<T>::~PagedPoolAllocator() {
        _reset();
    }


template <typename T>
    PagedPoolAllocator<T>::PagedPoolAllocator(PagedPoolAllocator<T>&& o) noexcept
    : _pagehead(o._pagehead)
    , _freehead(o._freehead)
    , _nobjs_per_page(o._nobjs_per_page) {
        o._pagehead = o._freehead = nullptr;
}

template <typename T>
PagedPoolAllocator<T>& PagedPoolAllocator<T>::operator=(PagedPoolAllocator<T>&& o) noexcept {
    if(this != &o) {
        _reset();
        using std::swap;
        swap(_pagehead, o._pagehead);
        swap(_freehead, o._freehead);
        _nobjs_per_page = o._nobjs_per_page;
    }
    return *this;
}

template <typename T>
    void PagedPoolAllocator<T>::swap(PagedPoolAllocator<T>& o) noexcept {
        using std::swap;
        swap(_freehead, o._freehead);
        swap(_pagehead, o._pagehead);
        swap(_nobjs_per_page, o._nobjs_per_page);
    }

template <typename T>
    T* PagedPoolAllocator<T>::alloc() {
        if(M7_UNLIKELY(_freehead == nullptr)) {
            _alloc_new_page();
        }

        auto* slot = _freehead;
        _freehead = slot->freenext;

        return &slot->obj;
    }

template <typename T>
    void PagedPoolAllocator<T>::free(T* obj) noexcept {
        auto* slot = reinterpret_cast<Slot*>(obj);
        slot->freenext = _freehead;
        _freehead = slot;
    }

template <typename T>
    void PagedPoolAllocator<T>::_alloc_new_page() {
        auto* raw_page = SystemAllocator::alloc(_pagesize_bytes(), alignof(Page));
        auto* page = reinterpret_cast<Page*>(raw_page);
        page->next = nullptr;

        auto* slots = &page->first_slot;
        auto* last_slot = slots + (_nobjs_per_page -1);

        last_slot->freenext = _freehead;
        auto* prev = last_slot;
        for(size_t i = _nobjs_per_page-1; i > 0;) {
            --i;
            auto* slot = &slots[i];
            slot->freenext = prev;
            prev = slot;
        }

        _freehead = prev;
        page->next = _pagehead;
        _pagehead = page;
    }

template <typename T>
    inline size_t PagedPoolAllocator<T>::_pagesize_bytes() const noexcept {
        return sizeof(Page) + sizeof(Slot) * (_nobjs_per_page -1);
    }

template <typename T>
    void PagedPoolAllocator<T>::_reset() noexcept {
        for(auto* page = _pagehead; page != nullptr;) {
            auto* nextpage = page->next;
            SystemAllocator::free(page, _pagesize_bytes(), alignof(Page));
            page = nextpage;
        }
        _pagehead = nullptr;
        _freehead = nullptr;
    }

template <typename T>
template <typename... Args>
inline PagedPoolAllocatorUniquePtr<T> PagedPoolAllocator<T>::make(Args&&... args) {
    auto* p = this->alloc();

    auto sg = makeScopeGuard([&]() { this->free(p); });
    new (p) T(std::forward<Args>(args)...);
    sg.dismiss();

    return PagedPoolAllocatorUniquePtr<T>(p, PagedPoolAllocatorDeleter<T>(this));
}

} //namespace
