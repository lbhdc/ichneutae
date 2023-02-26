cc_library(
    name = "aligned_allocator",
    hdrs = ["aligned_allocator.h"],
    visibility = ["//visibility:public"],
)

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
        "aligned_allocator_test.cc",
        "holding_pen_test.cc",
    ],
    deps = [
        ":aligned_allocator",
        ":holding_pen",
        "@com_google_googletest//:gtest_main",
    ],
)
