#ifndef ICHNEUTAE_GENERATE_CC_SOURCE_H
#define ICHNEUTAE_GENERATE_CC_SOURCE_H

#include "ichneutae/generate/cc_target.h"
#include "ichneutae/text/substitution_template.h"

namespace in::generate {
/// cc_source renders a cc source file
[[nodiscard]] std::string cc_source(
	text::substitution_template::value_map&& vm,
	cc_target target = cc_target::library
) noexcept;

/// cc_source renders a cc source file and writes it to a file
void cc_source(
	std::string_view path,
	text::substitution_template::value_map&& vm,
	cc_target target = cc_target::library
) noexcept;

[[nodiscard]] std::string_view cc_source_template(cc_target target) noexcept;
} // namespace in::generate

#endif
