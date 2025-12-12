#include "Commands/Clients_approach.hpp"

Create_deposit_command::Create_deposit_command(Date* date, Time* time, string name, Client_type cl_type, Account_currency_type cur_type, Deposit_type debit_type, BString* period, Money* money)  : Command(date, time) {
	this->name = name;
	this->cl_type = cl_type;
	this->cur_type = cur_type;
	this->debit_type = debit_type;
	this->money = money;
	this->period = period;
}

void Create_deposit_command::run(bank_info& info) {
	if (info.clients_by_name_type.contains(name)) {
		Client* client = info.clients_by_name_type[name];
		string opearation = "create deposit";
		info.analyzer.addNewActivity(client->get_id(), date, time, opearation);
		info.analyzer.add_new_client_enter(date, name);
	}

	if (info.is_open)
		create_deposit(info, date, time, name, cl_type, cur_type, debit_type, period, money);
}

bool Create_deposit_command::check_parse(string str) {
	return check_string_by_scheme(str, "Make Deposit");
}

Command* Create_deposit_command::parse(string str) {
	string temp = str;
	istringstream iss(temp);

	int col = 0;

	Date* date = new Date();
	Time* time = new Time();
	string name_str;
	Client_type cl_type;
	ulong cnt_opers = 0;
	Account_currency_type cur_t;
	Deposit_type deposit_t;
	BString* period = new BString("");
	Money* money = new Money(0);
	


	BString name("");
	BString type("");
	BString cur_type("");
	BString deposit_type("");
	string temp_data;


	while (getline(iss, temp, '#')) {
		temp = delete_spaces_from_start_and_end(temp);
		if (temp == "") continue;

		istringstream is(temp);

		switch (col) {
		case 0:
			is >> *date;
			break;
		case 1:
			is >> *time;
			break;
		case 2:
			break;
		case 3:
			is >> name;
			name_str = string(name.str);
			break;
		case 4:
			is >> type;
			temp_data = string(type.str);
			replace(temp_data.begin(), temp_data.end(), ' ', '_');
			if (temp_data.compare("Individual") == 0 || temp_data.compare("Legal_Entity") == 0) {
				strcpy(type.str, temp_data.c_str());
				cl_type = get_client_type_enum(&type);
				break;
			}

			fprintf(stderr, "Client error. Uknown type");
			exit(EXIT_FAILURE);

		case 5:
			is >> cnt_opers;
			if (cnt_opers != 1) {
				fprintf(stderr, "More than one operation");
				exit(EXIT_FAILURE);
			}
			break;
		case 6:
			break;
		case 7:
			is >> cur_type;
			temp_data = string(cur_type.str);
			strcpy(cur_type.str, temp_data.c_str());
			cur_t = get_account_currency_type_enum(&cur_type);
			break;
		case 8:
			is >> deposit_type;
			temp_data = string(deposit_type.str);
			strcpy(deposit_type.str, temp_data.c_str());
			deposit_t = get_debit_type_enum(&deposit_type);
			break;
		case 9:
			is >> *period;
			temp_data = string(period->str);
			strcpy(period->str, temp_data.c_str());
			break;
		case 10:
			is >> *money;
			break;
		default:
			fprintf(stderr, "Error parsing Transfere_between_accs_of_one_client_command");
			exit(EXIT_FAILURE);
		}

		col++;
	}

	Command* command = new Create_deposit_command(date, time, name_str, cl_type, cur_t, deposit_t, period, money);
	return command;
}

bool Create_deposit_command::set_worker(bank_info& info) {
	Work_place* place;
	if (this->cl_type == VIP_Individual_Client || this->cl_type == VIP_Legal_Entity) {
		place = get_fastest_work_place(info, VIP_Client_Manager);

	}
	else {
		if (this->cl_type == Individual_Client) place = get_fastest_work_place(info, Client_Manager);
		else {
			fprintf(stderr, "Client error create deposit for Legal Entity");
			return false;
		}
	}

	ulong time_to_be_done = place->add_new_client(this->time, 20);
	if (time_to_be_done >= 24 * 60) {
		time_to_be_done = 23 * 60 + 59;
	}
	this->time->set_time(time_to_be_done / 60, time_to_be_done % 60);
	return true;
}