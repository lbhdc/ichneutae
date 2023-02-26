#include "ichneutae/result.h"

namespace in {
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

result unknown() noexcept {
	return {result_code::unknown, code_to_string(result_code::unknown)};
}

result unknown(const std::string& msg) noexcept {
	return {result_code::unknown, code_to_string(result_code::unknown) + ": " + msg};
}
} // namespace in
