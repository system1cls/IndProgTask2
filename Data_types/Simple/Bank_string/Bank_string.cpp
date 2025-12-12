#include "Simple/Bank_string.hpp"

void Bank_string::_set_string(const char* str) {
	if (strlen(str) > 99) {
		//TODO:error;
		exit(EXIT_FAILURE);
	}

	strcpy(this->str, str);
}

istream& operator >> (istream& is, BString& bank_string) {
	string str = "";

	while (is.peek() != '#' && !is.eof()) {
		str += is.get();
	}

	if (sscanf(str.c_str(), R"(%99[a-zA-Z0-9/_ ])", bank_string.str) < 0) {
		//TODO: error;
		exit(EXIT_FAILURE);
	}
	return is;
}

ostream& operator << (ostream& os, BString& bstring) {
	os << bstring.str;
	return os;
}

bool operator == (BString& b1, BString& b2) {
	if (std::strcmp(b1.str, b2.str) == 0) return true;

	return false;
}
