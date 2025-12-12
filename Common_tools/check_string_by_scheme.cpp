#include "Common_tools.hpp"

bool check_string_by_scheme(string input, string scheme) {
	size_t phrase = input.find(scheme);
	if (phrase == string::npos) {
		return false;
	}

	return true;
}