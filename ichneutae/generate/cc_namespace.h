#ifndef ICHNEUTAE_GENERATE_CC_NAMESPACE_H
#define ICHNEUTAE_GENERATE_CC_NAMESPACE_H

#include "ichneutae/bazel/label.h"
#include <string>

namespace in::generate {
std::string cc_namespace(const bazel::label& l) noexcept;
} // namespace in::generate

#endif
