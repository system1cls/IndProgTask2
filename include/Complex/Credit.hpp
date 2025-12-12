#pragma once

#include "Simple/Simple_data_types.hpp"
#include "Enums/Enums.hpp"

class Credit {
private:
	ulong ID;
	double interest_rate;
	Money* money_was_lended;
	Money* money_payed;
	BString* type;

public:

	Credit(ulong ID, double intersert_rate, Money* money_was_lended, BString* type);

	ulong get_ID() const;

	void set_ID(ulong ID) {
		this->ID = ID;
	}

	double get_interest_rate() const;

	double get_money_was_lended() const;

	double get_money_payed() const;

	void add_money(double num);

	void reduce_credit(double money_to_reduce);

	BString* get_type() const;

	~Credit();
};
