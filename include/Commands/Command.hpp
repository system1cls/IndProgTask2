#pragma once

#include "Time_events/Time_events.hpp"
#include "Clients_operations/Client_operations.hpp"
#include "Online_operations/Online_operations.hpp"
#include <string>
#include <algorithm>
#include <sstream>
#include <iostream>

class Command {
public:
	Date* date;
	Time* time;


	Command(Date* date, Time* time);

	virtual void run(bank_info& info);
	virtual bool set_worker(bank_info& info);
	static bool check_parse(string str);
	static Command parse(string str);
};

bool operator < (const Command& command1, const Command& command2);

Work_place* get_fastest_work_place(bank_info& info, Work_place_type type);