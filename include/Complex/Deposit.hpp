#pragma once

#include "Simple/Simple_data_types.hpp"
#include "Enums/Enums.hpp"

class Deposit {
private:
	ulong ID;
	double interest_rate;
	BString* type;
	Date* date_of_creation;
	ulong days_of_duration;


public:

	Deposit(ulong ID, double interest_rate, BString* type, Date* date_of_creation);

	Deposit(ulong ID, double interest_rate, BString* type, Date* date_of_creation, ulong days_of_duration);

	ulong get_ID();

	void set_ID(ulong ID);

	double get_interest_rate();

	BString* get_type();

	Date* get_date_of_creation();

	ulong get_days_of_duration();

	void add_days(ulong days);

	void dec_days();

	~Deposit();
};
