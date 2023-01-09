load("@rules_cc//cc:defs.bzl", "cc_test")

cc_library(
    name = "search",
    hdrs = ["search.h"],
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
        "search_test.cc",
        "trim_test.cc",
    ],
    visibility = ["//visibility:private"],
    deps = [
        ":search",
        ":trim",
        "@com_google_googletest//:gtest_main",
    ],
)
