#ifndef CMD_SATYR_COMMAND_GEN_H
#define CMD_SATYR_COMMAND_GEN_H

#include <span>
#include <string>

namespace cmd::satyr::command {
void gen(std::string* workspace_dir, const bool* bin, std::span<std::string> cmds);
} // namespace cmd::satyr::command

#endif // CMD_SATYR_COMMAND_GEN_H
