#ifndef SILVERSEARCHER_TEXT_SEARCH_H
#define SILVERSEARCHER_TEXT_SEARCH_H

#include <string_view>
#include <string>

namespace ag::text {
/// contains is a thin wrapper around find that returns false when the needle is npos
template<typename N> constexpr bool contains(std::string_view haystack, N&& needle) noexcept {
  return haystack.find(std::forward<N>(needle)) != std::string::npos;
}
}

#endif // SILVERSEARCHER_TEXT_SEARCH_H
