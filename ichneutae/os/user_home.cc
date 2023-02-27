#include "ichneutae/os/user_home.h"
#include "ichneutae/os/path.h"
#include <cstddef>

namespace in::os {
result_or<std::string> user_home() noexcept {
	std::string unix_home = std::getenv("HOME");
	if (not unix_home.empty()) {
		return unix_home;
	}
	std::string windows_drive = std::getenv("HOMEDRIVE");
	std::string windows_path = std::getenv("HOMEPATH");
	auto windows_home = in::os::join(windows_drive, windows_path);
	if (not windows_home.empty()) {
		return windows_home;
	}
	return ok_result();
}
} // namespace in::os
