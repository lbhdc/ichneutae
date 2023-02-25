#include "ichneutae/memory/holding_pen.h"
#include <gtest/gtest.h>

namespace {
TEST(holding_pen, it_works) {
	auto pen = in::memory::holding_pen(1l);
	ASSERT_FALSE(pen.empty());
	ASSERT_EQ(pen.value(), 1);
}

TEST(holding_pen, are_comparable) {
	auto a = in::memory::holding_pen(1l);
	auto b = in::memory::holding_pen(1l);
	auto c = in::memory::holding_pen<long>();
	auto d = in::memory::holding_pen(2l);
	ASSERT_EQ(a, b);
	ASSERT_NE(c, d);
}

TEST(holding_pen, is_assignable) {
	auto x = in::memory::holding_pen<int>();
	x.assign(1);
	ASSERT_EQ(x.value(), 1);
}

TEST(holding_pen, is_emplacable) {
	auto x = in::memory::holding_pen<int>();
	x.emplace(1);
	ASSERT_EQ(x.value(), 1);
}

TEST(holding_pen, is_resetable) {
	auto x = in::memory::holding_pen(1);
	ASSERT_EQ(x.value(), 1);
	x.reset();
	ASSERT_DEATH(x.value(), "holding pen empty");
}

TEST(holding_pen, value_is_gettable) {
	auto x = in::memory::holding_pen(1);
	ASSERT_EQ(x.value(), 1);
	x.reset();
	ASSERT_DEATH(x.value(), "holding pen empty");
	ASSERT_EQ(x.value_or(2), 2);
}
} // namespace
