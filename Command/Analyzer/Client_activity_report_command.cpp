#include "Commands/Analyze_commands.hpp"

Client_activity_report_command::Client_activity_report_command(Date* date, Time* time, ulong id, Date* start, Date* end) : Command(date, time) {
	
	this->client_id = id;
	this->start = start;
	this->end = end;
}

void Client_activity_report_command::run(bank_info& info) {
	map<ulong, vector<shared_ptr<Activity>>> ans = info.analyzer.getOperation(client_id, start, end);
	for (auto map_it = ans.begin(); map_it != ans.end(); map_it++) {
		cout << map_it->first << " [";
		for (auto vec_it = map_it->second.begin(); vec_it != map_it->second.end(); vec_it++) {
			cout << "{" << vec_it->get()->time->get_hours() << ":" << vec_it->get()->time->get_minutes() << ", " << vec_it->get()->operation << "}";
		}
		cout << ']\n';
	}
}

bool Client_activity_report_command::check_parse(string str) {
	return check_string_by_scheme(str, "Client Activity Report");
}
Command* Client_activity_report_command::parse(string str) {
	string temp = str;
	istringstream iss(temp);

	int col = 0;

	Date* date = new Date();
	Time* time = new Time();
	ulong client_id;
	Date* start = new Date();
	Date* end = new Date();

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
			is >> client_id;
			break;
		case 4:
			is >> *start;
			break;
		case 5:
			is >> *end;
			break;
		default:
			fprintf(stderr, "Error parsing Transfere_between_accs_of_one_client_command");
			exit(EXIT_FAILURE);
		}

		col++;
	}

	Command* command = new Client_activity_report_command(date, time, client_id, start, end);
	return command;
}

bool Client_activity_report_command::set_worker(bank_info& info) {
	return true;
}

