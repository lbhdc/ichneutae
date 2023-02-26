#include "ichneutae/flag/parser.h"
#include "ichneutae/os/path.h"
#include "ichneutae/text/contains.h"
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <vector>

namespace in::flag {
// built-in flags are executed in the parse function directly after parsing
const auto help_flag = boolean("help", false, "Prints the program usage");

// flag_set holds registered flags to make them available to the parser
class flag_set {
	// instance_ptr holds the singleton instance of the flag set and is created and accessed through
	// the instance member variable.
	inline static flag_set* instance_ptr;

	// flag_set isn't constructable outside of the singleton
	flag_set() = default;
	flag_set(const flag_set&) = default;
	flag_set(flag_set&&) = default;

public:
	// argv holds positional arguments that were not parsed as flags or flag values
	std::vector<std::string> argv{};
	// executable_name is the program name extracted from argv
	std::string_view executable_name{};
	// setter_no_arg is a map of flag names and a function that initializes its state with the
	// provided function
	std::map<std::string_view, std::function<void()>> setter_no_arg{};
	// setter_single_arg is a map of flag names and a function that initializes its state from the
	// parsed value
	std::map<std::string_view, std::function<void(std::string)>> setter_single_arg{};
	// setter_usage is a map of flag names and usage text
	std::map<std::string_view, std::string> setter_usage{};

	// flag set is a singleton and can't be moved or copied
	flag_set& operator=(const flag_set&) = delete;
	flag_set& operator=(flag_set&&) = delete;

	// instance returns a pointer to the flags singleton
	static flag_set* instance() noexcept {
		if (instance_ptr == nullptr) {
			instance_ptr = new flag_set{};
		}
		return instance_ptr;
	}
};

// valid_flag_name checks that flag names don't contain characters needed to parse the flags
constexpr void valid_flag_name(std::string_view name) noexcept {
	if (name.starts_with('-') or text::contains(name, '=')) {
		std::cerr << "flag: invalid name: cannot start with '-' or contain '=' got '" << name << '\'';
		std::exit(EXIT_FAILURE);
	}
}

std::span<std::string> argv() noexcept {
	return flag_set::instance()->argv;
}

size_t nargs() noexcept {
	return flag_set::instance()->argv.size();
}

std::string_view executable_name() noexcept {
	return flag_set::instance()->executable_name;
}

void parse(int argc, char** argv) noexcept {
	auto fs = flag_set::instance();
	fs->executable_name = os::file_name(*argv);
	// no-op no args given
	if (argc == 1) {
		return;
	}
	auto args = std::vector<std::string>(argv + 1, argv + argc);
	std::string flag{};
	std::string value{};
	// loop over argv to parse our flags and their values
	// a cstyle loop with an iterator is used here to be able to shift forward to find values.
	for (auto arg{args.begin()}; arg < args.end(); ++arg) {
		// reset the state of the loop variables
		flag.clear();
		value.clear();
		// check if an arg starts with -- or - and set it to `flag` if it does
		if (arg->starts_with("--")) {
			flag = arg->substr(2, arg->size());
		} else if (arg->starts_with('-')) {
			flag = arg->substr(1, arg->size());
		}
		// if no flag was parsed, then arg isn't going to be used as a flag value and can be
		// accumulated in argv
		if (flag.empty()) {
			fs->argv.push_back(std::move(*arg));
			continue;
		}
		// if the flag is in the no arg setters list run setup and move on
		if (fs->setter_no_arg.count(flag)) {
			fs->setter_no_arg[flag]();
			continue;
		}
		// if the flag and value are separated by an `=` parse each value. Otherwise look at the next
		// value in argv and use that
		if (auto pivot = flag.find('='); pivot != std::string::npos) {
			value = flag.substr(pivot + 1, flag.size());
			flag = flag.substr(0, pivot);
		} else {
			++arg; // shift to the next value in argv
			if (arg == args.end()) {
				// went too far, bad parse
				break;
			}
			value = *arg;
		}
		// if the flag is in the single arg setters run setup
		if (fs->setter_single_arg.count(flag)) {
			fs->setter_single_arg[flag](std::move(value));
		}
	}
	// handle built in flags
	if (*help_flag) {
		std::cout << usage();
		std::exit(EXIT_SUCCESS);
	}
}

std::string usage() noexcept {
	const auto fs = flag_set::instance();
	// the flag_set captures the name as provided. We just want the file name
	size_t exec_begin{0};
	if (text::contains(fs->executable_name, '/')) {
		exec_begin = fs->executable_name.find_last_of('/') + 1;
	}
	auto indent = std::string(4, ' ');
	// add usage block
	auto usg =
		"USAGE\n" + indent + fs->executable_name.substr(exec_begin).begin() + " [flags] [args...]\n";
	// add flags block if flags have been defined
	if (not fs->setter_usage.empty()) {
		usg += "\nFLAGS\n";
		// find the widest key so the usage offtext can be aligned for all flags
		size_t max_key_width{0};
		for (auto& [flag_name, _] : fs->setter_usage) {
			max_key_width = std::max(max_key_width, flag_name.size());
		}
		// set the whitespace so the longest flag doesn't run into the usage text
		auto min_space_between_flag_and_usage{4};
		// add the flags to the usage text
		for (auto& [flag_name, usage_text] : fs->setter_usage) {
			auto space_between_flag_and_usage =
				std::string((max_key_width - flag_name.size()) + min_space_between_flag_and_usage, ' ');
			// {indent}-{flag_name}{whitespace}{usage_text}
			usg += indent + '-';
			usg += flag_name;
			usg += space_between_flag_and_usage;
			usg += usage_text + '\n';
		}
	}
	// add an empty line to the end of usage
	usg += "\n";
	return usg;
}

std::string* string(std::string_view name, std::string default_val, std::string usage) noexcept {
	valid_flag_name(name);
	auto out = new std::string{std::move(default_val)};
	flag_set::instance()->setter_single_arg[name] = [=](std::string&& in) { *out = std::move(in); };
	flag_set::instance()->setter_usage[name] = std::move(usage);
	return out;
}

bool* boolean(std::string_view name, bool default_val, std::string usage) noexcept {
	valid_flag_name(name);
	auto out = new bool{default_val};
	flag_set::instance()->setter_no_arg[name] = [=]() { *out = true; };
	flag_set::instance()->setter_usage[name] = std::move(usage);
	return out;
}

int32_t* int32(std::string_view name, int32_t default_val, std::string usage) noexcept {
	valid_flag_name(name);
	auto out = new int32_t{default_val};
	flag_set::instance()->setter_single_arg[name] = [=](std::string&& in) {
		std::istringstream(in) >> *out;
	};
	flag_set::instance()->setter_usage[name] = std::move(usage);
	return out;
}

int64_t* int64(std::string_view name, int64_t default_val, std::string usage) noexcept {
	valid_flag_name(name);
	auto out = new int64_t{default_val};
	flag_set::instance()->setter_single_arg[name] = [=](std::string&& in) {
		std::istringstream(in) >> *out;
	};
	flag_set::instance()->setter_usage[name] = std::move(usage);
	return out;
}
} // namespace in::flag
