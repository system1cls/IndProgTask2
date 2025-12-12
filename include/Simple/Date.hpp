#pragma once

#include <iostream>
using namespace std;

typedef unsigned long long int ulong;

class Date {
private:
	ulong day_from_start;

public:
	Date();

	Date(ulong date);

	ulong get_date() const;

	void set_date(ulong date);

	void inc();
};



ostream& operator << (ostream& os, const Date& date);

istream& operator >> (istream& is, Date& date);