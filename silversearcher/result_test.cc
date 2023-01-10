#include "silversearcher/result.h"
#include <gtest/gtest.h>

namespace {
ag::result f(bool toggle) {
  if (not toggle) {
    return ag::unknown();
  }
  return ag::ok_result();
}

ag::result g(bool toggle) {
  auto rs = f(toggle);
  if (not rs.ok()) {
    return rs;
  }
  return rs;
}

ag::result_or<std::string> h(bool toggle) {
  auto rs = f(toggle);
  if (not rs.ok()) {
    return rs;
  }
  return std::string("works");
}

TEST(result, it_works) {
  auto rs = ag::ok_result();
  ASSERT_TRUE(rs.ok());
  rs = g(true);
  ASSERT_TRUE(rs.ok());
  rs = g(false);
  ASSERT_FALSE(rs.ok());
  rs = ag::unknown("it works");
  ASSERT_EQ(rs.message(), "unknown: it works");
  ASSERT_EQ(rs.message(), rs.to_string());
  ASSERT_EQ(rs.code(), ag::result_code::unknown);
}

TEST(result_or, it_works) {
  auto rs = ag::result_or<std::string>("asdf");
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
}
