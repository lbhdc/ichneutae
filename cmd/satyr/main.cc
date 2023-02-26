#include "ichneutae/bazel/label.h"
#include "ichneutae/bazel/workspace.h"
#include "ichneutae/flag/parser.h"
#include "ichneutae/generate/cc_build.h"
#include "ichneutae/generate/cc_guards.h"
#include "ichneutae/generate/cc_header.h"
#include "ichneutae/generate/cc_namespace.h"
#include "ichneutae/generate/cc_source.h"
#include "ichneutae/os/path.h"
#include "ichneutae/version.h"
#include <iostream>

const auto bin = in::flag::boolean("bin", false, "Generate files for a bin instead of a lib");
const auto version = in::flag::boolean("version", false, "Print the program version");
const auto workspace_dir = in::flag::string("workspace-dir", "", "Set the project root directory");

void gen_command(std::span<std::string> cmds);

int main(int argc, char* argv[]) {
	in::flag::parse(argc, argv);
	if (*version) {
		std::cout << in::flag::executable_name() << ' ' << in::version << '\n';
		std::exit(EXIT_SUCCESS);
	}
	if (in::flag::nargs() > 0) {
		auto args = in::flag::argv();
		if ("gen" == args.front()) {
			gen_command({args.begin() + 1, args.end()});
		}
	}
	std::cerr << "un-recognized command\n";
	std::exit(EXIT_FAILURE);
}

void gen_command(std::span<std::string> cmds) {
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
	auto gen_cc_build = [&] {
		auto build_path = in::os::join(workspace, label.directory, "BUILD");
		in::generate::cc_build(
			build_path,
			{{"{{NAME}}", label.target}, {"{{DIR_NAME}}", in::os::dir(label.directory)}},
			*bin
		);
	};
	auto gen_cc_header = [&] {
		auto path = in::os::join(workspace, label.directory, label.target + ".h");
		in::generate::cc_header(
			path,
			{{"{{HEADER_GUARD}}",
				in::generate::cc_guards(in::os::join(label.directory, label.target + ".h"))},
			 {"{{NAMESPACE}}", in::generate::cc_namespace(label)}}
		);
	};
	auto gen_cc_source = [&] {
		auto path = in::os::join(workspace, label.directory, label.target + ".cc");
		in::generate::cc_source(
			path,
			{{"{{HEADER_FILE_PATH}}",
				in::generate::cc_guards(in::os::join(label.directory, label.target + ".cc"))},
			 {"{{NAMESPACE}}", in::generate::cc_namespace(label)}},
			*bin
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
