#include "ichneutae/memory/holding_pen.h"
#include <gtest/gtest.h>

namespace {
TEST(holding_pen, it_works) {
	auto ptr = in::memory::holding_pen(1l);
	ASSERT_EQ(sizeof(ptr), 16);
	auto another_ptr = in::memory::holding_pen<std::array<long, 100>>();
	ASSERT_EQ(sizeof(another_ptr), 808);
	ASSERT_FALSE(ptr.empty());
	ASSERT_EQ(ptr.value(), 1);
}

TEST(holding_pen, are_comparable) {
	auto a = in::memory::holding_pen(1l);
	auto b = in::memory::holding_pen(1l);
	auto c = in::memory::holding_pen<long>();
	auto d = in::memory::holding_pen(2l);
	//	a == b;
	//	ASSERT_EQ(a, b);
}
} // namespace
