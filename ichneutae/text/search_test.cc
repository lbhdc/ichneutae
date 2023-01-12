#include "ichneutae/text/search.h"
#include <gtest/gtest.h>

namespace {
TEST(contains, forwards_correctly) {
	ASSERT_TRUE(in::text::contains("ab", 'a'));
	ASSERT_TRUE(in::text::contains("abc", "ab"));
	ASSERT_FALSE(in::text::contains("a", 'b'));
}
} // namespace
