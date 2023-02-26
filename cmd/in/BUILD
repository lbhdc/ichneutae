load("//build:crosscompile.bzl", "crosscompile")
load("@com_github_google_rules_install//installer:def.bzl", "installer")

cc_binary(
    name = "in",
    srcs = ["main.cc"],
    features = ["static_libstdcxx"],
    deps = [
        "//ichneutae:version",
        "//ichneutae/flag:parser",
    ],
)

installer(
    name = "install_in",
    data = [":in"],
)

# supported platforms
PLATFORMS = [
    "@aspect_gcc_toolchain//platforms:aarch64_linux",
    "@aspect_gcc_toolchain//platforms:armv7_linux",
    "@aspect_gcc_toolchain//platforms:x86_64_linux",
]

[crosscompile(":in", platform) for platform in PLATFORMS]
