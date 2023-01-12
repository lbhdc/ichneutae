load("//build:crosscompile.bzl", "crosscompile")

cc_binary(
    name = "in",
    srcs = ["main.cc"],
    features = ["static_libstdcxx"],
)

# supported platforms
PLATFORMS = [
    "@aspect_gcc_toolchain//platforms:aarch64_linux",
    "@aspect_gcc_toolchain//platforms:armv7_linux",
    "@aspect_gcc_toolchain//platforms:x86_64_linux",
]

[crosscompile(":in", platform) for platform in PLATFORMS]
