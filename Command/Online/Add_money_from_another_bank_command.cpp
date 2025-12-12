#include "Commands/Online_operations.hpp"

Add_money_from_another_bank_command::Add_money_from_another_bank_command(Date* date, Time* time, ulong acc_id, Money* money) : Command(date, time) {
	this->acc_id = acc_id;
	this->money = money;
}

void Add_money_from_another_bank_command::run(bank_info& info) {
	add_money_from_another_bank(info, date, time, acc_id, money);
}

bool Add_money_from_another_bank_command::check_parse(string str) {
	return check_string_by_scheme(str, "Online Inbound Transfer");
}

Command* Add_money_from_another_bank_command::parse(string str) {
	string temp = str;
	istringstream iss(temp);

	int col = 0;

	Date* date = new Date();
	Time* time = new Time();
	ulong acc_id;
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
			is >> acc_id;
			break;
		case 3:
			is >> *money;
			break;
		default:
			fprintf(stderr, "Error parsing Transfere_between_accs_of_one_client_command");
			exit(EXIT_FAILURE);
		}

		col++;
	}

	Command* command = new Add_money_from_another_bank_command(date, time, acc_id, money);
	return command;
}
