#include "ichneutae/text/replace_all.h"

namespace in::text {
size_t replace_all(std::string& inout, std::string_view what, std::string_view with) {
	size_t count{};
	for (std::string::size_type pos{};
			 inout.npos != (pos = inout.find(what.data(), pos, what.length()));
			 pos += with.length(), ++count) {
		inout.replace(pos, what.length(), with.data(), with.length());
	}
	return count;
}

} // namespace in::text
