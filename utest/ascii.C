#include <gtest/gtest.h>
#include <m7/ascii.H>
#include <m7/StringUtils.H>
#include <string_view>
#include <bitset>
#include <array>

using namespace m7;

using CharSet = std::bitset<256>;

CharSet make_set(std::string_view str) {
    CharSet s = {};
    for(auto c: str) {
        s[c] = true;
    }
    return s;
}

CharSet digit_set() {
    return make_set("0123456789");
}

CharSet xudigit_set() {
    return digit_set() | make_set("ABCDEF");
}

CharSet xldigit_set() {
    return digit_set() | make_set("abcdef");
}

CharSet xdigit_set() {
    return xldigit_set() | xudigit_set();
}

CharSet lower_set() {
    return make_set("abcdefghijkhlmnopqrstuvwxyz");
}

CharSet upper_set() {
    return make_set("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
}

CharSet alpha_set() {
    return lower_set() | upper_set();
}

CharSet alnum_set() {
    return alpha_set() | digit_set();
}

CharSet punct_set() {
    return make_set("!\"#$%&\'()*+,-./:;<=>?@[\\]^_`{|}~");
}

CharSet graph_set() {
    return alnum_set() | punct_set();
}

CharSet blank_set() {
    return make_set("\t ");
}

CharSet space_set() {
    return make_set("\t \r\n\v\f");
}

CharSet print_set() {
    return graph_set() | make_set(" ");
}

CharSet cntrl_set() {
    auto s = make_set("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B\x0C\x0C\x0D\x0E\x0F")
        | make_set("\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1A\x1B\x1C\x1C\x1D\x1E\x1F");
    s['\0'] = true;
    s['\x7F'] = true;
    return s;
}

template <typename F>
void test_is(F f, CharSet s) {
    for(size_t i = 0; i < s.size(); ++i) {
        auto c = char(i);

        ASSERT_EQ(f(c), s[i]) << "Char was: `" << c << "' (" << int(c) << ")";
    }
}

TEST(Ascii, digit) {
    test_is(m7::ascii::isdigit, digit_set());
}

TEST(Ascii, xudigit) {
    test_is(m7::ascii::isxudigit, xudigit_set());
}

TEST(Ascii, xldigit) {
    test_is(m7::ascii::isxldigit, xldigit_set());
}

TEST(Ascii, xdigit) {
    test_is(m7::ascii::isxdigit, xdigit_set());
}

TEST(Ascii, lower) {
    test_is(m7::ascii::islower, lower_set());
}

TEST(Ascii, upper) {
    test_is(m7::ascii::isupper, upper_set());
}

TEST(Ascii, alpha) {
    test_is(m7::ascii::isalpha, alpha_set());
}

TEST(Ascii, alnum) {
    test_is(m7::ascii::isalnum, alnum_set());
}

TEST(Ascii, punct) {
    test_is(m7::ascii::ispunct, punct_set());
}

TEST(Ascii, graph) {
    test_is(m7::ascii::isgraph, graph_set());
}

TEST(Ascii, blank) {
    test_is(m7::ascii::isblank, blank_set());
}

TEST(Ascii, space) {
    test_is(m7::ascii::isspace, space_set());
}

TEST(Ascii, print) {
    test_is(m7::ascii::isprint, print_set());
}

TEST(Ascii, cntrl) {
    test_is(m7::ascii::iscntrl, cntrl_set());
}

template <typename T>
using CharMap = std::array<T, 256>;

template <typename T>
void make_id_map(CharMap<T>& m) {
    for(size_t i = 0; i < m.size(); ++i) {
        m[i] = i;
    }
}

template <typename T, typename Vals>
void make_map(CharMap<T>& m, std::string_view chars, Vals&& vals) {
    ASSERT_EQ(chars.size(), std::size(vals)) << "BUG IN TEST CODE!";

    auto iter = std::begin(vals);
    for(size_t i = 0; i < chars.size(); ++i, ++iter) {
        auto c = size_t(chars[i]);
        m[c] = *iter;
    }
}

template <typename F, typename T, typename Filter>
void test_map(F f, const CharMap<T>& m, Filter filter) {
    for(size_t i = 0; i < m.size(); ++i) {
        auto c = char(i);

        if(!filter(c)) {
            continue;
        }

        ASSERT_EQ(f(c), m[i]) << "Char was `" << c << "' (" << int(c) << ")";
    }
}

template <typename F, typename T>
void test_map(F f, const CharMap<T>& m) {
    return test_map(f, m, [](char) { return true; });
}


TEST(Ascii, tolower) {
    CharMap<char> m = {{}};
    make_id_map(m);
    make_map(m, sv("ABCDEFGHIJKLMNOPQRSTUVWXYZ"), sv("abcdefghijklmnopqrstuvwxyz"));

    test_map(m7::ascii::tolower, m);
}

TEST(Ascii, toupper) {
    CharMap<char> m = {{}};
    make_id_map(m);
    make_map(m, sv("abcdefghijklmnopqrstuvwxyz"), sv("ABCDEFGHIJKLMNOPQRSTUVWXYZ"));

    test_map(m7::ascii::toupper, m);
}

TEST(Ascii, todigit) {
    CharMap<int> m = {{}};
    make_map(m, "0123456789", std::initializer_list<int>{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 });

    test_map([](char c) { return m7::ascii::todigit(c); }, m, m7::ascii::isdigit);
}


TEST(Ascii, todigit10) {
    CharMap<int> m = {{}};
    make_map(m, "0123456789", std::initializer_list<int>{ 0, 10, 20, 30, 40, 50, 60, 70, 80, 90 });

    test_map([](char c) { return m7::ascii::todigit(c, 10); }, m, m7::ascii::isdigit);
}


TEST(Ascii, todigit100) {
    CharMap<int> m = {{}};
    make_map(m, "0123456789", std::initializer_list<int>{ 0, 100, 200, 300, 400, 500, 600, 700, 800, 900 });

    test_map([](char c) { return m7::ascii::todigit(c, 100); }, m, m7::ascii::isdigit);
}

TEST(Ascii, toxudigit) {
    CharMap<int> m = {{}};
    make_map(m, "0123456789ABCDEF", std::initializer_list<int>{
            0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9
            , 0xA, 0xB, 0xC, 0xD, 0xE, 0xF
            });

    test_map([](char c) { return m7::ascii::toxudigit(c); }, m, m7::ascii::isxudigit);
}

TEST(Ascii, toxudigit16) {
    CharMap<int> m = {{}};
    make_map(m, "0123456789ABCDEF", std::initializer_list<int>{
            0x0, 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80, 0x90
            , 0xA0, 0xB0, 0xC0, 0xD0, 0xE0, 0xF0
            });

    test_map([](char c) { return m7::ascii::toxudigit(c, 0x10); }, m, m7::ascii::isxudigit);
}


TEST(Ascii, toxudigit256) {
    CharMap<int> m = {{}};
    make_map(m, "0123456789ABCDEF", std::initializer_list<int>{
            0x00, 0x100, 0x200, 0x300, 0x400, 0x500, 0x600, 0x700, 0x800, 0x900
            , 0xA00, 0xB00, 0xC00, 0xD00, 0xE00, 0xF00
            });

    test_map([](char c) { return m7::ascii::toxudigit(c, 0x100); }, m, m7::ascii::isxudigit);
}

TEST(Ascii, toxldigit) {
    CharMap<int> m = {{}};
    make_map(m, "0123456789abcdef", std::initializer_list<int>{
            0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9
            , 0xA, 0xB, 0xC, 0xD, 0xE, 0xF
            });

    test_map([](char c) { return m7::ascii::toxldigit(c); }, m, m7::ascii::isxldigit);
}

TEST(Ascii, toxldigit16) {
    CharMap<int> m = {{}};
    make_map(m, "0123456789abcdef", std::initializer_list<int>{
            0x0, 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80, 0x90
            , 0xA0, 0xB0, 0xC0, 0xD0, 0xE0, 0xF0
            });

    test_map([](char c) { return m7::ascii::toxldigit(c, 0x10); }, m, m7::ascii::isxldigit);
}

TEST(Ascii, toxldigit256) {
    CharMap<int> m = {{}};
    make_map(m, "0123456789abcdef", std::initializer_list<int>{
            0x00, 0x100, 0x200, 0x300, 0x400, 0x500, 0x600, 0x700, 0x800, 0x900
            , 0xA00, 0xB00, 0xC00, 0xD00, 0xE00, 0xF00
            });

    test_map([](char c) { return m7::ascii::toxldigit(c, 0x100); }, m, m7::ascii::isxldigit);
}



TEST(Ascii, toxdigit) {
    CharMap<int> m = {{}};
    make_map(m, "0123456789ABCDEFabcdef", std::initializer_list<int>{
            0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9
            , 0xA, 0xB, 0xC, 0xD, 0xE, 0xF
            , 0xA, 0xB, 0xC, 0xD, 0xE, 0xF
            });

    test_map([](char c) { return m7::ascii::toxdigit(c); }, m, m7::ascii::isxdigit);
}

TEST(Ascii, toxdigit16) {
    CharMap<int> m = {{}};
    make_map(m, "0123456789ABCDEFabcdef", std::initializer_list<int>{
            0x0, 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80, 0x90
            , 0xA0, 0xB0, 0xC0, 0xD0, 0xE0, 0xF0
            , 0xA0, 0xB0, 0xC0, 0xD0, 0xE0, 0xF0
            });

    test_map([](char c) { return m7::ascii::toxdigit(c, 0x10); }, m, m7::ascii::isxdigit);
}

TEST(Ascii, toxdigit256) {
    CharMap<int> m = {{}};
    make_map(m, "0123456789ABCDEFabcdef", std::initializer_list<int>{
            0x00, 0x100, 0x200, 0x300, 0x400, 0x500, 0x600, 0x700, 0x800, 0x900
            , 0xA00, 0xB00, 0xC00, 0xD00, 0xE00, 0xF00
            , 0xA00, 0xB00, 0xC00, 0xD00, 0xE00, 0xF00
            });

    test_map([](char c) { return m7::ascii::toxdigit(c, 0x100); }, m, m7::ascii::isxdigit);
}
