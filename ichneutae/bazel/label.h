#ifndef COLLECTIVE_ICHNEUTAE_BAZEL_LABEL_H
#define COLLECTIVE_ICHNEUTAE_BAZEL_LABEL_H

#include <string>
#include <string_view>

namespace in::bazel {
/// label is a representation of a bazel label
struct label {
	/// workspace is the name of the workspace derived from the directory name. For local workspaces
	/// this value is empy.
	std::string workspace{};
	/// directory is the filesystem path from the workspace root to the package. If the package is at
	/// the workspace root this value is empty.
	std::string directory{};
	/// is the name of the bazel target.
	std::string target{};

	explicit label(std::string_view label_str) noexcept {
		this->parse(label_str);
	}

	/// is_remote returns if the parsed label is not a local workspace
	[[nodiscard]] bool is_remote() const noexcept {
		return (not this->workspace.empty()) and not(this->workspace == "@");
	}

	/// parse a string into a bazel label
	void parse(std::string_view label_str) noexcept;
};
} // namespace in::bazel

#endif
