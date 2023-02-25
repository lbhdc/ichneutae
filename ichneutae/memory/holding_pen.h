#ifndef ICHNEUTAE_MEMORY_SMART_PTR_H
#define ICHNEUTAE_MEMORY_SMART_PTR_H

#include "ichneutae/memory/raw_memory.h"
#include <cstdlib>
#include <iostream>

namespace in::memory {
template<typename T> class holding_pen final {
	using pointer_type = typename raw_memory<T>::pointer_type;
	using const_pointer_type = typename raw_memory<T>::const_pointer_type;
	using value_type = typename raw_memory<T>::value_type;
	using reference_type = typename raw_memory<T>::reference_type;
	using const_reference_type = typename raw_memory<T>::const_reference_type;

	raw_memory<T> store;
	bool holding{false};

public:
	constexpr holding_pen() noexcept = default;

	constexpr holding_pen(T&& t) noexcept : holding{true} {
		this->store.emplace(std::move(t));
	}

	// not copyable
	constexpr holding_pen(holding_pen const&) = delete;
	holding_pen& operator=(holding_pen const&) = delete;

	// is movable
	constexpr holding_pen(holding_pen&& h) noexcept : holding{h.holding} {
		if (this->holding) {
			this->store.emplace(std::move(h.store.value()));
		}
	}

	holding_pen& operator=(holding_pen&& hp) noexcept {
		if (hp.holding) {
			assign(std::move(hp.store.value()));
		} else {
			this->reset();
		}
		return *this;
	}

	constexpr ~holding_pen() {
		this->reset();
	}

	constexpr reference_type value() noexcept {
		if (this->holding) [[likely]] {
			return *this->store.data();
		}
		std::cerr << "memory: holding pen empty";
		std::exit(EXIT_FAILURE);
	}

	[[nodiscard]] constexpr bool empty() const noexcept {
		return not this->holding;
	}

	constexpr void assign(value_type t) noexcept {
		this->store.destroy_if(std::exchange(this->holding, true));
		this->store.emplace(std::move(t));
	}

	template<typename... Args> constexpr reference_type emplace(Args... args) noexcept {
		this->store.destroy_if(std::exchange(this->holding, true));
		return this->store.emplace(std::forward<Args>(args)...);
	}

	constexpr void reset() noexcept {
		this->store.destroy_if(std::exchange(this->holding, false));
	}

	[[nodiscard]] constexpr holding_pen release() && noexcept {
		if (not this->holding) {
			return holding_pen{};
		} else {
			value_type r{std::move(value())};
			this->reset();
			return r;
		}
	}

	[[nodiscard]] constexpr const_reference_type value() const noexcept {
		if (this->holding) [[likely]] {
			return *this->store.data();
		}
		std::cerr << "memory: holding pen empty";
		std::exit(EXIT_FAILURE);
	}

	template<typename U>
	[[nodiscard]] constexpr value_type value_or(U&& default_value) const noexcept {
		if (this->holding) {
			return *this->store.data();
		}
		return static_cast<value_type>(std::forward<U>(default_value));
	}

	[[nodiscard]] constexpr pointer_type operator->() noexcept {
		return &this->value();
	}

	[[nodiscard]] constexpr const_pointer_type operator->() const noexcept {
		return &this->value();
	}

	[[nodiscard]] constexpr reference_type operator*() noexcept {
		return this->value();
	}

	[[nodiscard]] constexpr const_reference_type operator*() const noexcept {
		return this->value();
	}

	[[nodiscard]] explicit constexpr operator bool() const noexcept {
		return this->holding;
	}

	[[nodiscard]] constexpr friend bool operator==(
		holding_pen const& l,
		holding_pen const& r
	) noexcept {
		if (l.holding != r.holding) {
			return false;
		} else if (not l.holding and not r.holding) {
			return true;
		} else {
			return *(r.store).data() == *(l.store).data();
		}
	}
};
} // namespace in::memory

#endif // ICHNEUTAE_MEMORY_SMART_PTR_H
