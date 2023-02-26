#include "ichneutae/bazel/label.h"
#include "ichneutae/os/path.h"
#include "ichneutae/text/replace_all.h"

namespace in::bazel {
void label::parse(std::string_view label_str) noexcept {
	if (label_str.empty()) {
		return;
	}
	auto pivot = label_str.find("//");
	this->workspace = label_str.substr(0, pivot);
	this->directory = label_str.substr(pivot + 2, label_str.length());
	pivot = this->directory.find(':');
	if (pivot == std::string::npos) {
		// if no explict target is given use the name of the directory that the target would reside in
		this->target = os::file_name(this->directory, '/');
	} else {
		// if the label contains an explict label remove it from the dir string
		this->target = this->directory.substr(pivot + 1, this->directory.length());
		this->directory = this->directory.substr(0, pivot);
	}
	// localize path on non-unix systems
	if constexpr (os::path_seperator != '/') {
		text::replace_all(this->directory, "/", std::string{os::path_seperator});
	}
}

} // namespace in::bazel
