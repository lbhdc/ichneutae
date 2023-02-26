cc_library(
    name = "cc_build",
    srcs = ["cc_build.cc"],
    hdrs = ["cc_build.h"],
    visibility = ["//visibility:public"],
    deps = ["//ichneutae/text:substitution_template"],
)

cc_library(
    name = "cc_guards",
    srcs = ["cc_guards.cc"],
    hdrs = ["cc_guards.h"],
    visibility = ["//visibility:public"],
    deps = [
        "//ichneutae/os:path",
        "//ichneutae/text:case",
        "//ichneutae/text:replace_all",
        "//ichneutae/text:trim",
    ],
)

cc_library(
    name = "cc_header",
    srcs = ["cc_header.cc"],
    hdrs = ["cc_header.h"],
    visibility = ["//visibility:public"],
    deps = ["//ichneutae/text:substitution_template"],
)

cc_library(
    name = "cc_namespace",
    srcs = ["cc_namespace.cc"],
    hdrs = ["cc_namespace.h"],
    visibility = ["//visibility:public"],
    deps = [
        "//ichneutae/bazel:label",
        "//ichneutae/text:replace_all",
    ],
)

cc_library(
    name = "cc_source",
    srcs = ["cc_source.cc"],
    hdrs = ["cc_source.h"],
    visibility = ["//visibility:public"],
    deps = ["//ichneutae/text:substitution_template"],
)

cc_test(
    name = "generate_test",
    size = "small",
    srcs = ["cc_test.cc"],
    deps = [
        ":cc_build",
        ":cc_guards",
        ":cc_header",
        ":cc_namespace",
        ":cc_source",
        "@com_google_googletest//:gtest_main",
    ],
)
