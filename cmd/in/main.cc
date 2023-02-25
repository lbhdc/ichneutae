#include "ichneutae/flag/parser.h"
#include <iostream>

constexpr auto in_version = "0.0.0";

const auto version = in::flag::boolean("version", false, "Print the program version");

int main(int argc, char* argv[]) {
	in::flag::parse(argc, argv);
	if (*version) {
		std::cout << in::flag::executable_name() << ' ' << in_version << '\n';
		std::exit(EXIT_SUCCESS);
	}
	std::cout << "works\n";
}
