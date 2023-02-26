#include "ichneutae/bazel/workspace.h"
#include "ichneutae/os/path.h"
#include <filesystem>

namespace in::bazel {
result_or<std::string> workspace(std::string_view current_dir) noexcept {
	auto cwd = current_dir;
	if (cwd.empty()) {
		cwd = std::filesystem::current_path().string();
	}
	// walk from current directory to root
	while (not cwd.empty()) {
		std::string path;
		// loop through dir looking for WORKSPACE file
		for (const auto& entry : std::filesystem::directory_iterator(cwd)) {
			path = entry.path();
			if ("WORKSPACE" == os::file_name(path)) {
				path = os::dir(path);
				return path;
			}
		}
		// walk to parent directory
		cwd = in::os::dir(cwd);
	}
	return failed_precondition("bazel: not in a workspace");
}
} // namespace in::bazel
