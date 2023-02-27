#ifndef ICHNEUTAE_GENERATE_CC_TESTS_H
#define ICHNEUTAE_GENERATE_CC_TESTS_H

#include "ichneutae/text/substitution_template.h"
#include <string>

namespace in::generate {
/// cc_header renders a cc header file
[[nodiscard]] std::string cc_tests(text::substitution_template::value_map&& vm) noexcept;

/// cc_header renders a cc header file and writes it to a file
void cc_tests(std::string_view path, text::substitution_template::value_map&& vm) noexcept;
} // namespace in::generate

#endif // ICHNEUTAE_GENERATE_CC_TESTS_H
