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
    srcs = ["{{NAME}}_test.cc"],
    deps = [
        ":{{NAME}}",
        "@com_google_googletest//:gtest_main",
    ],
)
)";

inline constexpr std::string_view cc_build_bin_tpl =
	R"(load("//build:crosscompile.bzl", "crosscompile", "PLATFORMS")
load("@com_github_google_rules_install//installer:def.bzl", "installer")

cc_binary(
    name = "{{DIR_NAME}}",
    srcs = ["main.cc"],
    features = ["static_libstdcxx"],
    deps = [
        "//ichneutae:version",
        "//ichneutae/flag:parser",
    ],
)

installer(
    name = "install_{{DIR_NAME}}",
    data = [":{{DIR_NAME}}"],
)

[crosscompile(":{{DIR_NAME}}", platform) for platform in PLATFORMS]
)";

std::string cc_build(text::substitution_template::value_map&& vm, const cc_target target) noexcept {
	if (target == cc_target::library) {
		return text::substitution_template::render(cc_build_lib_tpl, std::move(vm));
	}
	return text::substitution_template::render(cc_build_bin_tpl, std::move(vm));
}

void cc_build(
	std::string_view path,
	text::substitution_template::value_map&& vm,
	const cc_target target
) noexcept {
	const auto rendered_template = cc_build(std::move(vm), target);
	auto ofile = std::ofstream(path.begin());
	ofile << rendered_template;
	ofile.close();
}
} // namespace in::generate
