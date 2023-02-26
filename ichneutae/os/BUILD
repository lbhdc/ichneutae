cc_library(
    name = "path",
    srcs = ["path.cc"],
    hdrs = ["path.h"],
    visibility = ["//visibility:public"],
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
