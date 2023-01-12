#ifndef ICHNEUTAE_TEXT_SEARCH_H
#define ICHNEUTAE_TEXT_SEARCH_H

#include <string>
#include <string_view>

namespace in::text {
/// contains is a thin wrapper around find that returns false when the needle is npos
template<typename N> constexpr bool contains(std::string_view haystack, N&& needle) noexcept {
	return haystack.find(std::forward<N>(needle)) != std::string::npos;
}
} // namespace in::text

#endif // ICHNEUTAE_TEXT_SEARCH_H
