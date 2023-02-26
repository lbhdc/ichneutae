#include "ichneutae/text/substitution_template.h"

namespace in::text {
std::string substitution_template::execute(std::istream& input) const noexcept {
	std::string rendered_template;
	for (std::string row; std::getline(input, row);) {
		for (const auto& [what, with] : this->values) {
			replace_all(row, what, with);
		}
		rendered_template += row + '\n';
	}
	return rendered_template.substr(0, rendered_template.size() - 1);
}

std::string substitution_template::execute(std::istream& input, value_map&& extra_args)
	const noexcept {
	std::string rendered_template;
	for (std::string row; std::getline(input, row);) {
		for (const auto& [what, with] : this->values) {
			replace_all(row, what, with);
		}
		for (const auto& [what, with] : extra_args) {
			replace_all(row, what, with);
		}
		rendered_template += row + '\n';
	}
	return rendered_template.substr(0, rendered_template.size() - 1);
}

std::string substitution_template::render(
	std::istream& input,
	substitution_template::value_map&& vm
) noexcept {
	return substitution_template{std::move(vm)}.execute(input);
}

std::string substitution_template::render(
	std::string_view tpl,
	substitution_template::value_map&& vm
) noexcept {
	auto input = std::istringstream(tpl.begin());
	return substitution_template{std::move(vm)}.execute(input);
}
} // namespace in::text
