#ifndef ICHNEUTAE_GENERATE_CC_BUILD_H
#define ICHNEUTAE_GENERATE_CC_BUILD_H

#include "ichneutae/text/substitution_template.h"

namespace in::generate {
/// cc_build renders a bazel build file for a c++ library
[[nodiscard]] std::string cc_build(
	text::substitution_template::value_map&& vm,
	bool library = true
) noexcept;

/// cc_build renders a bazel build file for a c++ library and writes it to a file
void cc_build(
	std::string_view path,
	text::substitution_template::value_map&& vm,
	bool library = true
) noexcept;
} // namespace in::generate

#endif
