#include "ichneutae/result.h"
#include <gtest/gtest.h>

namespace {
in::result f(bool toggle) {
	if (not toggle) {
		return in::unknown();
	}
	return in::ok_result();
}

in::result g(bool toggle) {
	auto rs = f(toggle);
	if (not rs.ok()) {
		return rs;
	}
	return rs;
}

in::result_or<std::string> h(bool toggle) {
	auto rs = f(toggle);
	if (not rs.ok()) {
		return rs;
	}
	return std::string("works");
}

TEST(result, it_works) {
	auto rs = in::ok_result();
	ASSERT_TRUE(rs.ok());
	rs = g(true);
	ASSERT_TRUE(rs.ok());
	rs = g(false);
	ASSERT_FALSE(rs.ok());
	rs = in::unknown("it works");
	ASSERT_EQ(rs.message(), "unknown: it works");
	ASSERT_EQ(rs.message(), rs.to_string());
	ASSERT_EQ(rs.code(), in::result_code::unknown);
}

TEST(result_or, it_works) {
	auto rs = in::result_or<std::string>("asdf");
	ASSERT_TRUE(rs.ok());
	ASSERT_TRUE(rs.res().ok());
	ASSERT_EQ(rs.value(), "asdf");
	rs = h(true);
	ASSERT_TRUE(rs.ok());
	ASSERT_EQ(rs.value(), "works");
	rs = h(false);
	ASSERT_FALSE(rs.ok());
	ASSERT_EQ(rs.message(), "unknown");
}
} // namespace
