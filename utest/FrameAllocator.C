#include <gtest/gtest.h>
#include <m7/FrameAllocator.H>
#include <exception>

using namespace m7;

template <typename T>
class TestObj {
    public:
        template <typename... Args>
        TestObj(Args&&...) { ++_count; }
        ~TestObj() { --_count; }

        static int count() { return _count; }
    private:
        static int _count;
    private:
        T _value = {};
};

struct ThrowObj {
    explicit ThrowObj(bool do_throw) {
        if(do_throw) {
            throw std::exception();
        }
    }
};

template <typename T>
int TestObj<T>::_count = 0;

void test_make_allocator(size_t size_bytes) {
    SCOPED_TRACE("size_bytes=(" + std::to_string(size_bytes) + ")");

    auto p = FrameAllocator(size_bytes);
    ASSERT_EQ(p.frame_bytes(), size_bytes);
    ASSERT_EQ(p.bytes_used(), size_t(0));
    ASSERT_EQ(p.bytes_free(), size_bytes);
}

template <typename T>
void test_alloc(int nobjs_in_frame, int nobjs_to_alloc) {

    auto size_bytes = nobjs_in_frame * sizeof(T);
    SCOPED_TRACE(
            "nobjs_in_frame=(" + std::to_string(nobjs_in_frame)
           + ", size_bytes=(" + std::to_string(size_bytes)
           + "), nobjs_to_alloc=(" + std::to_string(nobjs_to_alloc)
           + ")");

    auto p = FrameAllocator(size_bytes);
    ASSERT_EQ(p.frame_bytes(), size_bytes);
    ASSERT_EQ(p.bytes_used(), size_t(0));
    ASSERT_EQ(p.bytes_free(), size_bytes);

    std::vector<FrameAllocatorUniquePtr<TestObj<T>>> ptrs;

    for(int i = 0; i < nobjs_to_alloc; ++i) {
        ASSERT_EQ(TestObj<T>::count(), i);
        ptrs.push_back(p.template make<TestObj<T>>());
        ASSERT_EQ(TestObj<T>::count(), i + 1);
    }

    ptrs.clear();

    ASSERT_EQ(TestObj<T>::count(), 0);
}

TEST(FrameAllocator, make_many) {
    for(int i = 0; i < 4096; ++i) {
        test_make_allocator(i);
    }
}

TEST(FrameAllocator, throw_0_1) {
    EXPECT_THROW(test_alloc<int>(0, 1), FrameAllocatorOverflowError);
}

TEST(FrameAllocator, throw_1_2) {
    EXPECT_THROW(test_alloc<int>(1, 2), FrameAllocatorOverflowError);
}

TEST(FrameAllocator, throw_4_31) {
    EXPECT_THROW(test_alloc<int>(4, 31), FrameAllocatorOverflowError);
}

TEST(FrameAllocator, throw_50_100) {
    EXPECT_THROW(test_alloc<int>(50, 100), FrameAllocatorOverflowError);
}

TEST(FrameAllocator, alloc_1_1) {
    test_alloc<int>(1, 1);
}

TEST(FrameAllocator, alloc_2_1) {
    test_alloc<int>(2, 1);
}

TEST(FrameAllocator, alloc_3_2) {
    test_alloc<int>(3, 2);
}

TEST(FrameAllocator, alloc_45_44) {
    test_alloc<int>(45, 44);
}

TEST(FrameAllocator, alloc_45_1) {
    test_alloc<int>(45, 1);
}

TEST(FrameAllocator, alloc_500_500) {
    test_alloc<int>(500, 500);
}

TEST(FrameAllocator, alloc_288_147) {
    test_alloc<int>(288, 147);
}

TEST(FrameAllocator, alloc_1M_1M) {
    test_alloc<int>(0x100000, 0x100000);
}

TEST(FrameAllocator, free_on_throw_in_make) {
    auto pool = FrameAllocator(sizeof(ThrowObj) * 20);
    pool.template make<ThrowObj>(false);

    auto bytes_used_before_make = pool.bytes_used();
    auto bytes_free_before_make = pool.bytes_free();

    //When T() throws, make should reclaim the memory.
    EXPECT_ANY_THROW(pool.template make<ThrowObj>(true));

    ASSERT_EQ(pool.bytes_used(), bytes_used_before_make);
    ASSERT_EQ(pool.bytes_free(), bytes_free_before_make);

}
