package(default_visibility = ["//visibility:public"])

load("@rules_cc//cc:defs.bzl", "cc_test")

cc_library(
    name = "path",
    srcs = ["path.cc"],
    hdrs = ["path.h"],
)

cc_test(
    name = "os_test",
    size = "small",
    srcs = ["path_test.cc"],
    deps = [
        ":path",
        "@com_google_googletest//:gtest_main",
    ],
)
