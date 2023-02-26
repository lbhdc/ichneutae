load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

BAZEL_SKYLIB_VER = "1.2.1"
BAZEL_SKYLIB_SHA = "f7be3474d42aae265405a592bb7da8e171919d74c16f082a5457840f06054728"

GCC_TOOLCHAIN_VER = "7e9e62a61be70d5c233bb3cb2ce51b0bc8d17e4c"
GCC_TOOLCHAIN_SHA = "40ffe8de9149176470d0b430cdb6f4f4acccb80baf7a1e010d29e5e3999bfcbb"

GOOG_TEST_VER = "1.12.1"
GOOG_TEST_SHA = "24564e3b712d3eb30ac9a85d92f7d720f60cc0173730ac166f27dda7fed76cb2"

RULES_INSTALL_VER = "0.4"
RULES_INSTALL_SHA = "ac2c9c53aa022a110273c0e510d191a4c04c6adafefa069a5eeaa16313edc9b9"

def workspace_step_0():
    http_archive(
        name = "bazel_skylib",
        sha256 = BAZEL_SKYLIB_SHA,
        urls = [
            "https://mirror.bazel.build/github.com/bazelbuild/bazel-skylib/releases/download" +
            "/{ver}/bazel-skylib-{ver}.tar.gz".format(ver = BAZEL_SKYLIB_VER),
            "https://github.com/bazelbuild/bazel-skylib/releases/download" +
            "/{ver}/bazel-skylib-{ver}.tar.gz".format(ver = BAZEL_SKYLIB_VER),
        ],
    )
    http_archive(
        name = "aspect_gcc_toolchain",
        sha256 = GCC_TOOLCHAIN_SHA,
        strip_prefix = "gcc-toolchain-%s" % GCC_TOOLCHAIN_VER,
        urls = ["https://github.com/aspect-build/gcc-toolchain/archive/%s.zip" % GCC_TOOLCHAIN_VER],
    )
    http_archive(
        name = "com_google_googletest",
        sha256 = GOOG_TEST_SHA,
        urls = ["https://github.com/google/googletest/archive/refs/tags/release-%s.zip" % GOOG_TEST_VER],
        strip_prefix = "googletest-release-%s" % GOOG_TEST_VER,
    )
    http_archive(
        name = "com_github_google_rules_install",
        urls = [
            "https://github.com/google/bazel_rules_install/releases/download" +
            "/{ver}/bazel_rules_install-{ver}.tar.gz".format(ver = RULES_INSTALL_VER),
        ],
        sha256 = RULES_INSTALL_SHA,
        strip_prefix = "bazel_rules_install-{ver}".format(ver = RULES_INSTALL_VER),
    )
