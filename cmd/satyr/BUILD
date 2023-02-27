load("//build:crosscompile.bzl", "crosscompile")
load("@com_github_google_rules_install//installer:def.bzl", "installer")

cc_binary(
    name = "satyr",
    srcs = ["main.cc"],
    features = ["static_libstdcxx"],
    deps = [
        "//cmd/satyr/command:gen",
        "//ichneutae:version",
        "//ichneutae/flag:parser",
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
