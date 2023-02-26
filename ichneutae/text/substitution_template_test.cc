#include "ichneutae/text/substitution_template.h"
#include <gtest/gtest.h>
#include <sstream>

namespace {
TEST(substitution_template, it_works) {
	auto st = in::text::substitution_template{{{"{{A_VARIABLE}}", "a-value"}}};
	auto input = std::istringstream{"{{A_VARIABLE}} {{WORKS}}"};
	ASSERT_EQ(st.execute(input, {{"{{WORKS}}", "works"}}), "a-value works");
}

TEST(substitution_template, are_renderable) {
	const auto tpl =
		in::text::substitution_template::render("-{{A_VARIABLE}}-", {{"{{A_VARIABLE}}", "a-value"}});
	ASSERT_EQ(tpl, "-a-value-");
}
} // namespace
