#include "Complex/Work_place.hpp"

Work_place::Work_place(BString* type, ulong cnt_places) {
	this->type = type;
	this->cnt_places = cnt_places;
	for (int i = 0; i < cnt_places; i++) {
		this->cnt_clients_in_day.push_back(0);
		this->cnt_clients_in_year.push_back(0);
		this->time_to_be_freed.push_back(0);
	}
}

BString* Work_place::get_type() const {
	return this->type;
}

ulong Work_place::get_cnt_places() const {
	return this->cnt_places;
}

ulong Work_place::min_time_when_be_ready() {
	ulong min_time = this->time_to_be_freed[0];
	for (int it = 0; it < this->cnt_places; it++) {
		if (this->time_to_be_freed[it] < min_time) {
			min_time = this->time_to_be_freed[it];
		}
	}

	return min_time;
}

ulong Work_place::add_new_client(Time* start_time, ulong time) {
	ulong min_time = this->time_to_be_freed[0];
	ulong it_of_min_time = 0;
	for (int it = 0; it < this->cnt_places; it++) {
		if (this->time_to_be_freed[it] < min_time) {
			min_time = this->time_to_be_freed[it];
			it_of_min_time = it;
		}
	}

	this->time_to_be_freed[it_of_min_time] += start_time->get_hours()*60 + start_time->get_minutes() + time;
	this->cnt_clients_in_day[it_of_min_time]++;
	this->cnt_clients_in_year[it_of_min_time]++;

	return this->time_to_be_freed[it_of_min_time];
}

void Work_place::end_day(Date* date) {
	for (ulong i = 0; i < this->cnt_places; i++) {
		this->time_to_be_freed[i] = 0;
		printf("%llu # %s # %llu # %llu\n", date->get_date(), this->type->str, i + 1, this->cnt_clients_in_day[i]);
		this->cnt_clients_in_day[i] = 0;
	}
}

void Work_place::end_year(Date* date) {
	for (ulong i = 0; i < this->cnt_places; i++) {
		printf("%llu # %s # %llu # %llu\n", date->get_date(), this->type->str, i + 1, this->cnt_clients_in_year[i]);
		this->cnt_clients_in_year[i] = 0;
	}
}


Work_place:: ~Work_place() {
	if (this->type != nullptr) delete this->type;
}