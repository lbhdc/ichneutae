load("//build:crosscompile.bzl", "PLATFORMS", "crosscompile")
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

[crosscompile(":satyr", platform) for platform in PLATFORMS]
