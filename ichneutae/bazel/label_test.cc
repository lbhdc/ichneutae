#include "ichneutae/bazel/label.h"
#include <gtest/gtest.h>

namespace {
TEST(label, it_works) {
	auto label = in::bazel::label("//some/label");
	ASSERT_EQ(label.directory, "some/label");
	ASSERT_EQ(label.target, "label");
	ASSERT_EQ(label.workspace, "");
	label = in::bazel::label("@//some/nested:label");
	ASSERT_EQ(label.directory, "some/nested");
	ASSERT_EQ(label.target, "label");
	ASSERT_EQ(label.workspace, "@");
	label = in::bazel::label("@remote//some/nested:label");
	ASSERT_EQ(label.directory, "some/nested");
	ASSERT_EQ(label.target, "label");
	ASSERT_EQ(label.workspace, "@remote");
}
} // namespace
