#include <gtest/gtest.h>
#include <m7/PagedPoolAllocator.H>

using namespace m7;

template <typename T, size_t N>
void test_alloc(int nobjs_per_page) {

    auto p = PagedPoolAllocator<T>(nobjs_per_page);

    std::array<T*, N> ptrs;

    auto alloc_fwd = [&p](auto& ptrs) {
        for(auto& ptr: ptrs) {
            ptr = p.alloc();
        }
    };

    alloc_fwd(ptrs);

    for(auto& ptr: ptrs) {
        p.free(ptr);
    }

    alloc_fwd(ptrs);

    for(auto iter = ptrs.rbegin(); iter != ptrs.rend(); ++iter) {
        p.free(*iter);
    }
}

TEST(PagedPoolAllocator, test) {
    test_alloc<int,31>(4);
    test_alloc<int,259>(500);
    test_alloc<int,147>(288);
    test_alloc<int,100>(50);
    test_alloc<int,7>(1);
}

TEST(PagedPoolAllocator, UniquePtr) {
    struct Obj {
        Obj(int x, float y, double z) : x(x), y(y), z(z) {}
        int x;
        float y;
        double z;
    };

    auto pool = PagedPoolAllocator<Obj>(20);
    auto ptr = pool.make(2, 3.0f, 50.0);
}
