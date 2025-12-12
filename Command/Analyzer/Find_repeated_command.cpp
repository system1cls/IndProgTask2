#include "Commands/Analyze_commands.hpp"

Find_repeated_command::Find_repeated_command(Date* date, Time* time, Date* first, Date* second) : Command(date, time) {
	this->first = first;
	this->second = second;
}

void Find_repeated_command::run(bank_info& info) {
	shared_ptr<Date> firsts = make_shared<Date>(first->get_date());
	shared_ptr<Date> seconds = make_shared<Date>(second->get_date());
	set<string> ans = info.analyzer.getRepeat(firsts, seconds);
	for (auto it = ans.begin(); it != ans.end(); it++) {
		cout << *it << "\n";
	}

}

bool Find_repeated_command::check_parse(string str) {
	return check_string_by_scheme(str, "Find Repeated Visits");
}


Command* Find_repeated_command::parse(string str) {
	string temp = str;
	istringstream iss(temp);

	int col = 0;

	Date* date = new Date();
	Time* time = new Time();
	Date* gfirst = new Date();
	Date* gsecond = new Date();
	Money* money = new Money(0);

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
			is >> *gfirst;
			break;
		case 3:
			is >> *gsecond;
			break;
		default:
			fprintf(stderr, "Error parsing Transfere_between_accs_of_one_client_command");
			exit(EXIT_FAILURE);
		}

		col++;
	}

	Command* command = new Find_repeated_command(date, time, gfirst, gsecond);
	return command;
}


bool Find_repeated_command::set_worker(bank_info& info) {
	return true;
}