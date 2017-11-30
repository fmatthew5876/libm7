#include <gtest/gtest.h>
#include <m7/StaticArrayView.H>

#include <vector>
#include <array>

using namespace m7;

template <typename T, size_t N, typename Src>
void test_arrays(Src&& src) {
    using std::data;
    using std::size;
    using std::empty;

    StaticArrayView<T, N> from_ptr_view(data(src));
    StaticArrayView<T, N> constructed_view(src);
    StaticArrayView<T, N> assigned_view(src);
    assigned_view = StaticArrayView<T, N>(src);

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
    test_arrays<int, 0>(v);
    test_arrays<const int, 0>(v);
    test_arrays<volatile int, 0>(v);
    test_arrays<const volatile int, 0>(v);
}

TEST(ArrayView, make_vector1) {
    std::vector<int> v = { 1, 2, 3, 4, 5 };
    test_arrays<int, 5>(v);
    test_arrays<const int, 5>(v);
    test_arrays<volatile int, 5>(v);
    test_arrays<const volatile int, 5>(v);
}



TEST(StaticArrayView, make_array0) {
    std::array<int, 3> a = {{ 1, 2, 3}};
    test_arrays<int, 3>(a);
    test_arrays<const int, 3>(a);
    test_arrays<volatile int, 3>(a);
    test_arrays<const volatile int, 3>(a);
}


TEST(StaticArrayView, make_array1) {
    std::array<const int, 3> a = {{ 1, 2, 3}};
    test_arrays<const int, 3>(a);
    test_arrays<const volatile int, 3>(a);
}

TEST(StaticArrayView, make_array2) {
    std::array<volatile int, 3> a = {{ 1, 2, 3}};
    test_arrays<volatile int, 3>(a);
    test_arrays<const volatile int, 3>(a);
}

TEST(StaticArrayView, make_array3) {
    std::array<const volatile int, 3> a = {{ 1, 2, 3}};
    test_arrays<const volatile int, 3>(a);
}

TEST(StaticArrayView, make_carray0) {
    int a[] = { 1, 2, 3};
    test_arrays<int, 3>(a);
    test_arrays<const int, 3>(a);
    test_arrays<volatile int, 3>(a);
    test_arrays<const volatile int, 3>(a);
}


TEST(StaticArrayView, make_carray1) {
    const int a[] = { 1, 2, 3};
    test_arrays<const int, 3>(a);
    test_arrays<const volatile int, 3>(a);
}

TEST(StaticArrayView, make_carray2) {
    volatile int a[] = { 1, 2, 3};
    test_arrays<volatile int, 3>(a);
    test_arrays<const volatile int, 3>(a);
}

TEST(StaticArrayView, make_carray3) {
    const volatile int a[] = { 1, 2, 3};
    test_arrays<const volatile int, 3>(a);
}

TEST(StaticArrayView, make_view0) {
    int a[] = { 1, 2, 3};
    auto v = StaticArrayView(a);
    test_arrays<int, 3>(v);
    test_arrays<const int, 3>(v);
    test_arrays<volatile int, 3>(v);
    test_arrays<const volatile int, 3>(v);
}


TEST(StaticArrayView, make_view1) {
    const int a[] = { 1, 2, 3};
    auto v = StaticArrayView(a);
    test_arrays<const int, 3>(v);
    test_arrays<const volatile int, 3>(v);
}

TEST(StaticArrayView, make_view2) {
    volatile int a[] = { 1, 2, 3};
    auto v = StaticArrayView(a);
    test_arrays<volatile int, 3>(v);
    test_arrays<const volatile int, 3>(v);
}

TEST(StaticArrayView, make_view3) {
    const volatile int a[] = { 1, 2, 3};
    auto v = StaticArrayView(a);
    test_arrays<const volatile int, 3>(v);
}


TEST(StaticArrayView, cmp) {
    int a[] = {1};
    int b[] = {1, 1};
    int c[] = {1, 2};
    int d[] = {1, 2};
    int e[] = {1, 4, 5};

    auto va = StaticArrayView(a);
    auto vb = StaticArrayView(b);
    auto vc = StaticArrayView(c);
    auto vd = StaticArrayView(d);
    auto ve = StaticArrayView(e);

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

TEST(StaticArrayView, prefix) {
    int a[] = { 1, 2, 3, 4, 5 };

    auto v = StaticArrayView(a);

    ASSERT_EQ(v.size(), 5u);
    ASSERT_FALSE(v.empty());

    auto v2 = remove_prefix<2>(v);
    ASSERT_EQ(v2.size(), 3u);
    ASSERT_FALSE(v2.empty());

    ASSERT_EQ(v2[0], 3);
    ASSERT_EQ(v2[1], 4);
    ASSERT_EQ(v2[2], 5);

    auto v3 = remove_prefix<3>(v2);

    ASSERT_EQ(v3.size(), 0u);
    ASSERT_TRUE(v3.empty());

    auto v4 = remove_prefix_trunc<3>(v);

    ASSERT_EQ(v4.size(), 2u);
    ASSERT_EQ(v4[0], 4);
    ASSERT_EQ(v4[1], 5);

    auto v5 = remove_prefix_trunc<4>(v);

    ASSERT_EQ(v5.size(), 1u);
    ASSERT_EQ(v5[0], 5);

    auto v6 = remove_prefix_trunc<5>(v);

    ASSERT_EQ(v6.size(), 0u);
    ASSERT_TRUE(v6.empty());

    auto v7 = remove_prefix_trunc<6>(v);

    ASSERT_EQ(v7.size(), 0u);
    ASSERT_TRUE(v7.empty());

    auto v8 = remove_prefix_trunc<9999>(v);

    ASSERT_EQ(v8.size(), 0u);
    ASSERT_TRUE(v8.empty());

}

TEST(ArrayView, suffix) {
    int a[] = { 1, 2, 3, 4, 5 };

    auto v = StaticArrayView(a);

    ASSERT_EQ(v.size(), 5u);
    ASSERT_FALSE(v.empty());

    auto v2 = remove_suffix<2>(v);
    ASSERT_EQ(v2.size(), 3u);
    ASSERT_FALSE(v2.empty());

    ASSERT_EQ(v2[0], 1);
    ASSERT_EQ(v2[1], 2);
    ASSERT_EQ(v2[2], 3);

    auto v3 = remove_suffix<3>(v2);

    ASSERT_EQ(v3.size(), 0u);
    ASSERT_TRUE(v3.empty());

    auto v4 = remove_suffix_trunc<3>(v);

    ASSERT_EQ(v4.size(), 2u);
    ASSERT_EQ(v4[0], 1);
    ASSERT_EQ(v4[1], 2);

    auto v5 = remove_suffix_trunc<4>(v);

    ASSERT_EQ(v5.size(), 1u);
    ASSERT_EQ(v5[0], 1);

    auto v6 = remove_suffix_trunc<5>(v);

    ASSERT_EQ(v6.size(), 0u);
    ASSERT_TRUE(v6.empty());

    auto v7 = remove_suffix_trunc<6>(v);

    ASSERT_EQ(v7.size(), 0u);
    ASSERT_TRUE(v7.empty());

    auto v8 = remove_suffix_trunc<9999>(v);

    ASSERT_EQ(v8.size(), 0u);
    ASSERT_TRUE(v8.empty());
}

TEST(ArrayView, slice) {
    int a[] = { 1, 2, 3, 4, 5 };

    auto v = StaticArrayView(a);

    ASSERT_EQ(v.size(), 5u);
    ASSERT_FALSE(v.empty());

    auto v2 = slice<0, 5>(v);

    ASSERT_EQ(v2.size(), v.size());
    ASSERT_EQ(v2.front(), v.front());
    ASSERT_EQ(v2.back(), v.back());

    auto v3 = slice<0, 4>(v);

    ASSERT_EQ(v3.size(), 4u);
    ASSERT_EQ(v3.front(), 1);
    ASSERT_EQ(v3.back(), 4);

    auto v4 = slice<1, 4>(v);

    ASSERT_EQ(v4.size(), 4u);
    ASSERT_EQ(v4.front(), 2);
    ASSERT_EQ(v4.back(), 5);

    auto v5 = slice<2, 2>(v);

    ASSERT_EQ(v5.size(), 2u);
    ASSERT_EQ(v5.front(), 3);
    ASSERT_EQ(v5.back(), 4);

    auto v6 = slice<2, 0>(v);

    ASSERT_EQ(v6.size(), 0u);
    ASSERT_TRUE(v6.empty());

    auto v7 = slice<5, 0>(v);

    ASSERT_EQ(v7.size(), 0u);
    ASSERT_TRUE(v7.empty());

    auto v8 = slice_trunc<0, 5>(v);

    ASSERT_EQ(v8.size(), v.size());
    ASSERT_EQ(v8.front(), v.front());
    ASSERT_EQ(v8.back(), v.back());

    auto v9 = slice_trunc<0, 4>(v);

    ASSERT_EQ(v9.size(), 4u);
    ASSERT_EQ(v9.front(), 1);
    ASSERT_EQ(v9.back(), 4);

    auto va = slice_trunc<1, 4>(v);

    ASSERT_EQ(va.size(), 4u);
    ASSERT_EQ(va.front(), 2);
    ASSERT_EQ(va.back(), 5);

    auto vb = slice_trunc<2, 2>(v);

    ASSERT_EQ(vb.size(), 2u);
    ASSERT_EQ(vb.front(), 3);
    ASSERT_EQ(vb.back(), 4);

    auto vc = slice_trunc<2, 0>(v);

    ASSERT_EQ(vc.size(), 0u);
    ASSERT_TRUE(vc.empty());

    auto vd = slice_trunc<5, 0>(v);

    ASSERT_EQ(vd.size(), 0u);
    ASSERT_TRUE(vd.empty());

    auto ve = slice_trunc<7, 0>(v);

    ASSERT_EQ(ve.size(), 0u);
    ASSERT_TRUE(ve.empty());

    auto vf = slice_trunc<6, 4>(v);

    ASSERT_EQ(vf.size(), 0u);
    ASSERT_TRUE(vf.empty());

    auto vg = slice_trunc<2, 80>(v);

    ASSERT_EQ(vg.size(), 3u);
    ASSERT_EQ(vg.front(), 3);
    ASSERT_EQ(vg.back(), 5);

    auto vh = slice_trunc<0, 6>(v);

    ASSERT_EQ(vh.size(), 5u);
    ASSERT_EQ(vh.front(), 1);
    ASSERT_EQ(vh.back(), 5);
}

TEST(ArrayView, subset) {
    int a0[] = { 1, 2, 3, 4, 5 };
    int a1[] = { 6, 7, 8, 9, 10 };

    auto v0 = StaticArrayView(a0);
    auto v1 = StaticArrayView(a1);

    ASSERT_TRUE(is_subset(v0, v0));
    ASSERT_TRUE(is_subset(v1, v1));
    ASSERT_FALSE(is_subset(v0, v1));

    auto v2 = remove_prefix<2>(v0);

    ASSERT_TRUE(is_subset(v0, v2));
    ASSERT_FALSE(is_subset(v1, v2));

    auto v3 = remove_suffix<2>(v1);

    ASSERT_FALSE(is_subset(v0, v3));
    ASSERT_TRUE(is_subset(v1, v3));

    auto v4 = StaticArrayView<int, 0>(nullptr);

    ASSERT_FALSE(is_subset(v0, v4));
    ASSERT_FALSE(is_subset(v1, v4));
}

TEST(ArrayView, overlap) {
    int a0[] = { 1, 2, 3, 4, 5 };
    int a1[] = { 6, 7, 8, 9, 10 };

    auto v0 = StaticArrayView(a0);
    auto v1 = StaticArrayView(a1);

    ASSERT_TRUE(is_overlap(v0, v0));
    ASSERT_TRUE(is_overlap(v1, v1));
    ASSERT_FALSE(is_overlap(v0, v1));

    auto v2 = remove_prefix<2>(v0);

    ASSERT_TRUE(is_overlap(v0, v2));
    ASSERT_FALSE(is_overlap(v1, v2));

    auto v3 = remove_suffix<2>(v1);

    ASSERT_FALSE(is_overlap(v0, v3));
    ASSERT_TRUE(is_overlap(v1, v3));

    auto v4 = StaticArrayView<int,0>(nullptr);

    ASSERT_FALSE(is_overlap(v0, v4));
    ASSERT_FALSE(is_overlap(v1, v4));

    auto v5 = slice<0, 3>(v0);
    auto v6 = slice<2, 3>(v0);

    ASSERT_TRUE(is_overlap(v5, v6));

    auto v7 = remove_suffix<1>(v5);

    ASSERT_FALSE(is_overlap(v7, v6));

    auto v8 = remove_prefix<1>(v6);

    ASSERT_FALSE(is_overlap(v7, v8));
}

TEST(ArrayView, same) {
    int a0[] = { 1, 2, 3, 4, 5 };
    int a1[] = { 6, 7, 8, 9, 10 };

    auto v0 = StaticArrayView(a0);
    auto v1 = StaticArrayView(a1);

    ASSERT_TRUE(is_same(v0, v0));
    ASSERT_TRUE(is_same(v1, v1));
    ASSERT_FALSE(is_same(v0, v1));

    auto v2 = remove_prefix<2>(v0);

    ASSERT_FALSE(is_same(v0, v2));
    ASSERT_FALSE(is_same(v1, v2));

    auto v3 = remove_suffix<2>(v1);

    ASSERT_FALSE(is_same(v0, v3));
    ASSERT_FALSE(is_same(v1, v3));

    auto v4 = StaticArrayView(a0);
    auto v5 = StaticArrayView(a1);

    ASSERT_TRUE(is_same(v0, v4));
    ASSERT_TRUE(is_same(v1, v5));
}

TEST(StaticArrayView, iter) {
    int a[] = { 1, 2, 3 };

    auto v = StaticArrayView(a);

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

TEST(StaticArrayView, rev_iter) {
    int a[] = { 1, 2, 3 };

    auto v = StaticArrayView(a);

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

TEST(StaticArrayView, CStaticArrayView) {
    int a[] = { 1, 2, 3 };

    auto v = StaticArrayView(a);
    auto cv = CStaticArrayView<int, 3>(a);

    static_assert(std::is_same_v<decltype(v.data()),int*>, "StaticArrayView is broken!");
    static_assert(std::is_same_v<decltype(cv.data()),const int*>, "CStaticArrayView is broken!");
}
