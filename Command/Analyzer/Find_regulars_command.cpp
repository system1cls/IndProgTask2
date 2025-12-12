#include "Commands/Analyze_commands.hpp"

Find_regulars_command::Find_regulars_command(Date* date, Time* time, Date* start, Date* end) : Command(date, time){
	this->start = start;
	this->end = end;
}

void Find_regulars_command::run(bank_info& info) {
	shared_ptr<Date> starts = make_shared<Date>(start->get_date());
	shared_ptr<Date> ends = make_shared<Date>(end->get_date());
	map<string, ulong> ans = info.analyzer.getTop(starts, ends);

	for (auto it = ans.begin(); it != ans.end(); it++) {
		cout << it->first << " # " << it->second << "\n";
	}
}

bool Find_regulars_command::check_parse(string str) {
	return check_string_by_scheme(str, "Find Regulars");
}

Command* Find_regulars_command::parse(string str) {
	string temp = str;
	istringstream iss(temp);

	int col = 0;

	Date* date = new Date();
	Time* time = new Time();
	Date* gstart = new Date();
	Date* gend = new Date();
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
			is >> *gstart;
			break;
		case 3:
			is >> *gend;
			break;
		default:
			fprintf(stderr, "Error parsing Transfere_between_accs_of_one_client_command");
			exit(EXIT_FAILURE);
		}

		col++;
	}

	Command* command = new Find_regulars_command(date, time, gstart, gend);
	return command;
}

bool Find_regulars_command::set_worker(bank_info& info) {
	return true;
}