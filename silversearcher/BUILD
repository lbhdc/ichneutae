load("@rules_cc//cc:defs.bzl", "cc_test")

cc_library(
    name = "result",
    srcs = ["result.cc"],
    hdrs = ["result.h"],
    visibility = ["//visibility:public"],
)

cc_test(
    name = "silversearcher_test",
    size = "small",
    srcs = [
        "result_test.cc",
    ],
    visibility = ["//visibility:private"],
    deps = [
        ":result",
        "@com_google_googletest//:gtest_main",
    ],
)
