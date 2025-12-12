#include "Commands/Analyze_commands.hpp"

Last_transaction_command::Last_transaction_command(Date* date, Time* time) : Command(date, time) {}

void Last_transaction_command::run(bank_info& info) {
	vector<shared_ptr<Transaction>> vec = info.analyzer.getLast();
	for (auto it = vec.begin(); it != vec.end(); it++) {
		cout << it->get()->date->get_date() << " # " << it->get()->time->get_hours() << ":" << it->get()->time->get_minutes() << " # " << it->get()->id << '\n';
	}
}

bool Last_transaction_command::check_parse(string str) {
	return check_string_by_scheme(str, "Last Transactions");
}

Command* Last_transaction_command::parse(string str) {
	string temp = str;
	istringstream iss(temp);

	int col = 0;

	Date* date = new Date();
	Time* time = new Time();
	string typeStr;
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
		default:
			fprintf(stderr, "Error parsing Transfere_between_accs_of_one_client_command");
			exit(EXIT_FAILURE);
		}

		col++;
	}

	Command* command = new Last_transaction_command(date, time);
	return command;
}


bool Last_transaction_command::set_worker(bank_info& info) {
	return true;
}