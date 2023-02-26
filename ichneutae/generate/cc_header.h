#ifndef ICHNEUTAE_GENERATE_CC_HEADER_H
#define ICHNEUTAE_GENERATE_CC_HEADER_H

#include "ichneutae/text/substitution_template.h"

namespace in::generate {
/// cc_header renders a cc header file
[[nodiscard]] std::string cc_header(text::substitution_template::value_map&& vm) noexcept;

/// cc_header renders a cc header file and writes it to a file
void cc_header(std::string_view path, text::substitution_template::value_map&& vm) noexcept;
} // namespace in::generate

#endif
