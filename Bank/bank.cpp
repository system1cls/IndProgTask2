#include "bank.hpp"

Command* get_approach(string str) {
	string temp;
	getline(cin, temp);
	str += " # " + temp;

	if (Close_deposit_command::check_parse(str)) {
		Command* com = Close_deposit_command::parse(str);
		return com;
	}

	if (Create_credit_command::check_parse(str)) {
		return Create_credit_command::parse(str);
	}

	if (Create_debit_command::check_parse(str)) {
		return Create_debit_command::parse(str);
	}

	if (Create_deposit_command::check_parse(str)) {
		return Create_deposit_command::parse(str);
	}

	if (Exchange_currency_command::check_parse(str)) {
		return Exchange_currency_command::parse(str);
	}

	if (Print_acc_info_command::check_parse(str)) {
		return Print_acc_info_command::parse(str);
	}

	if (Top_up_command::check_parse(str)) {
		return Top_up_command::parse(str);
	}

	if (Withdraw_command::check_parse(str)) {
		return Withdraw_command::parse(str);
	}

	fprintf(stderr, "Uknown client approach");
	exit(EXIT_FAILURE);
}


Command* get_command(string str) {
	if (str.find("Personal Appeal") != string::npos) {
		return get_approach(str);
		
	}

	if (Add_money_from_another_bank_command::check_parse(str)) {
		return Add_money_from_another_bank_command::parse(str);
		
	}

	if (Transfere_between_accs_of_one_client_command::check_parse(str)) {
		return Transfere_between_accs_of_one_client_command::parse(str);
		
	}

	if (Transfer_between_accs_of_other_client_command::check_parse(str)) {
		return Transfer_between_accs_of_other_client_command::parse(str);
		
	}

	if (End_of_the_day_command::check_parse(str)) {
		return End_of_the_day_command::parse(str);
	
	}

	if (End_of_the_month_command::check_parse(str)) {
		return End_of_the_month_command::parse(str);
		
	}

	if (End_of_the_Quater_command::check_parse(str)) {
		return End_of_the_Quater_command::parse(str);
		
	}

	if (End_of_the_Semi_command::check_parse(str)) {
		return End_of_the_Semi_command::parse(str);
		
	}

	if (End_of_the_year_command::check_parse(str)) {
		return End_of_the_year_command::parse(str);
		
	}

	if (Start_of_the_day_command::check_parse(str)) {
		return Start_of_the_day_command::parse(str);
		
	}

	if (Client_activity_report_command::check_parse(str)) {
		return Client_activity_report_command::parse(str);
	}

	if (Find_regulars_command::check_parse(str)) {
		return Find_regulars_command::parse(str);
	}

	if (Find_repeated_command::check_parse(str)) {
		return Find_repeated_command::parse(str);
	}

	if (Find_transaction_command::check_parse(str)) {
		return Find_transaction_command::parse(str);
	}

	if (Last_transaction_command::check_parse(str)) {
		return Last_transaction_command::parse(str);
	}

	if (str != "") {
		fprintf(stderr, ("Uknown operation" + str).c_str());
		return nullptr;
	}

	return nullptr;
}

void set_commands(vector<Command*>& commands) {
	string str;

	while (getline(cin, str)) {
		Command* cmd = get_command(str);
		if (cmd != nullptr) {
			commands.push_back(cmd);
		}
	}
}



void work_by_cmd(bank_info& info, Command* com, vector<Command*>& working_commands) {

	if (info.is_open && com->date->get_date() != info.date.get_date()) {
		fprintf(stderr, "Wrong date");
		exit(EXIT_FAILURE);
	}

	ulong cnt_compl_commands = 0;
	for (auto command_to_be_done : working_commands) {
		if (*command_to_be_done < *com) {
			info.date.set_date(command_to_be_done->date->get_date());
			info.time.set_time(command_to_be_done->time->get_hours(), command_to_be_done->time->get_minutes());
			command_to_be_done->run(info);
			cnt_compl_commands++;
		}
	}
	if (cnt_compl_commands > 0) {
		auto it = working_commands.begin();
		for (int i = 0; i < cnt_compl_commands; i++) {
			Command* cmd = *it;
			delete cmd;
			it++;
		}

		working_commands.erase(working_commands.begin(), next(working_commands.begin(), cnt_compl_commands));
	}

	com->set_worker(info);
	working_commands.push_back(com);

}

void end_bank(bank_info& info, vector<Command*> working_commands) {
	for (auto command_to_be_done : working_commands) {

		info.date.set_date(command_to_be_done->date->get_date());
		info.time.set_time(command_to_be_done->time->get_hours(), command_to_be_done->time->get_minutes());
		command_to_be_done->run(info);
	}

	auto it = working_commands.begin();
	for (int i = 0; i < working_commands.size(); i++) {
		Command* cmd = *it;
		delete cmd;
		it++;
	}
}

void bank(ulong seed) {
	vector<Command*> start_commands;
	vector<Command*> working_commands;
	bank_info info = get_init_info(seed);
	set_commands(start_commands);

	for (auto it = start_commands.begin(); it != start_commands.end(); it++) {
		Command* com = *it;
		
		work_by_cmd(info, com, working_commands);
	}

	end_bank(info, working_commands);
}


void bank_by_cmd(int seed) {
	vector<Command*> working_commands;
	bank_info info = get_init_info(seed);
	string cmd_str;

	while(getline(cin, cmd_str)) {
		Command* com = get_command(cmd_str);

		work_by_cmd(info, com, working_commands);
	}


	end_bank(info, working_commands);
}