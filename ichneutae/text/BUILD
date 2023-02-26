load("@rules_cc//cc:defs.bzl", "cc_test")

cc_library(
    name = "contains",
    hdrs = ["contains.h"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "trim",
    hdrs = ["trim.h"],
    visibility = ["//visibility:public"],
)

cc_test(
    name = "text_test",
    size = "small",
    srcs = [
        "contains_test.cc",
        "trim_test.cc",
    ],
    deps = [
        ":contains",
        ":trim",
        "@com_google_googletest//:gtest_main",
    ],
)
