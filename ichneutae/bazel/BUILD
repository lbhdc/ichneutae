package(default_visibility = ["//visibility:public"])

load("@rules_cc//cc:defs.bzl", "cc_test")

cc_library(
    name = "label",
    srcs = ["label.cc"],
    hdrs = ["label.h"],
    deps = [
        "//ichneutae/os:path",
        "//ichneutae/text:replace_all",
    ],
)

cc_library(
    name = "workspace",
    srcs = ["workspace.cc"],
    hdrs = ["workspace.h"],
    deps = [
        "//ichneutae:result_or",
        "//ichneutae/os:path",
    ],
)

cc_test(
    name = "bazel_test",
    size = "small",
    srcs = [
        "label_test.cc",
    ],
    deps = [
        ":label",
        "@com_google_googletest//:gtest_main",
    ],
)
