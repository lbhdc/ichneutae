#ifndef ICHNEUTAE_TEXT_REPLACE_ALL_H
#define ICHNEUTAE_TEXT_REPLACE_ALL_H

#include <string>
#include <string_view>

namespace in::text {
size_t replace_all(std::string& inout, std::string_view what, std::string_view with);

} // namespace in::text

#endif
