#ifndef ICHNEUTAE_TEXT_SUBSTITUTION_TEMPLATE_H
#define ICHNEUTAE_TEXT_SUBSTITUTION_TEMPLATE_H

#include "ichneutae/text/replace_all.h"
#include <fstream>
#include <optional>
#include <sstream>
#include <string>
#include <string_view>
#include <unordered_map>

namespace in::text {
/// substitution_template is a simple templating abstraction that takes a map of variables used to
/// replace temporary placeholders in a string template.
struct substitution_template {
	using value_map = std::unordered_map<std::string_view, std::string_view>;

	/// values are a map of template variables and the values they should be replaced with
	value_map values{};

	substitution_template() = delete;

	explicit substitution_template(value_map&& vm) noexcept : values(std::move(vm)) {}

	// is movable
	substitution_template(substitution_template&&) noexcept = default;
	substitution_template& operator=(substitution_template&&) = default;

	// isn't copyable
	substitution_template(const substitution_template&) noexcept = delete;
	substitution_template& operator=(const substitution_template&) = delete;

	~substitution_template() = default;

	[[nodiscard]] std::string execute(std::istream& input) const noexcept;

	[[nodiscard]] std::string execute(std::istream& input, value_map&& extra_args) const noexcept;

	[[nodiscard]] static std::string render(std::istream& input, value_map&& vm) noexcept;

	[[nodiscard]] static std::string render(std::string_view tpl, value_map&& vm) noexcept;
};
} // namespace in::text

#endif
