load("@aspect_bazel_lib//lib:transitions.bzl", "platform_transition_filegroup")
load("@bazel_tools//tools/build_defs/pkg:pkg.bzl", "pkg_tar")

# supported platforms
PLATFORMS = [
    "@aspect_gcc_toolchain//platforms:aarch64_linux",
    "@aspect_gcc_toolchain//platforms:armv7_linux",
    "@aspect_gcc_toolchain//platforms:x86_64_linux",
]

def crosscompile(binary, platform):
    name = package_from_label(binary)
    platform_suffix = package_from_label(platform).replace("_linux", "")
    transition_name = "{}_{}".format(name, platform_suffix)
    platform_transition_filegroup(
        name = transition_name,
        target_platform = platform,
        srcs = [binary],
    )
    pkg_tar(
        name = "%s_tar" % transition_name,
        srcs = [":%s" % transition_name],
    )

def package_from_label(label):
    chunks = label.split(":")
    if len(chunks) != 2:
        fail("malformed label: " + label)
    package = chunks[-1]
    return package
