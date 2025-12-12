#include "Commands/Time_events.hpp"

End_of_the_month_command::End_of_the_month_command(Date* date, Time* time) : Command(date, time) {}

void End_of_the_month_command::run(bank_info& info) {
	Time_events::end_of_the_month(date, time, info);
}

bool End_of_the_month_command::check_parse(string str) {
	return check_string_by_scheme(str, "End of Bank Month");
}

Command* End_of_the_month_command::parse(string str) {
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
		default:
			fprintf(stderr, "Error parsing Transfere_between_accs_of_one_client_command");
			exit(EXIT_FAILURE);
		}

		col++;
	}

	Command* command = new End_of_the_month_command(date, time);
	return command;
}
