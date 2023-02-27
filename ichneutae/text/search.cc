#include "ichneutae/text/search.h"
#include <algorithm>
#include <fstream>

namespace in::text {
result_or<search_match> search_glob(
	const std::string_view haystack,
	const std::string_view needle,
	const int row_num
) noexcept {
	const auto it = std::search(haystack.begin(), haystack.end(), needle.begin(), needle.end());
	if (it == haystack.end()) {
		return not_found(needle);
	}
	const auto match_start = it - haystack.begin();
	return search_match{
		row_num,
		static_cast<int>(match_start),
		static_cast<int>(needle.size()),
		haystack.begin()};
}

async::generator<search_match> search(std::istream& haystack, std::string_view needle) noexcept {
	auto row_idx{0};
	for (std::string row; std::getline(haystack, row);) {
		auto rs = search_glob(row, needle, row_idx);
		++row_idx;
		if (not rs.ok()) {
			continue;
		}
		co_yield rs.value();
	}
}
} // namespace in::text
