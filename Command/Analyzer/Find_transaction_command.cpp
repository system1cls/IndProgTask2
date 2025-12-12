#include "Commands/Analyze_commands.hpp"

Find_transaction_command::Find_transaction_command(Date* date, Time* time, MoneyRequestType type, Money* money) : Command(date, time) {
	this->mType = mType;
	this->money = money;
}

void Find_transaction_command::run(bank_info& info) {
	shared_ptr<Money> mmoney = make_shared<Money>(this->money->get_money());
	vector<shared_ptr<Transaction>> vec = info.analyzer.getTransactionWithMoneyType(date->get_date(), mType, mmoney);
	for (auto it = vec.begin(); it != vec.end(); it++) {
		cout << it->get()->time->get_hours() << ":" << it->get()->time->get_minutes() << " # " << it->get()->id << " # " << it->get()->money->get_ent_dec().first << "." << it->get()->money->get_ent_dec().second << "\n";
	}
}

bool Find_transaction_command::check_parse(string str) {
	return check_string_by_scheme(str, "Find transaction");
}

MoneyRequestType getTypeFromStr(string& str) {
	if (str.compare("GREATER") == 0) {
		return MoneyRequestType::More;
	}
	if (str.compare("LESS") == 0) {
		return MoneyRequestType::Less;
	}
	if (str.compare("EQUAL") == 0) {
		return Equal;
	}
	
	return Less;
}

Command* Find_transaction_command::parse(string str) {
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
		case 2:
			is >> typeStr;
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

	Command* command = new Find_transaction_command(date, time, getTypeFromStr(typeStr), money);
	return command;
};


bool Find_transaction_command::set_worker(bank_info& info) {
	return true;
};