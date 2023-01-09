#include "silversearcher/text/trim.h"
#include <gtest/gtest.h>

namespace {
struct trim_prefix_test_case {
  std::string_view prefix{};
  std::string_view have{};
  std::string_view want{};
};

class trim_prefix_test: public ::testing::TestWithParam<trim_prefix_test_case> {};

TEST_P(trim_prefix_test, prefixes_are_trimable) {
  trim_prefix_test_case c = GetParam();
  ASSERT_EQ(ag::text::trim_prefix(c.have, c.prefix), c.want);
}

INSTANTIATE_TEST_SUITE_P(prefix_test_cases, trim_prefix_test, testing::Values(
  trim_prefix_test_case{.prefix="a", .have={"abcd"}, .want={"bcd"}},
  trim_prefix_test_case{.prefix=" ", .have={"   a"}, .want={"a"}},
  trim_prefix_test_case{.prefix="a", .have={"bbccdd"}, .want={"bbccdd"}},
  trim_prefix_test_case{}
));

struct trim_suffix_test_case {
  std::string_view suffix{};
  std::string_view have{};
  std::string_view want{};
};

class trim_suffix_test: public ::testing::TestWithParam<trim_suffix_test_case> {};

TEST_P(trim_suffix_test, suffixes_are_trimable) {
  trim_suffix_test_case c = GetParam();
  ASSERT_EQ(ag::text::trim_suffix(c.have, c.suffix), c.want);
}

INSTANTIATE_TEST_SUITE_P(suffix_test_cases, trim_suffix_test, testing::Values(
  trim_suffix_test_case{.suffix="d", .have={"abcd"}, .want={"abc"}},
  trim_suffix_test_case{.suffix=" ", .have={"a   "}, .want={"a"}},
  trim_suffix_test_case{.suffix="d", .have={"aabbcc"}, .want={"aabbcc"}},
  trim_suffix_test_case{}
));

TEST(trim_whitespace, whatspace_is_trimable) {
  ASSERT_EQ(ag::text::trim_whitespace("\n\t\r\f  a  \f\r\t\n"), "a");
}

TEST(trim_whitespace_prefix, whatspace_is_trimable) {
  ASSERT_EQ(ag::text::trim_whitespace_prefix("\n\t\r\f  a"), "a");
}

TEST(trim_whitespace_suffix, whatspace_is_trimable) {
  ASSERT_EQ(ag::text::trim_whitespace_suffix("a  \f\r\t\n"), "a");
}
}
