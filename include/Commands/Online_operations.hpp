#pragma once
#include "Command.hpp"

class Transfere_between_accs_of_one_client_command : public Command {
	ulong acc1_id;
	ulong acc2_id;
	Money* money;

public:

	Transfere_between_accs_of_one_client_command(Date* date, Time* time, ulong acc1_id, ulong acc2_id, Money* money);

	void run(bank_info& info) override;

	static bool check_parse(string str);
	static Command* parse(string str);
};

class Transfer_between_accs_of_other_client_command : public Command {
	ulong acc1_id;
	ulong acc2_id;
	Money* money;

public:

	Transfer_between_accs_of_other_client_command(Date* date, Time* time, ulong acc1_id, ulong acc2_id, Money* money);

	void run(bank_info& info) override;

	static bool check_parse(string str);
	static Command* parse(string str);
};

class Add_money_from_another_bank_command : public Command {
	ulong acc_id;
	Money* money;

public:

	Add_money_from_another_bank_command(Date* date, Time* time, ulong acc_id, Money* money);

	void run(bank_info& info) override;

	static bool check_parse(string str);
	static Command* parse(string str);
};
