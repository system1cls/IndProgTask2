#include "Commands/Online_operations.hpp"

Transfere_between_accs_of_one_client_command::Transfere_between_accs_of_one_client_command(Date* date, Time* time, ulong acc1_id, ulong acc2_id, Money* money) : Command(date, time) {
	this->acc1_id = acc1_id;
	this->acc2_id = acc2_id;
	this->money = money;
}


void Transfere_between_accs_of_one_client_command::run(bank_info& info) {
	transfer_between_accs_of_one_client(info, date, time, acc1_id, acc2_id, money);
}

bool Transfere_between_accs_of_one_client_command::check_parse(string str) {
	return check_string_by_scheme(str, "Online Transfer Between My Accounts");
}

Command* Transfere_between_accs_of_one_client_command::parse(string str) {
	string temp = str;
	istringstream iss(temp);

	int col = 0;

	Date* date = new Date();
	Time* time = new Time();
	ulong acc1_id, acc2_id;
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
			is >> acc1_id;
			break;
		case 3:
			is >> acc2_id;
			break;
		case 4:
			is >> *money;
			break;
		default:
			fprintf(stderr, "Error parsing Transfere_between_accs_of_one_client_command");
			exit(EXIT_FAILURE);
		}

		col++;
	}

	Command* command = new Transfere_between_accs_of_one_client_command(date, time, acc1_id, acc2_id, money);
	return command;
}