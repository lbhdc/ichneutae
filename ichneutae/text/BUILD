cc_library(
    name = "case",
    hdrs = ["case.h"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "contains",
    hdrs = ["contains.h"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "remove_all",
    hdrs = ["remove_all.h"],
    visibility = ["//visibility:public"],
    deps = [":replace_all"],
)

cc_library(
    name = "replace_all",
    srcs = ["replace_all.cc"],
    hdrs = ["replace_all.h"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "substitution_template",
    srcs = ["substitution_template.cc"],
    hdrs = ["substitution_template.h"],
    visibility = ["//visibility:public"],
    deps = [
        "//ichneutae:result",
        "//ichneutae/os:path",
        "//ichneutae/text:replace_all",
    ],
)

cc_library(
    name = "trim",
    hdrs = ["trim.h"],
    visibility = ["//visibility:public"],
)

cc_test(
    name = "text_test",
    size = "small",
    srcs = [
        "case_test.cc",
        "contains_test.cc",
        "replace_all_test.cc",
        "substitution_template_test.cc",
        "trim_test.cc",
    ],
    deps = [
        ":case",
        ":contains",
        ":remove_all",
        ":replace_all",
        ":substitution_template",
        ":trim",
        "@com_google_googletest//:gtest_main",
    ],
)
