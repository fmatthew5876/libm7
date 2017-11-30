#include <gtest/gtest.h>
#include <m7/ArrayView.H>

#include <vector>
#include <array>

using namespace m7;

template <typename T, typename Src>
void test_arrays(Src&& src) {
    using std::data;
    using std::size;
    using std::empty;

    ArrayView<T> from_ptr_view(data(src), size(src));
    ArrayView<T> constructed_view(src);
    ArrayView<T> assigned_view;
    assigned_view = ArrayView<T>(src);

    for(auto& view: { from_ptr_view, constructed_view, assigned_view }) {
        ASSERT_EQ(view.data(), data(src));
        ASSERT_EQ(view.size(), size(src));
        ASSERT_EQ(view.empty(), empty(src));

        if(!view.empty()) {
            ASSERT_EQ(view.front(), src[0]);
            ASSERT_EQ(view.back(), src[size(src)-1]);
        }

        for(size_t i = 0; i < view.size(); ++i) {
            ASSERT_EQ(view[i], src[i]);
        }
    }
}

TEST(ArrayView, make_vector0) {
    std::vector<int> v;
    test_arrays<int>(v);
    test_arrays<const int>(v);
    test_arrays<volatile int>(v);
    test_arrays<const volatile int>(v);
}

TEST(ArrayView, make_vector1) {
    std::vector<int> v = { 1, 2, 3, 4, 5 };
    test_arrays<int>(v);
    test_arrays<const int>(v);
    test_arrays<volatile int>(v);
    test_arrays<const volatile int>(v);
}

TEST(ArrayView, make_array0) {
    std::array<int, 3> a = {{ 1, 2, 3}};
    test_arrays<int>(a);
    test_arrays<const int>(a);
    test_arrays<volatile int>(a);
    test_arrays<const volatile int>(a);
}


TEST(ArrayView, make_array1) {
    std::array<const int, 3> a = {{ 1, 2, 3}};
    test_arrays<const int>(a);
    test_arrays<const volatile int>(a);
}

TEST(ArrayView, make_array2) {
    std::array<volatile int, 3> a = {{ 1, 2, 3}};
    test_arrays<volatile int>(a);
    test_arrays<const volatile int>(a);
}

TEST(ArrayView, make_array3) {
    std::array<const volatile int, 3> a = {{ 1, 2, 3}};
    test_arrays<const volatile int>(a);
}

TEST(ArrayView, make_carray0) {
    int a[] = { 1, 2, 3};
    test_arrays<int>(a);
    test_arrays<const int>(a);
    test_arrays<volatile int>(a);
    test_arrays<const volatile int>(a);
}


TEST(ArrayView, make_carray1) {
    const int a[] = { 1, 2, 3};
    test_arrays<const int>(a);
    test_arrays<const volatile int>(a);
}

TEST(ArrayView, make_carray2) {
    volatile int a[] = { 1, 2, 3};
    test_arrays<volatile int>(a);
    test_arrays<const volatile int>(a);
}

TEST(ArrayView, make_carray3) {
    const volatile int a[] = { 1, 2, 3};
    test_arrays<const volatile int>(a);
}

TEST(ArrayView, make_view0) {
    int a[] = { 1, 2, 3};
    auto v = ArrayView(a);
    test_arrays<int>(v);
    test_arrays<const int>(v);
    test_arrays<volatile int>(v);
    test_arrays<const volatile int>(v);
}


TEST(ArrayView, make_view1) {
    const int a[] = { 1, 2, 3};
    auto v = ArrayView(a);
    test_arrays<const int>(v);
    test_arrays<const volatile int>(v);
}

TEST(ArrayView, make_view2) {
    volatile int a[] = { 1, 2, 3};
    auto v = ArrayView(a);
    test_arrays<volatile int>(v);
    test_arrays<const volatile int>(v);
}

TEST(ArrayView, make_view3) {
    const volatile int a[] = { 1, 2, 3};
    auto v = ArrayView(a);
    test_arrays<const volatile int>(v);
}



TEST(ArrayView, cmp) {
    int a[] = {1};
    int b[] = {1, 1};
    int c[] = {1, 2};
    int d[] = {1, 2};
    int e[] = {1, 4, 5};

    auto va = ArrayView(a);
    auto vb = ArrayView(b);
    auto vc = ArrayView(c);
    auto vd = ArrayView(d);
    auto ve = ArrayView(e);

    ASSERT_LT(va, vb);
    ASSERT_LE(va, vb);
    ASSERT_GT(vb, va);
    ASSERT_GE(vb, va);
    ASSERT_NE(va, vb);

    ASSERT_LT(vb, vc);
    ASSERT_LE(vb, vc);
    ASSERT_GT(vc, vb);
    ASSERT_GE(vc, vb);
    ASSERT_NE(vb, vc);

    ASSERT_EQ(vc, vd);

    ASSERT_LT(vd, ve);
    ASSERT_LE(vd, ve);
    ASSERT_GT(ve, vd);
    ASSERT_GE(ve, vd);
    ASSERT_NE(vd, ve);
}

TEST(ArrayView, prefix) {
    int a[] = { 1, 2, 3, 4, 5 };

    auto v = ArrayView(a);

    ASSERT_EQ(v.size(), 5u);
    ASSERT_FALSE(v.empty());

    v.remove_prefix(2);
    ASSERT_EQ(v.size(), 3u);
    ASSERT_FALSE(v.empty());

    ASSERT_EQ(v[0], 3);
    ASSERT_EQ(v[1], 4);
    ASSERT_EQ(v[2], 5);

    v.remove_prefix(3);

    ASSERT_EQ(v.size(), 0u);
    ASSERT_TRUE(v.empty());
}

TEST(ArrayView, suffix) {
    int a[] = { 1, 2, 3, 4, 5 };

    auto v = ArrayView(a);

    ASSERT_EQ(v.size(), 5u);
    ASSERT_FALSE(v.empty());

    v.remove_suffix(2);
    ASSERT_EQ(v.size(), 3u);
    ASSERT_FALSE(v.empty());

    ASSERT_EQ(v[0], 1);
    ASSERT_EQ(v[1], 2);
    ASSERT_EQ(v[2], 3);

    v.remove_suffix(3);

    ASSERT_EQ(v.size(), 0u);
    ASSERT_TRUE(v.empty());
}

TEST(ArrayView, iter) {
    int a[] = { 1, 2, 3 };

    auto v = ArrayView(a);

    auto iter = v.begin();

    ASSERT_NE(iter, v.end());
    ASSERT_EQ(*iter, 1);

    ++iter;
    ASSERT_NE(iter, v.end());
    ASSERT_EQ(*iter, 2);

    ++iter;
    ASSERT_NE(iter, v.end());
    ASSERT_EQ(*iter, 3);

    ++iter;
    ASSERT_EQ(iter, v.end());
}

TEST(ArrayView, rev_iter) {
    int a[] = { 1, 2, 3 };

    auto v = ArrayView(a);

    auto iter = v.rbegin();

    ASSERT_NE(iter, v.rend());
    ASSERT_EQ(*iter, 3);

    ++iter;
    ASSERT_NE(iter, v.rend());
    ASSERT_EQ(*iter, 2);

    ++iter;
    ASSERT_NE(iter, v.rend());
    ASSERT_EQ(*iter, 1);

    ++iter;
    ASSERT_EQ(iter, v.rend());
}

TEST(ArrayView, CArrayView) {
    int a[] = { 1, 2, 3 };

    auto v = ArrayView(a);
    auto cv = CArrayView<int>(a);

    static_assert(std::is_same_v<decltype(v.data()),int*>, "ArrayView is broken!");
    static_assert(std::is_same_v<decltype(cv.data()),const int*>, "CArrayView is broken!");
}
