#ifndef ICHNEUTAE_FLAG_PARSER_H
#define ICHNEUTAE_FLAG_PARSER_H

#include <span>
#include <string>

namespace in::flag {
/// argv returns the positional args that were not parsed as flags or their values. This does not
/// include the executable name, see `executable_name`.
[[nodiscard]] std::span<std::string> argv() noexcept;

/// nargs returns the number of positional args in argv
[[nodiscard]] size_t nargs() noexcept;

/// executable_name returns the first element parsed from argv
[[nodiscard]] std::string_view executable_name() noexcept;

/// parse the registered cli flags from argv
///
/// At a high level the parser works by running setter functions for each flag seen that wrangles a
/// string into a desired type. If a flag is not seen it setter is never run and it will be set to
/// the default value.
///
/// Positional args not parsed can be accessed using `argv`.
void parse(int argc, char* argv[]) noexcept;

[[nodiscard]] std::string usage() noexcept;

/// string registers a flag that is wrangled into a std::string and returned as a pointer
///
/// The returned pointer is initialized as the default_value, and should never be a nullptr.
[[nodiscard]] std::string* string(
	std::string_view name,
	std::string default_val,
	std::string usage
) noexcept;

/// boolean registers a flag that is wrangled into a bool and returned as a pointer
///
/// The returned pointer is initialized as the default_value, and should never be a nullptr.
[[nodiscard]] bool* boolean(std::string_view name, bool default_val, std::string usage) noexcept;

/// int32 registers a flag that is wrangled into a int32_t and returned as a pointer
///
/// The returned pointer is initialized as the default_value, and should never be a nullptr.
[[nodiscard]] int32_t* int32(
	std::string_view name,
	int32_t default_val,
	std::string usage
) noexcept;

/// int64 registers a flag that is wrangled into a int64_t and returned as a pointer
///
/// The returned pointer is initialized as the default_value, and should never be a nullptr.
[[nodiscard]] int64_t* int64(
	std::string_view name,
	int64_t default_val,
	std::string usage
) noexcept;
} // namespace in::flag

#endif // ICHNEUTAE_FLAG_PARSER_H
