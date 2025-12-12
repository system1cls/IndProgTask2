#pragma once

#include <iostream>
using namespace std;

typedef unsigned long long int ulong;

class Time {
private:
	ulong hours;
	ulong minutes;

public:
	Time();

	Time(ulong hours, ulong minutes);

	Time(Time& time);

	ulong get_hours() const;

	ulong get_minutes() const;

	void set_time(ulong hours, ulong minutes);

	void set_hours(ulong hours);

	void set_minutes(ulong minutes);

	void add_minutes(ulong minutes_to_add);
};

ostream& operator << (ostream& os, const Time& time);

istream& operator >> (istream& is, Time& time);