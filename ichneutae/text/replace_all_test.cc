#include "ichneutae/text/remove_all.h"
#include "ichneutae/text/replace_all.h"
#include <gtest/gtest.h>

namespace {
TEST(replace_and_remove_all, it_works) {
	std::string x = "{{A}}-{{B}}-{{C}}";
	ASSERT_EQ(in::text::remove_all(x, "{{A}}"), 1);
	ASSERT_EQ(x, "-{{B}}-{{C}}");
	ASSERT_EQ(in::text::remove_all(x, "{{B}}"), 1);
	ASSERT_EQ(x, "--{{C}}");
	ASSERT_EQ(in::text::remove_all(x, "{{C}}"), 1);
	ASSERT_EQ(x, "--");
	ASSERT_EQ(in::text::replace_all(x, "--", "works"), 1);
	ASSERT_EQ(x, "works");
}
} // namespace
