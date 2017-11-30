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

    auto v2 = remove_prefix(v, 2);
    ASSERT_EQ(v2.size(), 3u);
    ASSERT_FALSE(v2.empty());

    ASSERT_EQ(v2[0], 3);
    ASSERT_EQ(v2[1], 4);
    ASSERT_EQ(v2[2], 5);

    v.remove_prefix(2);
    ASSERT_EQ(v.size(), 3u);
    ASSERT_FALSE(v.empty());

    ASSERT_EQ(v[0], 3);
    ASSERT_EQ(v[1], 4);
    ASSERT_EQ(v[2], 5);

    v.remove_prefix(3);

    ASSERT_EQ(v.size(), 0u);
    ASSERT_TRUE(v.empty());

    v = ArrayView(a);

    v2 = remove_prefix_trunc(v, 3);

    ASSERT_EQ(v2.size(), 2u);
    ASSERT_EQ(v2[0], 4);
    ASSERT_EQ(v2[1], 5);

    v2 = remove_prefix_trunc(v, 4);

    ASSERT_EQ(v2.size(), 1u);
    ASSERT_EQ(v2[0], 5);

    v2 = remove_prefix_trunc(v, 5);

    ASSERT_EQ(v2.size(), 0u);
    ASSERT_TRUE(v2.empty());

    v2 = remove_prefix_trunc(v, 6);

    ASSERT_EQ(v2.size(), 0u);
    ASSERT_TRUE(v2.empty());

    v2 = remove_prefix_trunc(v, 9999);

    ASSERT_EQ(v2.size(), 0u);
    ASSERT_TRUE(v2.empty());

}

TEST(ArrayView, suffix) {
    int a[] = { 1, 2, 3, 4, 5 };

    auto v = ArrayView(a);

    ASSERT_EQ(v.size(), 5u);
    ASSERT_FALSE(v.empty());

    auto v2 = remove_suffix(v, 2);
    ASSERT_EQ(v2.size(), 3u);
    ASSERT_FALSE(v2.empty());

    ASSERT_EQ(v2[0], 1);
    ASSERT_EQ(v2[1], 2);
    ASSERT_EQ(v2[2], 3);


    v.remove_suffix(2);
    ASSERT_EQ(v.size(), 3u);
    ASSERT_FALSE(v.empty());

    ASSERT_EQ(v[0], 1);
    ASSERT_EQ(v[1], 2);
    ASSERT_EQ(v[2], 3);

    v.remove_suffix(3);

    ASSERT_EQ(v.size(), 0u);
    ASSERT_TRUE(v.empty());

    v = ArrayView(a);

    v2 = remove_suffix_trunc(v, 3);

    ASSERT_EQ(v2.size(), 2u);
    ASSERT_EQ(v2[0], 1);
    ASSERT_EQ(v2[1], 2);

    v2 = remove_suffix_trunc(v, 4);

    ASSERT_EQ(v2.size(), 1u);
    ASSERT_EQ(v2[0], 1);

    v2 = remove_suffix_trunc(v, 5);

    ASSERT_EQ(v2.size(), 0u);
    ASSERT_TRUE(v2.empty());

    v2 = remove_suffix_trunc(v, 6);

    ASSERT_EQ(v2.size(), 0u);
    ASSERT_TRUE(v2.empty());

    v2 = remove_suffix_trunc(v, 9999);

    ASSERT_EQ(v2.size(), 0u);
    ASSERT_TRUE(v2.empty());
}

TEST(ArrayView, slice) {
    int a[] = { 1, 2, 3, 4, 5 };

    auto v = ArrayView(a);

    ASSERT_EQ(v.size(), 5u);
    ASSERT_FALSE(v.empty());

    auto v2 = slice(v, 0, 5);

    ASSERT_EQ(v2.size(), v.size());
    ASSERT_EQ(v2.front(), v.front());
    ASSERT_EQ(v2.back(), v.back());

    v2 = slice(v, 0, 4);

    ASSERT_EQ(v2.size(), 4u);
    ASSERT_EQ(v2.front(), 1);
    ASSERT_EQ(v2.back(), 4);

    v2 = slice(v, 1, 4);

    ASSERT_EQ(v2.size(), 4u);
    ASSERT_EQ(v2.front(), 2);
    ASSERT_EQ(v2.back(), 5);

    v2 = slice(v, 2, 2);

    ASSERT_EQ(v2.size(), 2u);
    ASSERT_EQ(v2.front(), 3);
    ASSERT_EQ(v2.back(), 4);

    v2 = slice(v, 2, 0);

    ASSERT_EQ(v2.size(), 0u);
    ASSERT_TRUE(v2.empty());

    v2 = slice(v, 5, 0);

    ASSERT_EQ(v2.size(), 0u);
    ASSERT_TRUE(v2.empty());

    v2 = slice_trunc(v, 0, 5);

    ASSERT_EQ(v2.size(), v.size());
    ASSERT_EQ(v2.front(), v.front());
    ASSERT_EQ(v2.back(), v.back());

    v2 = slice_trunc(v, 0, 4);

    ASSERT_EQ(v2.size(), 4u);
    ASSERT_EQ(v2.front(), 1);
    ASSERT_EQ(v2.back(), 4);

    v2 = slice_trunc(v, 1, 4);

    ASSERT_EQ(v2.size(), 4u);
    ASSERT_EQ(v2.front(), 2);
    ASSERT_EQ(v2.back(), 5);

    v2 = slice_trunc(v, 2, 2);

    ASSERT_EQ(v2.size(), 2u);
    ASSERT_EQ(v2.front(), 3);
    ASSERT_EQ(v2.back(), 4);

    v2 = slice_trunc(v, 2, 0);

    ASSERT_EQ(v2.size(), 0u);
    ASSERT_TRUE(v2.empty());

    v2 = slice_trunc(v, 5, 0);

    ASSERT_EQ(v2.size(), 0u);
    ASSERT_TRUE(v2.empty());

    v2 = slice_trunc(v, 7, 0);

    ASSERT_EQ(v2.size(), 0u);
    ASSERT_TRUE(v2.empty());

    v2 = slice_trunc(v, 6, 4);

    ASSERT_EQ(v2.size(), 0u);
    ASSERT_TRUE(v2.empty());

    v2 = slice_trunc(v, 2, 80);

    ASSERT_EQ(v2.size(), 3u);
    ASSERT_EQ(v2.front(), 3);
    ASSERT_EQ(v2.back(), 5);

    v2 = slice_trunc(v, 0, 6);

    ASSERT_EQ(v2.size(), 5u);
    ASSERT_EQ(v2.front(), 1);
    ASSERT_EQ(v2.back(), 5);
}

TEST(ArrayView, subset) {
    int a0[] = { 1, 2, 3, 4, 5 };
    int a1[] = { 6, 7, 8, 9, 10 };

    auto v0 = ArrayView(a0);
    auto v1 = ArrayView(a1);

    ASSERT_TRUE(is_subset(v0, v0));
    ASSERT_TRUE(is_subset(v1, v1));
    ASSERT_FALSE(is_subset(v0, v1));

    auto v2 = remove_prefix(v0, 2);

    ASSERT_TRUE(is_subset(v0, v2));
    ASSERT_FALSE(is_subset(v1, v2));

    v2 = remove_suffix(v1, 2);

    ASSERT_FALSE(is_subset(v0, v2));
    ASSERT_TRUE(is_subset(v1, v2));

    v2 = ArrayView<int>();

    ASSERT_FALSE(is_subset(v0, v2));
    ASSERT_FALSE(is_subset(v1, v2));
}

TEST(ArrayView, overlap) {
    int a0[] = { 1, 2, 3, 4, 5 };
    int a1[] = { 6, 7, 8, 9, 10 };

    auto v0 = ArrayView(a0);
    auto v1 = ArrayView(a1);

    ASSERT_TRUE(is_overlap(v0, v0));
    ASSERT_TRUE(is_overlap(v1, v1));
    ASSERT_FALSE(is_overlap(v0, v1));

    auto v2 = remove_prefix(v0, 2);

    ASSERT_TRUE(is_overlap(v0, v2));
    ASSERT_FALSE(is_overlap(v1, v2));

    v2 = remove_suffix(v1, 2);

    ASSERT_FALSE(is_overlap(v0, v2));
    ASSERT_TRUE(is_overlap(v1, v2));

    v2 = ArrayView<int>();

    ASSERT_FALSE(is_overlap(v0, v2));
    ASSERT_FALSE(is_overlap(v1, v2));

    v2 = slice(v0, 0, 3);
    auto v3 = slice(v0, 2, 3);

    ASSERT_TRUE(is_overlap(v2, v3));

    v2.remove_suffix(1);

    ASSERT_FALSE(is_overlap(v2, v3));

    v3.remove_prefix(1);

    ASSERT_FALSE(is_overlap(v2, v3));
}

TEST(ArrayView, same) {
    int a0[] = { 1, 2, 3, 4, 5 };
    int a1[] = { 6, 7, 8, 9, 10 };

    auto v0 = ArrayView(a0);
    auto v1 = ArrayView(a1);

    ASSERT_TRUE(is_same(v0, v0));
    ASSERT_TRUE(is_same(v1, v1));
    ASSERT_FALSE(is_same(v0, v1));

    auto v2 = remove_prefix(v0, 2);

    ASSERT_FALSE(is_same(v0, v2));
    ASSERT_FALSE(is_same(v1, v2));

    v2 = remove_suffix(v1, 2);

    ASSERT_FALSE(is_same(v0, v2));
    ASSERT_FALSE(is_same(v1, v2));

    v2 = ArrayView(a0);
    auto v3 = ArrayView(a1);

    ASSERT_TRUE(is_same(v0, v2));
    ASSERT_TRUE(is_same(v1, v3));
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
