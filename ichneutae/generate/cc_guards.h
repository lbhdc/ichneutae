#ifndef ICHNEUTAE_GENERATE_CC_GUARDS_H
#define ICHNEUTAE_GENERATE_CC_GUARDS_H

#include <string>
#include <string_view>

namespace in::generate {
/// cc_guards converts a filesystem path to a cc header guard
std::string cc_guards(std::string_view path_to_file, std::string_view prefix = "") noexcept;

} // namespace in::generate

#endif
