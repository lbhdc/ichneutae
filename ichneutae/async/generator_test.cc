#include "ichneutae/async/generator.h"
#include <gtest/gtest.h>

namespace {
in::async::generator<int> f(int n) {
	for (auto i{0}; i < n; ++i) {
		co_yield i;
	}
}

TEST(generator, it_works) {
	auto want{0};
	for (auto got : f(10)) {
		ASSERT_EQ(got, want);
		++want;
	}
}

TEST(generator, is_nextable) {
	auto want{0};
	auto it = f(100);
	while (true) {
		auto got = it.next();
		if (got.empty()) {
			break;
		}
		ASSERT_EQ(*got, want);
		++want;
	}
}
} // namespace
