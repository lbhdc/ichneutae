#include "cmd/satyr/command/gen.h"
#include "ichneutae/bazel/label.h"
#include "ichneutae/bazel/workspace.h"
#include "ichneutae/generate/cc_build.h"
#include "ichneutae/generate/cc_guards.h"
#include "ichneutae/generate/cc_header.h"
#include "ichneutae/generate/cc_namespace.h"
#include "ichneutae/generate/cc_source.h"
#include "ichneutae/os/path.h"
#include <iostream>

namespace cmd::satyr::command {
void gen(std::string* workspace_dir, const bool* bin, std::span<std::string> cmds) {
	if (cmds.size() != 2) {
		std::cerr << "gen expects 3 arguments; gen <action> <bazel-label>";
		std::exit(EXIT_FAILURE);
	}
	auto action = cmds.front();
	auto label = in::bazel::label(cmds.back());
	// find the absolute path the workspace root, if it's not passed in, find it.
	auto workspace = *workspace_dir;
	if (workspace.empty()) {
		auto r = in::bazel::workspace();
		if (not r.ok()) {
			std::cerr << r.message();
			std::exit(EXIT_FAILURE);
		}
		workspace = r.value();
	}
	// not able to operate on remote labels
	if (label.is_remote()) {
		std::cerr << "remove labels aren't supported";
		std::exit(EXIT_FAILURE);
	}
	// create any directories needed
	auto absolute_dir_path = in::os::join(workspace, label.directory);
	if (not std::filesystem::create_directories(absolute_dir_path)) {
		if (not std::filesystem::exists(absolute_dir_path)) {
			std::cerr << "failed to create directory: " << absolute_dir_path;
			std::exit(EXIT_FAILURE);
		}
	}
	const auto target = *bin ? in::generate::cc_target::binary : in::generate::cc_target::library;
	const auto gen_cc_build = [&] {
		const auto build_path = in::os::join(workspace, label.directory, "BUILD");
		in::generate::cc_build(
			build_path,
			{{"{{NAME}}", label.target}, {"{{DIR_NAME}}", in::os::file_name(label.directory)}},
			target
		);
	};
	const auto gen_cc_header = [&] {
		const auto path = in::os::join(workspace, label.directory, label.target + ".h");
		in::generate::cc_header(
			path,
			{{"{{HEADER_GUARD}}",
				in::generate::cc_guards(in::os::join(label.directory, label.target + ".h"))},
			 {"{{NAMESPACE}}", in::generate::cc_namespace(label)}}
		);
	};
	const auto gen_cc_source = [&] {
		const auto path = in::os::join(workspace, label.directory, label.target + ".cc");
		in::generate::cc_source(
			path,
			{{"{{HEADER_FILE_PATH}}", in::os::join(label.directory, label.target + ".h")},
			 {"{{NAMESPACE}}", in::generate::cc_namespace(label)}},
			target
		);
	};
	// mux action and execute code generators
	if ("cc-build" == action) {
		gen_cc_build();
		std::exit(EXIT_SUCCESS);
	} else if ("cc-header" == action) {
		gen_cc_header();
		std::exit(EXIT_SUCCESS);
	} else if ("cc-source" == action) {
		gen_cc_source();
		std::exit(EXIT_SUCCESS);
	} else if ("cc-pkg" == action) {
		gen_cc_build();
		gen_cc_header();
		gen_cc_source();
		std::exit(EXIT_SUCCESS);
	}
	std::cerr << "gen unknown action; got = '" << action << '\'';
	std::exit(EXIT_FAILURE);
}
} // namespace cmd::satyr::command
