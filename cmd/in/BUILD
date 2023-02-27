load("//build:crosscompile.bzl", "PLATFORMS", "crosscompile")
load("@com_github_google_rules_install//installer:def.bzl", "installer")

cc_binary(
    name = "in",
    srcs = ["main.cc"],
    features = ["static_libstdcxx"],
    deps = [
        "//ichneutae:version",
        "//ichneutae/flag:parser",
        "//ichneutae/os:user_home",
        "//ichneutae/text:contains",
        "//ichneutae/text:search",
    ],
)

installer(
    name = "install_in",
    data = [":in"],
)

[crosscompile(":in", platform) for platform in PLATFORMS]
