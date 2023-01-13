#ifndef ICHNEUTAE_MEMORY_RAW_MEMORY_H
#define ICHNEUTAE_MEMORY_RAW_MEMORY_H

#include <array>
#include <memory>
#include <type_traits>

namespace in::memory {
template<typename T> class raw_memory {
	std::array<std::byte, sizeof(T)> pen alignas(T);

public:
	using value_type = std::remove_cv_t<std::remove_reference_t<T>>;
	using reference_type = std::add_lvalue_reference_t<value_type>;
	using const_reference_type = std::add_lvalue_reference_t<value_type const>;
	using pointer_type = std::add_pointer_t<value_type>;
	using const_pointer_type = std::add_pointer_t<value_type const>;

	constexpr raw_memory() = default;

	// not copyable
	raw_memory(const raw_memory&) = delete;
	raw_memory& operator=(raw_memory const&) = delete;

	// not movable
	raw_memory(raw_memory&&) = delete;
	raw_memory& operator=(raw_memory&&) = delete;

	[[nodiscard]] constexpr pointer_type data() noexcept {
		return std::launder(reinterpret_cast<pointer_type>(this->pen.data()));
	}

	[[nodiscard]] constexpr const_pointer_type data() const noexcept {
		return std::launder(reinterpret_cast<const_pointer_type>(this->pen.data()));
	}

	constexpr reference_type value() noexcept {
		return *this->data();
	}

	constexpr const_reference_type value() const noexcept {
		return *this->data();
	}

	template<typename... Args> constexpr reference_type emplace(Args... args) {
		std::construct_at<value_type>(this->data(), std::forward<Args>(args)...);
		return *this->data();
	}

	constexpr reference_type assign_or_emplace(const bool holds, value_type t) {
		if (holds) {
			return (*this->data() = std::move(t));
		} else {
			return emplace(std::move(t));
		}
	}

	constexpr void destroy_if(const bool destroy) noexcept {
		if (destroy) {
			std::destroy_at(this->data());
		}
	}
};
} // namespace in::memory

#endif // ICHNEUTAE_MEMORY_RAW_MEMORY_H
