#ifndef ICHNEUTAE_TEXT_CASE_H
#define ICHNEUTAE_TEXT_CASE_H

#include <algorithm>

namespace in::text {
/// lower_case mutates a string to lower case characters
void lower_case(std::string& s) noexcept {
	std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return std::tolower(c); });
}

/// upper_case mutates a string to upper case characters
void upper_case(std::string& s) noexcept {
	std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return std::toupper(c); });
}
} // namespace in::text

#endif
