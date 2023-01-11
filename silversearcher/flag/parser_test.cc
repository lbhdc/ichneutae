#include "silversearcher/flag/parser.h"
#include <gtest/gtest.h>

namespace {
TEST(parser, it_works) {
	auto flag1 = ag::flag::string("f", "f-default", "an f flag");
	auto flag2 = ag::flag::boolean("some-bool", false, "a binary toggle");
	auto flag3 = ag::flag::int64("i", 0, "some number");
	auto flag4 = ag::flag::int32("j", 1, "another number");
	// assert default args are set before parsing
	ASSERT_NE(ag::flag::executable_name(), "myapp");
	ASSERT_EQ(*flag1, "f-default");
	ASSERT_FALSE(*flag2);
	ASSERT_EQ(*flag3, 0);
	ASSERT_EQ(*flag4, 1);
	// string literals cant be non-const char* without setting -Wwrite-strings or explicit cast
	const char* argv[] =
		{"myapp", "-some-bool", "positional-arg", "--f", "non-default-value", "-i=1", "--j=2"};
	// parse argv
	ag::flag::parse(7, const_cast<char**>(argv));
	// assert parsed values
	ASSERT_GE(ag::flag::executable_name(), "myapp");
	ASSERT_EQ(*flag1, "non-default-value");
	ASSERT_TRUE(*flag2);
	ASSERT_EQ(*flag3, 1);
	ASSERT_EQ(*flag4, 2);
	ASSERT_EQ(ag::flag::nargs(), 1);
	ASSERT_EQ(ag::flag::argv()[0], "positional-arg");
}
} // namespace
