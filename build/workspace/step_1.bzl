load("@bazel_skylib//:workspace.bzl", "bazel_skylib_workspace")
load("@com_github_google_rules_install//:deps.bzl", "install_rules_dependencies")

def workspace_step_1():
    bazel_skylib_workspace()
    install_rules_dependencies()
