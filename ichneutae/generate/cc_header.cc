#include "ichneutae/generate/cc_header.h"

namespace in::generate {
inline constexpr std::string_view cc_header_tpl = R"(#ifndef {{HEADER_GUARD}}
#define {{HEADER_GUARD}}

namespace {{NAMESPACE}} {} // namespace {{NAMESPACE}}

#endif // {{HEADER_GUARD}}
)";

std::string cc_header(text::substitution_template::value_map&& vm) noexcept {
	return text::substitution_template::render(cc_header_tpl, std::move(vm));
}

void cc_header(std::string_view path, text::substitution_template::value_map&& vm) noexcept {
	auto ofile = std::ofstream(path.begin());
	auto rendered_template = cc_header(std::move(vm));
	ofile << rendered_template;
	ofile.close();
}
} // namespace in::generate
