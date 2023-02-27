#ifndef ICHNEUTAE_OS_USER_HOME_H
#define ICHNEUTAE_OS_USER_HOME_H

#include "ichneutae/result_or.h"
#include <string>

namespace in::os {
/// user_nome returns the current users home directory
[[nodiscard]] result_or<std::string> user_home() noexcept;
} // namespace in::os

#endif // ICHNEUTAE_OS_USER_HOME_H
