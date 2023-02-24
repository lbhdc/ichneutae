load("@rules_cc//cc:defs.bzl", "cc_test")

cc_library(
    name = "raw_memory",
    hdrs = ["raw_memory.h"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "holding_pen",
    hdrs = ["holding_pen.h"],
    visibility = ["//visibility:public"],
    deps = [":raw_memory"],
)

cc_test(
    name = "memory_test",
    size = "small",
    srcs = [
        "holding_pen_test.cc",
    ],
    visibility = ["//visibility:private"],
    deps = [
        ":holding_pen",
        "@com_google_googletest//:gtest_main",
    ],
)
