#include "ichneutae/os/files.h"
#include <filesystem>

namespace in::os {
result create_directories(std::string_view path_to_create) noexcept {
	if (not std::filesystem::create_directories(path_to_create)) {
		if (not std::filesystem::exists(path_to_create)) {
			return unknown("os: failed to create directory: " + std::string(path_to_create));
		}
	}
	return ok_result();
}
} // namespace in::os
