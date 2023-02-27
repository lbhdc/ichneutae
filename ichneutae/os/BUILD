cc_library(
    name = "files",
    srcs = ["files.cc"],
    hdrs = ["files.h"],
    visibility = ["//visibility:public"],
    deps = ["//ichneutae:result"],
)

cc_library(
    name = "path",
    srcs = ["path.cc"],
    hdrs = ["path.h"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "user_home",
    srcs = ["user_home.cc"],
    hdrs = ["user_home.h"],
    visibility = ["//visibility:public"],
    deps = [
        "//ichneutae:result_or",
        "//ichneutae/os:path",
    ],
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
