#include "ichneutae/generate/cc_source.h"

namespace in::generate {
inline constexpr std::string_view cc_source_lib_tpl = R"(#include "{{HEADER_FILE_PATH}}"

namespace {{NAMESPACE}} {} // namespace {{NAMESPACE}}
)";

inline constexpr std::string_view cc_source_bin_tpl = R"(#include "ichneutae/flag/parser.h"
#include "ichneutae/version.h"
#include <iostream>

const auto version = in::flag::boolean("version", false, "Print the program version");

int main(int argc, char* argv[]) {
	in::flag::parse(argc, argv);
	if (*version) {
		std::cout << in::flag::executable_name() << ' ' << in::version << '\n';
		std::exit(EXIT_SUCCESS);
	}
	std::cout << "works\n";
}
)";

std::string cc_source(
	text::substitution_template::value_map&& vm,
	const cc_target target
) noexcept {
	return text::substitution_template::render(cc_source_template(target), std::move(vm));
}

void cc_source(
	std::string_view path,
	text::substitution_template::value_map&& vm,
	const cc_target target
) noexcept {
	auto ofile = std::ofstream(path.begin());
	auto rendered_template = cc_source(std::move(vm), target);
	ofile << rendered_template;
	ofile.close();
}

std::string_view cc_source_template(cc_target target) noexcept {
	if (target == cc_target::library) {
		return cc_source_lib_tpl;
	}
	return cc_source_bin_tpl;
}
} // namespace in::generate
