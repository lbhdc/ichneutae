#include "ichneutae/os/path.h"
#include <gtest/gtest.h>

namespace {
TEST(path, dir_pops_path_elements) {
	const auto sep = '/';
	const auto x = "/a/file/system/path";
	auto got = in::os::dir(x, sep);
	ASSERT_EQ(got, "/a/file/system");
	got = in::os::dir(got, sep);
	ASSERT_EQ(got, "/a/file");
	got = in::os::dir(got, sep);
	ASSERT_EQ(got, "/a");
	got = in::os::dir(got, sep);
	ASSERT_EQ(got, "");
	got = in::os::dir(got, sep);
	ASSERT_EQ(got, "");
}

TEST(path, ext_works) {
	ASSERT_EQ(in::os::ext("thing.foo"), "foo");
	ASSERT_EQ(in::os::ext("thing"), "");
	ASSERT_EQ(in::os::ext(""), "");
}

TEST(path, file_name_works) {
	const auto sep = '/';
	ASSERT_EQ(in::os::file_name("/some/thing.foo", sep), "thing.foo");
	ASSERT_EQ(in::os::file_name("thing", sep), "thing");
	ASSERT_EQ(in::os::file_name("", sep), "");
}

TEST(path, paths_are_joinable) {
	const auto sep = '/';
	ASSERT_EQ(in::os::join('%', "some", "thing.foo"), "some%thing.foo");
	ASSERT_EQ(in::os::join(sep, "onething"), "onething");
	ASSERT_EQ(in::os::join("onething"), "onething");
	ASSERT_EQ(in::os::join(""), "");
}
} // namespace
