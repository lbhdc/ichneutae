#include "ichneutae/generate/cc_namespace.h"
#include "ichneutae/os/path.h"
#include "ichneutae/text/replace_all.h"

namespace in::generate {
std::string cc_namespace(const bazel::label& l) noexcept {
	auto ns = l.directory;
	text::replace_all(ns, std::string{os::path_seperator}, "::");
	text::replace_all(ns, "ichneutae", "in");
	return ns;
}
} // namespace in::generate
