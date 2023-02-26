#ifndef ICHNEUTAE_GENERATE_CC_SOURCE_H
#define ICHNEUTAE_GENERATE_CC_SOURCE_H

#include "ichneutae/text/substitution_template.h"

namespace in::generate {
/// cc_source renders a cc source file
[[nodiscard]] std::string cc_source(
	text::substitution_template::value_map&& vm,
	const bool library = true
) noexcept;

/// cc_source renders a cc source file and writes it to a file
void cc_source(
	std::string_view path,
	text::substitution_template::value_map&& vm,
	const bool library = true
) noexcept;
} // namespace in::generate

#endif
