cc_library(
    name = "result",
    srcs = ["result.cc"],
    hdrs = ["result.h"],
    visibility = ["//visibility:public"],
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
        "@com_google_googletest//:gtest_main",
    ],
)
