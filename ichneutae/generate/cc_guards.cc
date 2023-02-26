#include "ichneutae/generate/cc_guards.h"
#include "ichneutae/os/path.h"
#include "ichneutae/text/case.h"
#include "ichneutae/text/replace_all.h"
#include "ichneutae/text/trim.h"

namespace in::generate {
std::string cc_guards(std::string_view path_to_file, std::string_view prefix) noexcept {
	// <prefix>_<path_to_file>
	auto guard = std::string(prefix) + "_" + std::string(path_to_file);
	// replace os path separators with underscores
	text::replace_all(guard, std::string{os::path_seperator}, std::string{'_'});
	// if path_to_file is absolute there will be duplicate underscores between it and the prefix
	text::replace_all(guard, "__", "_");
	text::upper_case(guard);
	// if there is no prefix and the path is absolute it will start with an underscore
	text::trim_prefix(guard, "_");
	// if the path ends with a separator it will end with an underscore
	text::trim_suffix(guard, "_");
	// replace ext separator with underscores
	text::replace_all(guard, ".", "_");
	return guard;
}
} // namespace in::generate
