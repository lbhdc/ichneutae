# Hacking

Ichneutae has multiple build systems, but bazel is the primary build system, and some features (like
tests) are only available in bazel.

## Building with bazel
```shell
bazel build //...
```

The build can be altered through a `user.bazelrc` file.
```shell
echo "build --config=debug" > user.bazelrc
```

Natively built artifacts can be installed in the local system.
```shell
bazel run -c opt //cmd/in:install_in "$HOME/.local/bin"
```

## Building with make
Running make in the project root will produce a binary in the root directory.
```shell
make
```

## Automating with satyr
Satyr is a tool for automating project tasks.

One example is code generation. This would create a new build file, cc header, source, and test.
```shell
satyr gen cc-pkg //ichneute/a/new:library
```

Satyr can be installed with bazel.
```shell
bazel run -c opt //cmd/satyr:install_satyr "$HOME/.local/bin"
```

It can also be built with make.
```shell
make satyr
```