#pragma once
#include "Command.hpp"

class Print_acc_info_command : public Command {
private:
	string name;
	Client_type cl_type;
	ulong acc_ID;

public:

	Print_acc_info_command(Date* date, Time* time, string name, Client_type cl_type, ulong acc_ID);

	void run(bank_info& info) override;

	static bool check_parse(string str);
	static Command* parse(string str);
	bool set_worker(bank_info& info) override;
};

class Create_deposit_command : public Command {
private:
	string name;
	Client_type cl_type;
	Account_currency_type cur_type;
	Deposit_type debit_type;
	BString* period;
	Money* money;

public:

	Create_deposit_command(Date* date, Time* time, string name, Client_type cl_type, Account_currency_type cur_type, Deposit_type debit_type, BString* period, Money* money);

	void run(bank_info& info) override;

	static bool check_parse(string str);
	static Command* parse(string str);
	bool set_worker(bank_info& info) override;
};

class Close_deposit_command : public Command {
private:
	string name;
	Client_type cl_type;
	ulong acc_ID;

public:

	Close_deposit_command(Date* date, Time* time, string name, Client_type cl_type, ulong acc_ID);

	void run(bank_info& info) override;

	static bool check_parse(string str);
	static Command* parse(string str);
	bool set_worker(bank_info& info) override;
};


class Withdraw_command : public Command{
private:
	string name;
	Client_type cl_type;
	ulong acc_ID;
	Money* money;

public:

	Withdraw_command(Date* date, Time* time, string name, Client_type cl_type, ulong acc_ID, Money* money);

	void run(bank_info& info) override;

	static bool check_parse(string str);
	static Command* parse(string str);
	bool set_worker(bank_info& info) override;
};

class Top_up_command : public Command {
private:
	string name;
	Client_type cl_type;
	ulong acc_ID;
	Money* money;

public:
	Top_up_command(Date* date, Time* time, string name, Client_type cl_type, ulong acc_ID, Money* money);

	void run(bank_info& info) override;

	static bool check_parse(string str);
	static Command* parse(string str);
	bool set_worker(bank_info& info) override;
};

class Create_credit_command : public Command {
private:
	string name;
	Client_type cl_type;
	Account_currency_type cur_type;
	Credit_type credit_type;
	Money* money;

public:
	Create_credit_command(Date* date, Time* time, string name, Client_type cl_type, Account_currency_type cur_type, Credit_type credit_type, Money* money);

	void run(bank_info& info) override;

	static bool check_parse(string str);
	static Command* parse(string str);
	bool set_worker(bank_info& info) override;
};

class Create_debit_command : public Command {
private:
	string name;
	Client_type cl_type;
	Account_currency_type cur_type;

public:

	Create_debit_command(Date* date, Time* time, string name, Client_type cl_type, Account_currency_type cur_type);

	void run(bank_info& info) override;

	static bool check_parse(string str);
	static Command* parse(string str);
	bool set_worker(bank_info& info) override;
};

class Exchange_currency_command : public Command {
private:
	string name;
	Client_type cl_type;
	Account_currency_type from;
	Account_currency_type to;
	Money* money_to_transfer;

public:

	Exchange_currency_command(Date* date, Time* time, string name, Client_type cl_type, Account_currency_type from, Account_currency_type to, Money* money_to_transfer);

	void run(bank_info& info) override;

	static bool check_parse(string str);
	static Command* parse(string str);
	bool set_worker(bank_info& info) override;
};

