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
};

constexpr std::string_view code_to_string_view(result_code code) noexcept {
	switch (code) {
	case result_code::ok:
		return "ok";
	case result_code::invalid_argument:
		return "invalid argument";
	case result_code::unknown:
	default:
		return "unknown";
	}
}

std::string code_to_string(result_code code) noexcept {
	return code_to_string_view(code).begin();
}

// result_payload holds the error details in a result
struct result_payload {
	// message is the body of the error
	std::string message{code_to_string(result_code::ok)};
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

/// result_or encapsulates a value and an error result
template<typename T = void> class result_or {
	T data{};
	in::result rs{};

public:
	result_or() = delete;

	result_or(T&& data) : data{std::forward<T>(data)} {}

	result_or(in::result&& res) : rs{std::move(res)} {}

	// not copyable
	result_or(result_or&) = delete;
	result_or& operator=(const result_or&) = delete;

	// is movable
	result_or(result_or&&) noexcept = default;
	result_or& operator=(result_or&&) noexcept = default;

	/// ok returns true if the result code == result_code::ok
	[[nodiscard]] bool ok() const noexcept {
		return this->rs.ok();
	}

	/// message returns the results message
	[[nodiscard]] std::string_view message() const noexcept {
		return this->rs.message();
	}

	/// res ejects the result object
	[[nodiscard]] in::result result() noexcept {
		return std::move(this->rs);
	}

	/// value unwraps the returned value
	[[nodiscard]] T value() noexcept {
		return std::move(this->data);
	}
};

[[nodiscard]] result ok_result() noexcept;

[[nodiscard]] result invalid_argument(const std::string& msg) noexcept;

[[nodiscard]] result unknown() noexcept;

[[nodiscard]] result unknown(const std::string& msg) noexcept;
} // namespace in

#endif // ICHNEUTAE_RESULT_H
