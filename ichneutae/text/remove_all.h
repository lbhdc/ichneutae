#ifndef ICHNEUTAE_TEXT_REMOVE_ALL_H
#define ICHNEUTAE_TEXT_REMOVE_ALL_H

#include "ichneutae/text/replace_all.h"
#include <string>
#include <string_view>

namespace in::text {
size_t remove_all(std::string& inout, std::string_view what) {
	return replace_all(inout, what, "");
}

} // namespace in::text

#endif
