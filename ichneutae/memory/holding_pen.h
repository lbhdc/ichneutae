#ifndef ICHNEUTAE_MEMORY_SMART_PTR_H
#define ICHNEUTAE_MEMORY_SMART_PTR_H

#include "ichneutae/memory/raw_memory.h"
#include <cstdlib>
#include <iostream>

namespace in::memory {
template<typename T> class holding_pen {
	using pointer_type = typename raw_memory<T>::pointer_type;
	using const_pointer_type = typename raw_memory<T>::const_pointer_type;
	using value_type = typename raw_memory<T>::value_type;
	using reference_type = typename raw_memory<T>::reference_type;
	using const_reference_type = typename raw_memory<T>::const_reference_type;

	raw_memory<T> data;

	bool holding{false};

public:
	constexpr holding_pen() noexcept : holding{false} {}

	// not copyable
	holding_pen(const holding_pen&) = delete;
	holding_pen& operator=(const holding_pen&) = delete;

	constexpr holding_pen(T&& t) noexcept : holding{true} {
		this->data.emplace(std::move(t));
	}

	constexpr holding_pen(holding_pen&& p) noexcept : holding{p.holding} {
		if (this->holding) {
			this->data.emplace(std::move(p.data.value()));
		}
	}

	constexpr ~holding_pen() {
		this->reset();
	}

	[[nodiscard]] constexpr bool empty() const noexcept {
		return not this->holding;
	}

	constexpr void assign(value_type v) noexcept {
		this->reset();
		this->emplace(std::move(v));
	}

	template<typename... Args> constexpr reference_type emplace(Args... args) noexcept {
		this->reset();
		return this->data.emplace(std::forward<Args>(args)...);
	}

	constexpr holding_pen release() && {
		if (not this->holding) {
			return holding_pen{};
		}
		auto v = value_type{std::move(this->value())};
		this->reset();
		return v;
	}

	constexpr void reset() noexcept {
		this->data.destroy_if(std::exchange(this->holding, false));
	}

	[[nodiscard]] constexpr reference_type value() noexcept {
		if (this->holding) [[likely]] {
			return this->data.value();
		}
		std::cout << "memory: illegal access of empty smart pointer";
		std::exit(EXIT_FAILURE);
	}

	[[nodiscard]] constexpr const_reference_type value() const noexcept {
		if (this->holding) [[likely]] {
			return this->data.value();
		}
		std::cout << "memory: illegal access of empty smart pointer";
		std::exit(EXIT_FAILURE);
	}

	holding_pen& operator=(holding_pen&& ptr) noexcept {
		if (ptr.holding) {
			this->assign(std::move(ptr.data.value()));
		} else {
			this->reset();
		}
		return *this;
	}

	[[nodiscard]] constexpr pointer_type operator->() noexcept {
		return this->value();
	}

	[[nodiscard]] constexpr const_pointer_type operator->() const noexcept {
		return this->value();
	}

	friend bool operator==(const holding_pen& lhs, const holding_pen& rhs) noexcept {
		if (lhs.holding != rhs.holding) {
			return false;
		}
		if (not lhs.holding and not rhs.holding) {
			return true;
		}
		return *(rhs.data).data() == *(rhs.data).data();
	}
};
} // namespace in::memory

#endif // ICHNEUTAE_MEMORY_SMART_PTR_H
