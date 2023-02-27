#include "ichneutae/text/search.h"
#include <gtest/gtest.h>

namespace {
TEST(search_glob, it_works) {
	const std::string haystack = "0123456789";
	const std::string needle = "345";
	auto rs = in::text::search_glob(haystack, needle);
	ASSERT_TRUE(rs.ok());
	auto match = rs.value();
	ASSERT_EQ(match.row, -1);
	ASSERT_EQ(match.column, 3);
	ASSERT_EQ(match.match_length, 3);
	ASSERT_EQ(haystack.substr(match.column, match.match_length), needle);
	rs = in::text::search_glob(haystack, "no-match");
	ASSERT_FALSE(rs.ok());
	ASSERT_EQ(rs.result().code(), in::result_code::not_found);
}

TEST(search, it_works) {
	const auto haystack = R"(0123456789

0123456789

0123456789

0123456789
)";
	auto input = std::istringstream(haystack);
	for (auto result : in::text::search(input, "345")) {
		ASSERT_EQ(result.row % 2, 0);
		ASSERT_EQ(result.column, 3);
		ASSERT_EQ(result.match_length, 3);
	}
	std::vector<in::text::search_match> res;
	for (auto result : in::text::search(input, "no-match")) {
		res.push_back(std::move(result));
	}
	ASSERT_EQ(res.size(), 0);
}
} // namespace
