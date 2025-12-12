#include "Commands/Command.hpp"

Command::Command(Date* date, Time* time) {
	this->date = date;
	this->time = time;
}

bool Command::set_worker(bank_info& info) { return true; };
void Command::run(bank_info& info) {};

bool operator < (const Command& command1, const Command& command2) {
	if (command1.date->get_date() != command2.date->get_date()) {
		return command1.date->get_date() < command2.date->get_date();
	}

	if (command1.time->get_hours() != command2.time->get_hours()) {
		return command1.time->get_hours() < command2.time->get_hours();
	}

	if (command1.time->get_minutes() != command2.time->get_minutes()) {
		return command1.time->get_minutes() < command2.time->get_minutes();
	}

	return false;
}

Work_place* get_fastest_work_place(bank_info& info, Work_place_type type) {
	auto chosen_place = info.work_places.lower_bound(type);
	auto end = info.work_places.upper_bound(type);
	ulong max_time = 24 * 60 + 1000;
	for (auto it = chosen_place; it != end; it++) {
		Work_place* place = it->second;
		ulong time_here = place->min_time_when_be_ready();
		if (time_here < max_time) {
			max_time = time_here;
			chosen_place = it;
		}
	}

	return chosen_place->second;
}