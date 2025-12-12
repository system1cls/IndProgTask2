#pragma once
#include "Command.hpp"

class Client_activity_report_command : public Command {
private:
	ulong client_id;
	Date* start;
	Date* end;

public:
	Client_activity_report_command(Date* date, Time* time, ulong id, Date* start, Date* end);

	void run(bank_info& info) override;

	static bool check_parse(string str);
	static Command* parse(string str);
	bool set_worker(bank_info& info) override;

};

class Find_transaction_command : public Command {
private:
	MoneyRequestType mType;
	Money* money;

public:

	Find_transaction_command(Date* date, Time* time, MoneyRequestType type, Money* money);

	void run(bank_info& info) override;

	static bool check_parse(string str);
	static Command* parse(string str);
	bool set_worker(bank_info& info) override;
};

class Last_transaction_command : public Command {
public:

	Last_transaction_command(Date* date, Time* time);

	void run(bank_info& info) override;

	static bool check_parse(string str);
	static Command* parse(string str);
	bool set_worker(bank_info& info) override;
};

class Find_regulars_command : public Command {
private:
	Date* start;
	Date* end;

public:
	Find_regulars_command(Date* date, Time* time, Date* start, Date* end);

	void run(bank_info& info) override;

	static bool check_parse(string str);
	static Command* parse(string str);
	bool set_worker(bank_info& info) override;
};


class Find_repeated_command : public Command {
private:
	Date* first;
	Date* second;

public:

	Find_repeated_command(Date* date, Time* time, Date* first, Date* second);

	void run(bank_info& info) override;

	static bool check_parse(string str);
	static Command* parse(string str);
	bool set_worker(bank_info& info) override;
};
