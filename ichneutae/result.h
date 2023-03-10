#ifndef ICHNEUTAE_RESULT_H
#define ICHNEUTAE_RESULT_H

#include <cstdint>
#include <filesystem>
#include <memory>
#include <string>
#include <string_view>

namespace in {
enum class result_code : int {
	ok = 0,
	unknown = 1,
	invalid_argument = 2,
	failed_precondition = 3,
	not_found = 4,
};

// result_payload holds the error details in a result
struct result_payload {
	// message is the body of the error
	std::string message{"ok"};
	// code is the category the error belongs to
	result_code code{result_code::ok};
};

/// result is an error result type that encapsulates an error message and error code
///
/// If a result is default constructed the default behavior is that of `ok_result`.
class result {
	// payload is a pointer to the error details
	std::unique_ptr<result_payload> payload{};

public:
	constexpr result() noexcept = default;

	result(result_code code, std::string message) noexcept
			: payload{std::make_unique<result_payload>(result_payload{std::move(message), code})} {}

	// isn't copyable
	result(result&) = delete;
	result& operator=(result&) = delete;

	// is movable
	result(result&&) noexcept = default;
	result& operator=(result&&) noexcept = default;

	~result() = default;

	/// code returns the numeric code associated with a result
	[[nodiscard]] result_code code() const noexcept;

	/// message returns a string_view of an error message
	[[nodiscard]] std::string_view message() const noexcept;

	/// ok returns true if the code() == result_code::ok
	[[nodiscard]] bool ok() const noexcept;

	/// to_string returns the error message as a std::string
	[[nodiscard]] std::string to_string() noexcept;
};

[[nodiscard]] result ok_result() noexcept;

[[nodiscard]] result invalid_argument(const std::string& msg) noexcept;

[[nodiscard]] result failed_precondition(const std::string& msg) noexcept;

[[nodiscard]] result not_found(std::string_view) noexcept;

[[nodiscard]] result unknown() noexcept;

[[nodiscard]] result unknown(const std::string& msg) noexcept;
} // namespace in

#endif // ICHNEUTAE_RESULT_H
