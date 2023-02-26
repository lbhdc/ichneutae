#ifndef ICHNEUTAE_OS_PATH_H
#define ICHNEUTAE_OS_PATH_H

#include <initializer_list>
#include <string>
#include <string_view>

namespace in::os::internal {
std::string joiner(char seperator, std::initializer_list<std::string_view> paths) noexcept;
} // namespace in::os::internal

namespace in::os {
#if _WIN32
/// path_seperator is a system specif char used to separate path elements in a filesystem path
inline constexpr char path_seperator = '\\';
#else
/// path_seperator is a system specif char used to separate path elements in a filesystem path
inline constexpr char path_seperator = '/';
#endif

/// dir takes a filesystem path and returns the path without the last item
constexpr std::string_view dir(
	const std::string_view path,
	const char seperator = path_seperator
) noexcept {
	const auto pivot = path.find_last_of(seperator);
	if (pivot == std::string::npos) {
		return "";
	}
	return path.substr(0, pivot);
}

/// ext takes a filesystem path and returns the file extension if its present
constexpr std::string_view ext(const std::string_view path) noexcept {
	const auto pivot = path.find_last_of('.');
	if (pivot == std::string::npos) {
		return "";
	}
	return path.substr(pivot + 1, path.size());
}

/// file_name takes a filesystem path and returns the element of that path
constexpr std::string_view file_name(
	const std::string_view path,
	const char seperator = path_seperator
) noexcept {
	const auto pivot = path.find_last_of(seperator);
	if (pivot == std::string::npos) {
		return path;
	}
	return path.substr(pivot + 1, path.size());
}

template<typename SV, typename... Tail> std::string join(SV&& sv, Tail&&... tail) noexcept {
	return internal::joiner(path_seperator, {std::forward<SV>(sv), std::forward<Tail>(tail)...});
}

template<typename SV, typename... Tail>
std::string join(const char seperator, SV&& sv, Tail&&... tail) noexcept {
	return internal::joiner(seperator, {std::forward<SV>(sv), std::forward<Tail>(tail)...});
}
} // namespace in::os

#endif
