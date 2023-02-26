#include "ichneutae/generate/cc_build.h"

namespace in::generate {
inline constexpr std::string_view cc_build_lib_tpl = R"(cc_library(
    name = "{{NAME}}",
    srcs = ["{{NAME}}.cc"],
    hdrs = ["{{NAME}}.h"],
    visibility = ["//visibility:public"],
)

cc_test(
    name = "{{DIR_NAME}}_test",
    size = "small",
    srcs = ["{{NAME}}.cc"],
    deps = [
        ":{{NAME}}",
        "@com_google_googletest//:gtest_main",
    ],
)
)";

inline constexpr std::string_view cc_build_bin_tpl =
	R"(load("//build:crosscompile.bzl", "crosscompile")

cc_binary(
    name = "{{DIR_NAME}}",
    srcs = ["main.cc"],
    features = ["static_libstdcxx"],
    deps = [
        "//ichneutae:version",
        "//ichneutae/flag:parser",
    ],
)

# supported platforms
PLATFORMS = [
    "@aspect_gcc_toolchain//platforms:aarch64_linux",
    "@aspect_gcc_toolchain//platforms:armv7_linux",
    "@aspect_gcc_toolchain//platforms:x86_64_linux",
]

[crosscompile(":in", platform) for platform in PLATFORMS]
)";

std::string cc_build(text::substitution_template::value_map&& vm, bool library) noexcept {
	if (library) {
		return text::substitution_template::render(cc_build_lib_tpl, std::move(vm));
	}
	return text::substitution_template::render(cc_build_bin_tpl, std::move(vm));
}

void cc_build(
	std::string_view path,
	text::substitution_template::value_map&& vm,
	bool library
) noexcept {
	auto ofile = std::ofstream(path.begin());
	auto rendered_template = cc_build(std::move(vm), library);
	ofile << rendered_template;
	ofile.close();
}
} // namespace in::generate
