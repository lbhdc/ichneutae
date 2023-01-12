#include "silversearcher/text/search.h"
#include <gtest/gtest.h>

namespace {
TEST(contains, forwards_correctly) {
	ASSERT_TRUE(ag::text::contains("ab", 'a'));
	ASSERT_TRUE(ag::text::contains("abc", "ab"));
	ASSERT_FALSE(ag::text::contains("a", 'b'));
}
} // namespace
