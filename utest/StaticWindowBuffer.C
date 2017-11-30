#include <gtest/gtest.h>
#include <m7/StaticWindowBuffer.H>

using namespace m7;

template <size_t N>
void test_construct() {
    auto w = StaticWindowBuffer<int, N>();

    ASSERT_GE(w.size(), N);
    ASSERT_FALSE(w.empty());

    for(size_t i = 0; i < w.size(); ++i) {
        ASSERT_EQ(w[i], int());
    }

}

TEST(StaticWindowBuffer, construct_size) {
    test_construct<1>();
    test_construct<2>();
    test_construct<4>();
    test_construct<8>();
    test_construct<16>();
}

TEST(StaticWindowBuffer, push_front) {
    auto w = StaticWindowBuffer<int, 4>();

    w.push_front(1);

    ASSERT_EQ(w[0], 1);
    ASSERT_EQ(w[1], 0);
    ASSERT_EQ(w[2], 0);
    ASSERT_EQ(w[3], 0);

    w.push_front(2);

    ASSERT_EQ(w[0], 2);
    ASSERT_EQ(w[1], 1);
    ASSERT_EQ(w[2], 0);
    ASSERT_EQ(w[3], 0);

    w.push_front(3);

    ASSERT_EQ(w[0], 3);
    ASSERT_EQ(w[1], 2);
    ASSERT_EQ(w[2], 1);
    ASSERT_EQ(w[3], 0);

    w.push_front(4);

    ASSERT_EQ(w[0], 4);
    ASSERT_EQ(w[1], 3);
    ASSERT_EQ(w[2], 2);
    ASSERT_EQ(w[3], 1);

    w.push_front(5);

    ASSERT_EQ(w[0], 5);
    ASSERT_EQ(w[1], 4);
    ASSERT_EQ(w[2], 3);
    ASSERT_EQ(w[3], 2);
}
