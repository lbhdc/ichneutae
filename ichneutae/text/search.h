#ifndef ICHNEUTAE_TEXT_SEARCH_H
#define ICHNEUTAE_TEXT_SEARCH_H

#include "ichneutae/async/generator.h"
#include "ichneutae/result_or.h"
#include <string_view>

namespace in::text {
/// search_match is the location in a corpus of location of a match
struct search_match {
	/// row is the nth row of a search corpus where the match was found
	int row{-1};
	/// column is the start of the match in data
	int column{-1};
	/// match_length is the length of the match
	int match_length{-1};
	/// data is a copy of the row that was matched
	std::string data{};

	search_match() noexcept = default;

	search_match(int r, int col, int ml, std::string&& d) noexcept
			: row{r}, column{col}, match_length{ml}, data{d} {}

	// not copyable
	search_match(const search_match&) = delete;
	search_match& operator=(const search_match&) = delete;

	// is movable
	search_match(search_match&&) noexcept = default;
	search_match& operator=(search_match&&) noexcept = default;

	~search_match() = default;
};

/// search_glob returns a search_match if a needle is in a haystack
[[nodiscard]] result_or<search_match> search_glob(
	std::string_view haystack,
	std::string_view needle,
	int row_num = -1
) noexcept;

/// search returns a generator that returns a search_match for each row found
async::generator<search_match> search(std::istream& haystack, std::string_view needle) noexcept;
} // namespace in::text

#endif // ICHNEUTAE_TEXT_SEARCH_H
