#include "ichneutae/flag/parser.h"
#include "ichneutae/version.h"
#include <iostream>

const auto version = in::flag::boolean("version", false, "Print the program version");

int main(int argc, char* argv[]) {
	in::flag::parse(argc, argv);
	if (*version) {
		std::cout << in::flag::executable_name() << ' ' << in::version << '\n';
		std::exit(EXIT_SUCCESS);
	}
	std::cout << "works\n";
}
