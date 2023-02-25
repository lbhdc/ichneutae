package(default_visibility = ["//visibility:public"])

cc_library(
    name = "coroutine",
    hdrs = ["coroutine.h"],
    copts = ["-fcoroutines"],
)

cc_library(
    name = "generator",
    hdrs = ["generator.h"],
    deps = [
        ":coroutine",
        "//ichneutae/memory:aligned_allocator",
        "//ichneutae/memory:holding_pen",
    ],
)

cc_test(
    name = "async_test",
    size = "small",
    srcs = [
        "generator_test.cc",
    ],
    deps = [
        ":generator",
        "@com_google_googletest//:gtest_main",
    ],
)
