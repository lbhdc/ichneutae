#ifndef ICHNEUTAE_ASYNC_GENERATOR_H
#define ICHNEUTAE_ASYNC_GENERATOR_H

#include "ichneutae/async/coroutine.h"
#include "ichneutae/memory/aligned_allocator.h"
#include "ichneutae/memory/holding_pen.h"

namespace in::async {
template<typename T, typename Allocator> struct generator_promise;

template<typename T, typename Allocator = void> class generator {
	friend struct generator_promise<T, Allocator>;

	using handle_type = generator_promise<T, Allocator>::handle_type;

	handle_type handle;

	constexpr generator(handle_type h) noexcept : handle{std::move(h)} {}

public:
	using promise_type = generator_promise<T, Allocator>;

	constexpr ~generator() = default;

	// is movable
	constexpr generator(generator&&) noexcept = default;
	constexpr generator& operator=(generator&&) noexcept = default;

	// not copyable
	generator(const generator&) = delete;
	generator& operator=(const generator&) = delete;

	class iterator {
		friend class generator;

		handle_type handle{};

		iterator() noexcept = default;

		iterator(generator* g) noexcept : handle{std::move(g->handle)} {
			this->handle.resume();
			this->throw_if_needed();
		}

		constexpr void throw_if_needed() const {
			if (this->handle.promise().eptr) {
				std::rethrow_exception(this->handle.promise().eptr);
			}
		}

	public:
		// is movable
		iterator(iterator&&) noexcept = default;
		iterator& operator=(iterator&&) noexcept = default;

		// not copyable
		iterator(const iterator&) = delete;
		iterator& operator=(const iterator&) = delete;

		constexpr ~iterator() = default;

		[[nodiscard]] friend bool operator==(const iterator& lhs, const iterator& rhs) noexcept {
			if (not lhs.handle && not rhs.handle) {
				return true;
			} else if ((lhs.handle and lhs.handle.done()) and not rhs.handle) {
				return true;
			} else if (not lhs.handle and (rhs.handle and rhs.handle.done())) {
				return true;
			}
			return false;
		}

		[[nodiscard]] constexpr T operator*() noexcept {
			return static_cast<T&&>(std::move(this->handle.promise().value).release().value());
		}

		iterator& operator++() {
			this->handle.resume();
			this->throw_if_needed();
			if (not this->handle.promise().value) {
				this->handle = {};
			}
			return *this;
		}
	};

	[[nodiscard]] iterator begin() noexcept {
		return iterator{this};
	}

	[[nodiscard]] iterator end() noexcept {
		return iterator{};
	}

	[[nodiscard]] constexpr memory::holding_pen<T> next() {
		this->handle.resume();
		if (this->handle.promise().eptr) {
			std::rethrow_exception(this->handle.promise().eptr);
		}
		return std::move(this->handle.promise().value).release();
	}
};

template<typename T, typename Allocator> struct generator_promise
		: private memory::aligned_allocator<Allocator> {
	using memory::aligned_allocator<Allocator>::operator new;

	using memory::aligned_allocator<Allocator>::operator delete;

	using handle_type = unique_handle<generator_promise>;

	memory::holding_pen<T> value{};

	std::exception_ptr eptr{nullptr};

	template<typename U> std::suspend_always await_transform(U&&) = delete;

	[[nodiscard]] constexpr auto final_suspend() noexcept {
		return std::suspend_always{};
	}

	[[nodiscard]] constexpr auto get_return_object() noexcept {
		return generator<T, Allocator>{handle_type::from_promise(*this)};
	}

	[[nodiscard]] constexpr auto initial_suspend() noexcept {
		return std::suspend_always{};
	}

	[[nodiscard]] constexpr auto return_void() noexcept {
		this->value.reset();
		return std::suspend_never{};
	}

	constexpr void unhandled_exception() noexcept {
		this->eptr = std::current_exception();
	}

	[[nodiscard]] constexpr auto yield_value(T val) noexcept {
		this->value.emplace(std::move(val));
		return std::suspend_always{};
	}
};
} // namespace in::async

#endif
