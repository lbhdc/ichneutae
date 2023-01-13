#ifndef ICHNEUTAE_MEMORY_RAW_MEMORY_H
#define ICHNEUTAE_MEMORY_RAW_MEMORY_H

#include <array>
#include <memory>
#include <type_traits>

namespace in::memory {
template<typename T> class raw_memory {
	std::array<std::byte, sizeof(T)> bytes alignas(T);

public:
	using value_type = std::remove_cv_t<std::remove_reference_t<T>>;
	using const_value_type = std::add_const<value_type>;
	using reference_type = std::add_lvalue_reference_t<value_type>;
	using const_reference_type = std::add_lvalue_reference_t<const_value_type>;
	using pointer_type = std::add_pointer_t<value_type>;
	using const_pointer_type = std::add_pointer_t<const_value_type>;

	constexpr raw_memory() noexcept = default;

	raw_memory(const raw_memory&) = delete;
	raw_memory& operator=(const raw_memory&) = delete;

	constexpr raw_memory(raw_memory&&) noexcept = default;
	constexpr raw_memory& operator=(raw_memory&&) noexcept = default;

	[[nodiscard]] constexpr pointer_type data() noexcept {
		return std::launder(reinterpret_cast<pointer_type>(this->bytes.data()));
	}

	[[nodiscard]] constexpr const_pointer_type data() const noexcept {
		return std::launder(reinterpret_cast<const_pointer_type>(this->bytes.data()));
	}

	[[nodiscard]] constexpr reference_type value() noexcept {
		return *this->data();
	}

	[[nodiscard]] constexpr const_reference_type value() const noexcept {
		return *this->data();
	}

	template<typename... Args> constexpr reference_type emplace(Args... args) noexcept {
		// initialize bytes
		new (this->data()) value_type{std::forward<Args>(args)...};
		return this->value();
	}

	[[nodiscard]] constexpr reference_type assign_or_emplace(
		const bool holds,
		value_type t
	) noexcept {
		if (holds) {
			return this->value() = std::move(t);
		}
		return this->template emplace(std::move(t));
	}

	constexpr void destroy_if(const bool should_destroy) noexcept {
		if (should_destroy) {
			std::destroy_at(this->data());
		}
	}
};
} // namespace in::memory

#endif // ICHNEUTAE_MEMORY_RAW_MEMORY_H
