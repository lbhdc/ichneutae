load("@aspect_gcc_toolchain//toolchain:defs.bzl", "ARCHS", "gcc_register_toolchain")

def workspace_step_3():
    gcc_register_toolchain(
        name = "gcc_toolchain_x86_64",
        target_arch = ARCHS.x86_64,
    )
    gcc_register_toolchain(
        name = "gcc_toolchain_armv7",
        target_arch = ARCHS.armv7,
    )
    gcc_register_toolchain(
        name = "gcc_toolchain_aarch64",
        target_arch = ARCHS.aarch64,
    )
