load("@rules_cc//cc:defs.bzl", "cc_test")

cc_library(
    name = "parser",
    srcs = ["parser.cc"],
    hdrs = ["parser.h"],
    visibility = ["//visibility:public"],
    deps = [
        "//ichneutae/text:search",
    ],
)

cc_test(
    name = "flag_test",
    size = "small",
    srcs = [
        "parser_test.cc",
    ],
    visibility = ["//visibility:private"],
    deps = [
        ":parser",
        "@com_google_googletest//:gtest_main",
    ],
)
