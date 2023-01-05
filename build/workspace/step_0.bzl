load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

BAZEL_SKYLIB_VER = "1.2.1"
BAZEL_SKYLIB_SHA = "f7be3474d42aae265405a592bb7da8e171919d74c16f082a5457840f06054728"

GCC_TOOLCHAIN_VER = "ac745d4685e2095cc4f057862800f3f0a473c201"
GCC_TOOLCHAIN_SHA = "7393082a7717d284aa51998b57f5846ae9a9b607d220972df1356e46a35f4ecc"

GOOG_TEST_VER = "1.12.1"
GOOG_TEST_SHA = "24564e3b712d3eb30ac9a85d92f7d720f60cc0173730ac166f27dda7fed76cb2"

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
