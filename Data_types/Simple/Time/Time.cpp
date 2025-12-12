#include "Simple/Time.hpp"

Time::Time() {
	this->hours = -1;
	this->minutes = -1;
}

Time::Time(ulong hours, ulong minutes) {
	this->hours = hours;
	this->minutes = minutes;
}

Time::Time(Time& time) {
	this->hours = time.hours;
	this->minutes = time.minutes;
}

ulong Time::get_hours() const {
	return this->hours;
}

ulong Time::get_minutes() const {
	return this->minutes;
}



void Time::set_time(ulong hours, ulong minutes) {
	this->set_hours(hours);
	this->set_minutes(minutes);
}

void Time::set_hours(ulong hours) {
	this->hours = hours;
}

void Time::set_minutes(ulong minutes) {
	this->minutes = minutes;
}

void Time::add_minutes(ulong minutes_to_add) {
	this->minutes += minutes_to_add;
	this->hours += minutes / 60;
	this->hours %= 24;
	this->minutes %= 60;
}

ostream& operator << (ostream& os, const Time& time) {
	return os << time.get_hours() << ":" << time.get_minutes();
}

istream& operator >> (istream& is, Time& time) {
	ulong h, m;
	char colon;
	is >> h >> colon >> m;
	if (colon != ':') {
		fprintf(stderr, "Time cin error");
		exit(EXIT_FAILURE);
	}
	time.set_time(h, m);

	return is;
}
