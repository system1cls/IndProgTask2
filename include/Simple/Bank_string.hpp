#pragma once
#include <iostream>
#include <string>
using namespace std;

class Bank_string {
public:
	char str[100];

	Bank_string(const char* str) {
		this->_set_string(str);
	}

	void set_string(const char* str) {
		this->_set_string(str);
	}

private:
	void _set_string(const char* str);
};

typedef Bank_string BString;


istream& operator >> (istream& is, BString& bank_string);

ostream& operator << (ostream& os, BString& bstring);

bool operator == (BString& b1, BString& b2);