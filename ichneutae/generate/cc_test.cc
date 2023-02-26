#include "ichneutae/generate/cc_guards.h"
#include "ichneutae/generate/cc_namespace.h"
#include <gtest/gtest.h>

namespace {
TEST(cc, cc_guards) {
	ASSERT_EQ(in::generate::cc_guards("/path/to/file.h"), "PATH_TO_FILE_H");
	ASSERT_EQ(in::generate::cc_guards("/path/to/file.h", "prefix"), "PREFIX_PATH_TO_FILE_H");
}

TEST(cc, cc_namespace) {
	auto label = in::bazel::label("//a/label");
	ASSERT_EQ(in::generate::cc_namespace(label), "a::label");
	label = in::bazel::label("@remote//a/nested:label");
	ASSERT_EQ(in::generate::cc_namespace(label), "a::nested");
}
} // namespace
