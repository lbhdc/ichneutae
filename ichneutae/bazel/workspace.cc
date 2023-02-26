#include "ichneutae/bazel/workspace.h"
#include "ichneutae/os/path.h"
#include <filesystem>

namespace in::bazel {
result_or<std::string> workspace() noexcept {
	auto cwd = std::filesystem::current_path();
	// walk from current directory to root
	while (not cwd.empty()) {
		std::string path;
		// loop through dir looking for WORKSPACE file
		for (const auto& entry : std::filesystem::directory_iterator(cwd)) {
			path = entry.path();
			if (path.rfind("WORKSPACE", 0) == 0) {
				return path;
			}
		}
		// walk to parent directory
		cwd = in::os::dir(cwd.string());
	}
	return failed_precondition("bazel: not in a workspace");
}
} // namespace in::bazel
