#pragma once
#include "Command.hpp"


class Start_of_the_day_command : public Command {
public:

	Start_of_the_day_command(Date* date, Time* time);

	void run(bank_info& info) override;

	static bool check_parse(string str);
	static Command* parse(string str);

};


class End_of_the_day_command : public Command {
public:
	End_of_the_day_command(Date* date, Time* time);

	void run(bank_info& info) override;

	static bool check_parse(string str);
	static Command* parse(string str);
};

class End_of_the_month_command : public Command {
public:
	End_of_the_month_command(Date* date, Time* time);

	void run(bank_info& info) override;

	static bool check_parse(string str);
	static Command* parse(string str);
};

class End_of_the_Quater_command : public Command {
public:
	End_of_the_Quater_command(Date* date, Time* time);

	void run(bank_info& info) override;

	static bool check_parse(string str);
	static Command* parse(string str);
};

class End_of_the_Semi_command : public Command {
public:

	End_of_the_Semi_command(Date* date, Time* time);

	void run(bank_info& info) override;

	static bool check_parse(string str);
	static Command* parse(string str);
};

class End_of_the_year_command : public Command {
public:

	End_of_the_year_command(Date* date, Time* time);

	void run(bank_info& info) override;

	static bool check_parse(string str);
	static Command* parse(string str);
};