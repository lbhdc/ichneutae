#include "ichneutae/flag/parser.h"
#include "ichneutae/os/user_home.h"
#include "ichneutae/text/search.h"
#include "ichneutae/version.h"
#include <filesystem>
#include <fstream>
#include <iostream>

const auto version = in::flag::boolean("version", false, "Print the program version");
const auto haystack = in::flag::string("haystack", "", "The root directory to search");

int main(int argc, char* argv[]) {
	in::flag::parse(argc, argv);
	if (*version) {
		std::cout << in::flag::executable_name() << ' ' << in::version << '\n';
		std::exit(EXIT_SUCCESS);
	}
	std::string needle;
	if (in::flag::nargs() >= 1) {
		needle = in::flag::argv().front();
		// if an explicit dir root wasn't give and two arguments were passed use the second arg. If
		// neither were passed use the current working directory.
		if (in::flag::nargs() == 2 and haystack->empty()) {
			*haystack = in::flag::argv().back();
		} else if (haystack->empty()) {
			*haystack = std::filesystem::current_path().string();
		}
		// resolve tilde path
		if ('~' == haystack->front()) {
			auto rs = in::os::user_home();
			if (not rs.ok()) {
				std::cerr << "unable to resolve users home directory\n";
				std::exit(EXIT_FAILURE);
			}
			*haystack = rs.value() + haystack->substr(1, haystack->size());
		}
	} else {
		std::cerr << "un-recognized arguments\n";
		std::exit(EXIT_FAILURE);
	}
	for (const auto& path : std::filesystem::recursive_directory_iterator(
				 *haystack,
				 std::filesystem::directory_options::skip_permission_denied
			 )) {
		if (not path.is_directory()) {
			auto input = std::ifstream(path.path());
			for (auto match : in::text::search(input, needle)) {
				std::cout << match.row << ':' << match.column << ' ' << path.path().string() << '\n'
									<< match.data << "\n\n";
			}
		}
	}
}
