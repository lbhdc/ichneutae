#ifndef ICHNEUTAE_OS_FILES_H
#define ICHNEUTAE_OS_FILES_H

#include "ichneutae/result.h"

namespace in::os {
/// create_directories all non-existent directories in a path
result create_directories(std::string_view path_to_create) noexcept;
} // namespace in::os

#endif // ICHNEUTAE_OS_FILES_H
