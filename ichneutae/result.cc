#include "ichneutae/result.h"

namespace in {
constexpr std::string_view code_to_string_view(result_code code) noexcept {
	switch (code) {
	case result_code::ok:
		return "ok";
	case result_code::invalid_argument:
		return "invalid argument";
	case result_code::failed_precondition:
		return "failed_precondition";
	case result_code::not_found:
		return "not_found";
	case result_code::unknown:
	default:
		return "unknown";
	}
}

std::string code_to_string(result_code code) noexcept {
	return code_to_string_view(code).begin();
}

result_code result::code() const noexcept {
	if (this->payload) {
		return this->payload->code;
	}
	return result_code::ok;
}

std::string_view result::message() const noexcept {
	if (this->payload) {
		return this->payload->message;
	}
	return code_to_string_view(result_code::ok);
}

bool result::ok() const noexcept {
	if (this->payload) {
		return this->payload->code == result_code::ok;
	}
	return true;
}

std::string result::to_string() noexcept {
	if (this->payload) {
		return this->payload->message;
	}
	return code_to_string(result_code::ok);
}

result ok_result() noexcept {
	return {result_code::ok, code_to_string(result_code::ok)};
}

result invalid_argument(const std::string& msg) noexcept {
	return {
		result_code::invalid_argument,
		code_to_string(result_code::invalid_argument) + ": " + msg,
	};
}

result failed_precondition(const std::string& msg) noexcept {
	return {
		result_code::failed_precondition,
		code_to_string(result_code::failed_precondition) + ": " + msg,
	};
}

result not_found(std::string_view msg) noexcept {
	return {
		result_code::not_found,
		code_to_string(result_code::not_found) + ": " + std::string(msg),
	};
}

result unknown() noexcept {
	return {result_code::unknown, code_to_string(result_code::unknown)};
}

result unknown(const std::string& msg) noexcept {
	return {result_code::unknown, code_to_string(result_code::unknown) + ": " + msg};
}
} // namespace in
