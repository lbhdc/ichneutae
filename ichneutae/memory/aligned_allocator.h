#ifndef ICHNEUTAE_MEMORY_ASYNC_H
#define ICHNEUTAE_MEMORY_ASYNC_H

#include <bit>
#include <cstddef>
#include <new>

namespace in::memory {
template<typename Allocator> struct aligned_allocator;

template<> struct aligned_allocator<void> {
	[[nodiscard]] void* operator new(std::size_t n) {
		return ::operator new(n);
	}

	void operator delete(void* const prt, size_t) {
		return ::operator delete(prt);
	}
};

template<typename Allocator> struct aligned_allocator {
	struct allocation {
		Allocator* allocator{nullptr};
	};

	static constexpr size_t aligned_offset(const size_t base) noexcept {
		const size_t alignment = alignof(allocation);
		return (base + alignment - 1) & ~(alignment - 1);
	}

	[[nodiscard]] constexpr void* operator new(const size_t psz) noexcept {
		const auto alloc_base = aligned_offset(psz);
		const auto sz = alloc_base + sizeof(allocation);
		auto base = reinterpret_cast<std::byte*>(::operator new(sz));
		new (base + alloc_base) allocation{};
		return base;
	}

	template<typename... Args> [[nodiscard]] constexpr void* operator new(
		const size_t psz,
		Allocator& alloc,
		Args&...
	) noexcept {
		const auto alloc_base = aligned_offset(psz);
		const auto sz = alloc_base + sizeof(allocation);
		auto base = reinterpret_cast<std::byte*>(alloc.allocate(sz));
		new (base + alloc_base) allocation{&alloc};
		return base;
	}

	template<typename This, typename... Args>
	void* operator new(const size_t sz, This&&, Allocator& alloc, Args&...) {
		return operator new(sz, alloc);
	}

	constexpr void operator delete(void* const ptr, size_t psz) noexcept {
		const auto alloc_base = aligned_offset(psz);
		auto* const base = reinterpret_cast<std::byte*>(ptr);
		auto* alloc = std::launder(reinterpret_cast<allocation*>(base + alloc_base));
		if (alloc->allocator) {
			const auto sz = alloc_base + sizeof(allocation);
			auto* alc = alloc->allocator;
			alc->deallocate(ptr, sz);
		} else {
			::operator delete(ptr);
		}
	}
};
} // namespace in::memory

#endif
