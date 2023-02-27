#include "cmd/satyr/command/gen.h"
#include "ichneutae/flag/parser.h"
#include "ichneutae/version.h"
#include <iostream>

const auto bin = in::flag::boolean("bin", false, "Generate files for a bin instead of a lib");
const auto version = in::flag::boolean("version", false, "Print the program version");
const auto workspace_dir = in::flag::string("workspace-dir", "", "Set the project root directory");

int main(int argc, char* argv[]) {
	in::flag::parse(argc, argv);
	if (*version) {
		std::cout << in::flag::executable_name() << ' ' << in::version << '\n';
		std::exit(EXIT_SUCCESS);
	}
	if (in::flag::nargs() > 0) {
		auto args = in::flag::argv();
		if ("gen" == args.front()) {
			cmd::satyr::command::gen(workspace_dir, bin, {args.begin() + 1, args.end()});
		}
	}
	std::cerr << "un-recognized command\n";
	std::exit(EXIT_FAILURE);
}
