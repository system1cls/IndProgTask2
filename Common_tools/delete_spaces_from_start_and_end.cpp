#include "Common_tools.hpp"

string delete_spaces_from_start_and_end(string str) {
	size_t start = str.find_first_not_of(" \t");
	size_t end = str.find_last_not_of(' ');
	return str.substr(start, end + 1 - start);
}