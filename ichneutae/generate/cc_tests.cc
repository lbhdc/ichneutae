#include "ichneutae/generate/cc_tests.h"

namespace in::generate {
inline constexpr std::string_view cc_tests_tpl = R"(#include "{{HEADER_FILE_PATH}}"
#include <gtest/gtest.h>

namespace {
TEST({{DIR_NAME}}, it_works) {
  ASSERT_TRUE(true);
}
} // namespace

)";

std::string cc_tests(text::substitution_template::value_map&& vm) noexcept {
	return text::substitution_template::render(cc_tests_tpl, std::move(vm));
}

void cc_tests(std::string_view path, text::substitution_template::value_map&& vm) noexcept {
	auto ofile = std::ofstream(path.begin());
	auto rendered_template = cc_tests(std::move(vm));
	ofile << rendered_template;
	ofile.close();
}
} // namespace in::generate
