#ifndef ICHNEUTAE_RESULT_OR_H
#define ICHNEUTAE_RESULT_OR_H

#include "ichneutae/result.h"

namespace in {
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
} // namespace in

#endif // ICHNEUTAE_RESULT_OR_H
