cc_library(
    name = "result",
    srcs = ["result.cc"],
    hdrs = ["result.h"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "result_or",
    hdrs = ["result_or.h"],
    deps = [":result"],
)

cc_library(
    name = "version",
    hdrs = ["version.h"],
    visibility = ["//visibility:public"],
)

cc_test(
    name = "ichneutae_test",
    size = "small",
    srcs = [
        "result_test.cc",
    ],
    deps = [
        ":result",
        ":result_or",
        "@com_google_googletest//:gtest_main",
    ],
)
