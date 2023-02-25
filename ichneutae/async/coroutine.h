#ifndef ICHNEUTAE_ASYNC_COROUTINE_H
#define ICHNEUTAE_ASYNC_COROUTINE_H

#include <coroutine>
#include <utility>

namespace in::async {
struct unique_handle_base {
	virtual ~unique_handle_base() = default;
	virtual bool done() const noexcept = 0;
};

/// A wrapper around `coroutine_handle<P>` that manages the handle, calling
/// `destroy` on it when done.
template<typename P = void> class unique_handle final : public unique_handle_base {
	using coroutine_handle = std::coroutine_handle<P>;

	coroutine_handle handle = {};

	explicit unique_handle(coroutine_handle h) : handle{h} {}

public:
	unique_handle() {}

	unique_handle(unique_handle const&) = delete;

	unique_handle(unique_handle&& h) noexcept : handle{std::exchange(h.handle, {})} {}

	~unique_handle() {
		if (handle) {
			handle.destroy();
		}
	}

	unique_handle& operator=(unique_handle const&) = delete;

	unique_handle& operator=(unique_handle&& h) noexcept {
		if (handle) {
			handle.destroy();
		}
		handle = std::exchange(h.handle, {});
		return *this;
	}

	/// Comparison
	template<typename T> bool operator==(unique_handle<T> c) const {
		return get() == c.get();
	}

	template<typename T> bool operator==(coroutine_handle c) const {
		return get() == c;
	}

	/// Allow access to the underlying handle
	auto get() const noexcept {
		return handle;
	}

	auto release() noexcept {
		return std::exchange(handle, {});
	}

	/// Forwarders for `coroutine_handle<P>` members
	explicit operator bool() const noexcept {
		return bool{handle};
	}

	bool done() const noexcept {
		return handle.done();
	}

	template<typename PP> static auto from_promise(PP&& pp) noexcept {
		return unique_handle{coroutine_handle::from_promise(std::forward<PP>(pp))};
	}

	decltype(auto) promise() noexcept {
		return handle.promise();
	}

	decltype(auto) promise() const noexcept {
		return handle.promise();
	}

	void resume() noexcept {
		handle.resume();
	}
};
} // namespace in::async

#endif
