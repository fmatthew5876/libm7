#include <gtest/gtest.h>
#include <m7/WindowBuffer.H>

using namespace m7;

TEST(WindowBuffer, default_construct) {
    auto w = WindowBuffer<int>();

    ASSERT_EQ(w.size(), 0u);
    ASSERT_TRUE(w.empty());
}

TEST(WindowBuffer, construct_size) {
    for(size_t size: { 1, 2, 3, 43, 67, 256, 340, 512, 970, 134352 }) {
        auto w = WindowBuffer<int>(size);

        ASSERT_GE(w.size(), size);
        ASSERT_FALSE(w.empty());

        for(size_t i = 0; i < w.size(); ++i) {
            ASSERT_EQ(w[i], int());
        }
    }
}

TEST(WindowBuffer, construct_size_val) {
    for(size_t size: { 1, 2, 3, 43, 67, 256, 340, 512, 970, 134352 }) {
        auto w = WindowBuffer<int>(size, 5);

        ASSERT_GE(w.size(), size);
        ASSERT_FALSE(w.empty());

        for(size_t i = 0; i < w.size(); ++i) {
            ASSERT_EQ(w[i], 5);
        }
    }
}

TEST(WindowBuffer, move) {
    auto w0 = WindowBuffer<int>(3);

    w0.push_front(1);
    w0.push_front(2);
    w0.push_front(3);

    auto w1 = WindowBuffer<int>(5);

    w1.push_front(4);
    w1.push_front(5);

    auto w1_size = w1.size();

    w0 = std::move(w1);

    ASSERT_EQ(w0.size(), w1_size);
    ASSERT_EQ(w0[0], 5);
    ASSERT_EQ(w0[1], 4);

    ASSERT_EQ(w1.size(), 0u);
    ASSERT_TRUE(w1.empty());

    auto w2 = WindowBuffer<int>(std::move(w0));

    ASSERT_EQ(w2.size(), w1_size);
    ASSERT_EQ(w2[0], 5);
    ASSERT_EQ(w2[1], 4);

    ASSERT_EQ(w0.size(), 0u);
    ASSERT_TRUE(w0.empty());
}

TEST(WindowBuffer, copy) {
    auto w0 = WindowBuffer<int>(3);

    w0.push_front(1);
    w0.push_front(2);
    w0.push_front(3);

    auto w1 = WindowBuffer<int>(w0);

    ASSERT_EQ(w0.size(), w1.size());
    ASSERT_EQ(w0[0], w1[0]);
    ASSERT_EQ(w0[1], w1[1]);
    ASSERT_EQ(w0[2], w1[2]);

    auto w2 = WindowBuffer<int>();

    ASSERT_TRUE(w2.empty());

    w2 = w1;

    ASSERT_EQ(w2.size(), w1.size());
    ASSERT_EQ(w2[0], w1[0]);
    ASSERT_EQ(w2[1], w1[1]);
    ASSERT_EQ(w2[2], w1[2]);
}

TEST(WindowBuffer, swap) {
    auto w0 = WindowBuffer<int>(3);
    auto w1 = WindowBuffer<int>(87);

    auto w0_size = w0.size();
    auto w1_size = w1.size();

    //This is necessary for the later size checks to make sense.
    ASSERT_NE(w0_size, w1_size);

    w0.push_front(1);
    w0.push_front(2);
    w0.push_front(3);

    w1.push_front(4);
    w1.push_front(5);

    ASSERT_EQ(w0[0], 3);
    ASSERT_EQ(w0[1], 2);
    ASSERT_EQ(w0[2], 1);

    ASSERT_EQ(w1[0], 5);
    ASSERT_EQ(w1[1], 4);

    w0.swap(w1);

    ASSERT_EQ(w0.size(), w1_size);
    ASSERT_EQ(w1.size(), w0_size);

    ASSERT_EQ(w1[0], 3);
    ASSERT_EQ(w1[1], 2);
    ASSERT_EQ(w1[2], 1);

    ASSERT_EQ(w0[0], 5);
    ASSERT_EQ(w0[1], 4);
}

TEST(WindowBuffer, front_back) {
    auto w0 = WindowBuffer<int>(3);
    for(size_t i = 0; i < w0.size(); ++i) {
        w0.push_front(i);
    }

    ASSERT_EQ(w0.front(), int(w0.size())-1);
    ASSERT_EQ(w0.back(), 0);
}

TEST(WindowBuffer, push_front) {
    auto w = WindowBuffer<int>(4);

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

