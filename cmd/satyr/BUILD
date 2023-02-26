load("//build:crosscompile.bzl", "crosscompile")
load("@com_github_google_rules_install//installer:def.bzl", "installer")

cc_binary(
    name = "satyr",
    srcs = ["main.cc"],
    features = ["static_libstdcxx"],
    deps = [
        "//ichneutae:version",
        "//ichneutae/bazel:label",
        "//ichneutae/bazel:workspace",
        "//ichneutae/flag:parser",
        "//ichneutae/generate:cc_build",
        "//ichneutae/generate:cc_guards",
        "//ichneutae/generate:cc_header",
        "//ichneutae/generate:cc_namespace",
        "//ichneutae/generate:cc_source",
        "//ichneutae/os:path",
    ],
)

installer(
    name = "install_satyr",
    data = [":satyr"],
)

# supported platforms
PLATFORMS = [
    "@aspect_gcc_toolchain//platforms:aarch64_linux",
    "@aspect_gcc_toolchain//platforms:armv7_linux",
    "@aspect_gcc_toolchain//platforms:x86_64_linux",
]

[crosscompile(":satyr", platform) for platform in PLATFORMS]
