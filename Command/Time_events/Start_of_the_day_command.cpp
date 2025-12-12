#include "Commands/Time_events.hpp"

Start_of_the_day_command::Start_of_the_day_command(Date* date, Time* time) : Command(date, time) {}

void Start_of_the_day_command::run(bank_info& info) {
	info.is_open = true;
}

bool Start_of_the_day_command::check_parse(string str) {
	return check_string_by_scheme(str, "Start of Bank Day");
}

Command* Start_of_the_day_command::parse(string str) {
	string temp = str;
	istringstream iss(temp);

	int col = 0;

	Date* date = new Date();
	Time* time = new Time();

	while (getline(iss, temp, '#')) {
		temp = delete_spaces_from_start_and_end(temp);
		istringstream is(temp);
		if (isalpha(is.peek())) {
			continue;
		}

		switch (col) {
		case 0:
			is >> *date;
			break;
		case 1:
			is >> *time;
			break;
		case 2:
			break;
		default:
			fprintf(stderr, "Error parsing Start_of_the_day_command");
			exit(EXIT_FAILURE);
		}

		col++;
	}

	Command* command = new Start_of_the_day_command(date, time);
	return command;
}
