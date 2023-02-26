#include "ichneutae/os/path.h"

namespace ichneutae::os {}

namespace in::os::internal {
std::string joiner(const char seperator, std::initializer_list<std::string_view> paths) noexcept {
	auto full_path = std::string{};
	for (auto path : paths) {
		full_path += path;
		full_path += seperator;
	}
	full_path.pop_back(); // drop the trailing seperator
	return full_path;
}
} // namespace in::os::internal
