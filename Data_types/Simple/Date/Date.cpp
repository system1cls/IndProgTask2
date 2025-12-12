#include "Simple/Date.hpp"

#include <iostream>
using namespace std;

Date::Date() {
	this->set_date(0);
}

Date::Date(ulong date) {
	this->day_from_start = date;
}

ulong Date::get_date() const {
	return this->day_from_start;
}

void Date::set_date(ulong date) {
	this->day_from_start = date;
}

void Date::inc() {
	this->day_from_start++;
}


ostream& operator << (ostream& os, const Date& date) {
	return os << date.get_date();
}

istream& operator >> (istream& is, Date& date) {
	ulong days;
	is >> days;
	date.set_date(days);
	return is;
}