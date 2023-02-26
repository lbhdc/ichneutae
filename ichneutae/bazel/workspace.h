#ifndef ICHNEUTAE_BAZEL_WORKSPACE_H
#define ICHNEUTAE_BAZEL_WORKSPACE_H

#include "ichneutae/result_or.h"
#include <string>

namespace in::bazel {
/// workspace locates the root directory in a bazel workspace
[[nodiscard]] result_or<std::string> workspace() noexcept;
} // namespace in::bazel

#endif
