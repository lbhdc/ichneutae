cc_library(
    name = "parser",
    srcs = ["parser.cc"],
    hdrs = ["parser.h"],
    visibility = ["//visibility:public"],
    deps = [
        "//ichneutae/os:path",
        "//ichneutae/text:contains",
    ],
)

cc_test(
    name = "flag_test",
    size = "small",
    srcs = [
        "parser_test.cc",
    ],
    deps = [
        ":parser",
        "@com_google_googletest//:gtest_main",
    ],
)
