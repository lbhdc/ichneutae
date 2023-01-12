#ifndef ICHNEUTAE_TEXT_TRIM_H
#define ICHNEUTAE_TEXT_TRIM_H

#include <string>
#include <string_view>

namespace in::text {
/// is_whitespace returns true if a character is whitespace
[[nodiscard]] constexpr bool is_whitespace(const char ch) noexcept {
	return (ch == ' ') or (ch == '\t') or (ch == '\n') or (ch == '\r') or (ch == '\f');
}

/// trim_prefix remove a prefix from a string_view
[[nodiscard]] constexpr std::string_view trim_prefix(
	const std::string_view s,
	const std::string_view prefix
) noexcept {
	const auto pivot = s.find_first_not_of(prefix);
	if (pivot == std::string::npos) {
		return {};
	}
	return s.substr(pivot);
}

/// trim_suffix remove a suffix from a string_view
[[nodiscard]] constexpr std::string_view trim_suffix(
	const std::string_view s,
	const std::string_view suffix
) noexcept {
	const auto pivot = s.find_last_not_of(suffix);
	if (pivot == std::string::npos) {
		return s;
	}
	return s.substr(0, pivot + 1);
}

/// trim_whitespace removes the prefix and suffix of whitespace from a sting_view.
[[nodiscard]] constexpr std::string_view trim_whitespace(const std::string_view s) noexcept {
	size_t left{0};
	size_t right{s.size() - 1};
	while (is_whitespace(s[left]) and left <= right) {
		++left;
	}
	while (is_whitespace(s[right]) and left <= right) {
		--right;
	}
	return s.substr(left, 1 + right - left);
}

/// trim_whitespace_prefix removes the prefix of whitespace from a sting_view.
[[nodiscard]] constexpr std::string_view trim_whitespace_prefix(const std::string_view s) noexcept {
	size_t left{0};
	const size_t right{s.size() - 1};
	while (is_whitespace(s[left]) and left <= right) {
		++left;
	}
	return s.substr(left, 1 + right - left);
}

/// trim_whitespace_suffix removes the suffix of whitespace from a sting_view.
[[nodiscard]] constexpr std::string_view trim_whitespace_suffix(const std::string_view s) noexcept {
	size_t right{s.size() - 1};
	while (is_whitespace(s[right])) {
		--right;
	}
	s.find('c');
	return s.substr(0, 1 + right);
}
} // namespace in::text

#endif // ICHNEUTAE_TEXT_TRIM_H
