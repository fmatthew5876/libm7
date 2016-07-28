#include <gtest/gtest.h>
#include <m7/string_table.H>

using namespace m7;

TEST(StringTable, store) {
	StringTable table;

	StringView a0 = "Hello World";
	StringView b0 = "Goodbye World";
	StringView c0 =
	    "The macro offsetof expands to an integral constant expression of "
	    "type std::size_t, the value of which is the offset, in bytes, "
	    "from the beginning of an object of specified type to its "
	    "specified member, including padding if any.  If type is not a "
	    "standard layout type, the behavior is undefined.  If member is a "
	    "static member or a member function, the behavior is undefined.  "
	    "The offset of the first member of a standard-layout type is "
	    "always zero (empty-base optimization is mandatory). offsetof "
	    "throws no exceptions; the expression noexcept(offsetof(type, "
	    "member)) always evaluates to true. offsetof is required to work "
	    "as specified above, even if unary operator& is overloaded for any "
	    "of the types involved. This cannot be implemented in standard C++ "
	    "and requires compiler support.";

	StringView d0 = "ABC";
	StringView e0 = "";

	auto a1 = table.store(a0);
	auto b1 = table.store(b0);
	auto c1 = table.store(c0);
	auto d1 = table.store(d0);
	auto e1 = table.store(e0);

	ASSERT_EQ(a0, a1);
	ASSERT_EQ(b0, b1);
	ASSERT_EQ(c0, c1);
	ASSERT_EQ(d0, d1);
	ASSERT_EQ(e0, e1);

	for (int i = 0; i < 5000; ++i) {
		table.store(a0);
		table.store(b0);
	}
	ASSERT_EQ(a0, a1);
	ASSERT_EQ(b0, b1);
	ASSERT_EQ(c0, c1);
	ASSERT_EQ(d0, d1);
	ASSERT_EQ(e0, e1);
}
