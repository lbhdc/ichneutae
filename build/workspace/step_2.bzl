load("@aspect_gcc_toolchain//toolchain:repositories.bzl", "gcc_toolchain_dependencies")
load("@aspect_gcc_toolchain//toolchain:defs.bzl", "gcc_register_toolchain")

LIBC = "glibc"

GCC_VERSION = "bleeding-edge-2022.08-1"

def workspace_step_2():
    gcc_toolchain_dependencies()
    gcc_register_toolchain(
        name = "gcc12_x86-64_{libc}".format(libc = LIBC),
        sha256 = "9a09ac03001ef2a6cab391cc658fc2a32730b6a8f25614e97a91b9a79537fe33",
        strip_prefix = "x86-64--{libc}--{ver}".format(libc = LIBC, ver = GCC_VERSION),
        target_arch = "x86_64",
        url = "https://toolchains.bootlin.com/downloads/releases/toolchains/x86-64/tarballs" +
              "/x86-64--{libc}--{ver}.tar.bz2".format(libc = LIBC, ver = GCC_VERSION),
    )
    gcc_register_toolchain(
        name = "gcc12_aarcdh64_{libc}".format(libc = LIBC),
        sha256 = "d11a94113dc92fe1c141096dbeb1c3fe2adb0552b495bb9e3e41fad96b4b429a",
        strip_prefix = "aarch64--{libc}--{ver}".format(libc = LIBC, ver = GCC_VERSION),
        target_arch = "aarch64",
        url = "https://toolchains.bootlin.com/downloads/releases/toolchains/aarch64/tarballs" +
              "/aarch64--{libc}--{ver}.tar.bz2".format(libc = LIBC, ver = GCC_VERSION),
    )
    gcc_register_toolchain(
        name = "gcc12_armv7_{libc}".format(libc = LIBC),
        sha256 = "7a3ceba0e5ed7ccb16da16e630a905c76c2ea58f66d161d6d45dce33321e70f6",
        strip_prefix = "armv7-eabihf--{libc}--{ver}".format(libc = LIBC, ver = GCC_VERSION),
        target_arch = "armv7",
        url = "https://toolchains.bootlin.com/downloads/releases/toolchains/armv7-eabihf/tarballs" +
              "/armv7-eabihf--{libc}--{ver}.tar.bz2".format(libc = LIBC, ver = GCC_VERSION),
    )
