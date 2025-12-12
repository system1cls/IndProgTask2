#include "Commands/Clients_approach.hpp"

Print_acc_info_command::Print_acc_info_command(Date* date, Time* time, string name, Client_type cl_type, ulong acc_ID) : Command(date, time) {
	this->name = name;
	this->cl_type = cl_type;
	this->acc_ID = acc_ID;
}

void Print_acc_info_command::run(bank_info& info) {
	if (info.clients_by_name_type.contains(name)) {
		Client* client = info.clients_by_name_type[name];
		string opearation = "print account info";
		info.analyzer.addNewActivity(client->get_id(), date, time, opearation);
		info.analyzer.add_new_client_enter(date, name);
	}

	if (info.is_open)
		print_acc_info(info, date, time, name, cl_type, acc_ID);
}

bool Print_acc_info_command::check_parse(string str) {
	return check_string_by_scheme(str, "Balance Inquiry");
}

Command* Print_acc_info_command::parse(string str) {
	string temp = str;
	istringstream iss(temp);

	int col = 0;

	Date* date = new Date();
	Time* time = new Time();
	string name_str;
	Client_type cl_type;
	ulong cnt_opers = 0;
	ulong acc_id;


	BString name("");
	BString type("");
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
			is >> acc_id;
			break;
		default:
			fprintf(stderr, "Error parsing Transfere_between_accs_of_one_client_command");
			exit(EXIT_FAILURE);
		}

		col++;
	}

	Command* command = new Print_acc_info_command(date, time, name_str, cl_type, acc_id);
	return command;
}

bool Print_acc_info_command::set_worker(bank_info& info) {
	Work_place* place;
	if (this->cl_type == VIP_Individual_Client || this->cl_type == VIP_Legal_Entity) {
		place = get_fastest_work_place(info, VIP_Client_Manager);

	}
	else {
		place = get_fastest_work_place(info, Client_Manager);
	}

	ulong time_to_be_done = place->add_new_client(this->time, 5);
	if (time_to_be_done >= 24 * 60) {
		time_to_be_done = 23 * 60 + 59;
	}
	this->time->set_time(time_to_be_done / 60, time_to_be_done % 60);
	return true;
}