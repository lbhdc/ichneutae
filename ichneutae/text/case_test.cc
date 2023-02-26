#include "ichneutae/text/case.h"
#include <gtest/gtest.h>

namespace {
TEST(cases, it_works) {
	std::string x = "ASDF";
	in::text::lower_case(x);
	ASSERT_EQ(x, "asdf");
	in::text::upper_case(x);
	ASSERT_EQ(x, "ASDF");
}
} // namespace
