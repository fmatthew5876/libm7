#include <gtest/gtest.h>
#include <m7/WindowIterator.H>
#include <m7/WindowBuffer.H>
#include <m7/StaticWindowBuffer.H>

using namespace m7;

TEST(WindowIterator, EmptyWindowBuffer) {
    auto w = WindowBuffer<int>();

    ASSERT_EQ(w.begin(), w.end());
    ASSERT_EQ(w.cbegin(), w.cend());
    ASSERT_EQ(w.rbegin(), w.rend());
    ASSERT_EQ(w.crbegin(), w.crend());
}

template <typename B>
void test_buffer(B& w) {
    ASSERT_NE(w.begin(), w.end());
    ASSERT_EQ(w.begin() + w.size(), w.end());
    ASSERT_EQ(w.size() + w.begin(), w.end());
    ASSERT_EQ(w.begin(), w.end() - w.size());

    auto b = w.begin();
    b += w.size();

    ASSERT_EQ(b, w.end());

    auto e = w.end();
    e -= w.size();
    ASSERT_EQ(w.begin(), e);

    for(size_t i = w.size() * 2; i > 0;) {
        --i;
        w.push_front(i);
    }

    ASSERT_EQ(w.begin()[0], 0);
    ASSERT_EQ(w.begin()[1], 1);
    ASSERT_EQ(w.begin()[2], 2);
    ASSERT_EQ(w.begin()[3], 3);

    {
        ASSERT_NE(w.begin(), w.end());
        ASSERT_LE(w.begin(), w.end());
        ASSERT_LT(w.begin(), w.end());
        ASSERT_GE(w.end(), w.begin());
        ASSERT_GT(w.end(), w.begin());
        auto iter = w.begin();
        for(; iter != w.end(); ++iter) {
            ASSERT_EQ(*iter, int(iter - w.begin()));

            ASSERT_NE(iter, w.end());
            ASSERT_LE(iter, w.end());
            ASSERT_LT(iter, w.end());
            ASSERT_GE(w.end(), iter);
            ASSERT_GT(w.end(), iter);
        }

        ASSERT_EQ(iter, w.end());
        ASSERT_LE(w.begin(), iter);
        ASSERT_LT(w.begin(), iter);
        ASSERT_GE(iter, w.begin());
        ASSERT_GT(iter, w.begin());
    }

    {
        ASSERT_NE(w.cbegin(), w.cend());
        auto iter = w.cbegin();
        for(; iter != w.cend(); ++iter) {
            ASSERT_EQ(*iter, int(iter - w.cbegin()));

            ASSERT_NE(iter, w.cend());
            ASSERT_LE(iter, w.cend());
            ASSERT_LT(iter, w.cend());
            ASSERT_GE(w.cend(), iter);
            ASSERT_GT(w.cend(), iter);
        }
        ASSERT_EQ(iter, w.cend());
    }

    {
        ASSERT_NE(w.rbegin(), w.rend());
        auto iter = w.rbegin();
        for(; iter != w.rend(); ++iter) {
            ASSERT_EQ(*iter, int(w.size() - (iter - w.rbegin()) - 1));

            ASSERT_NE(iter, w.rend());
            ASSERT_LE(iter, w.rend());
            ASSERT_LT(iter, w.rend());
            ASSERT_GE(w.rend(), iter);
            ASSERT_GT(w.rend(), iter);
        }
        ASSERT_EQ(iter, w.rend());
    }

    {
        ASSERT_NE(w.crbegin(), w.crend());
        auto iter = w.crbegin();
        for(; iter != w.crend(); ++iter) {
            ASSERT_EQ(*iter, int(w.size() - (iter - w.crbegin()) - 1));

            ASSERT_NE(iter, w.crend());
            ASSERT_LE(iter, w.crend());
            ASSERT_LT(iter, w.crend());
            ASSERT_GE(w.crend(), iter);
            ASSERT_GT(w.crend(), iter);
        }
        ASSERT_EQ(iter, w.crend());
    }


}

TEST(WindowIterator, WindowBuffer) {
    auto w = WindowBuffer<int>(4);
    test_buffer(w);
}

TEST(WindowIterator, StaticWindowBuffer) {
    auto w = StaticWindowBuffer<int, 4>();
    test_buffer(w);
}
