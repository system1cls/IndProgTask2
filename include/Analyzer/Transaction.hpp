#pragma once
#include "Simple/Date.hpp"
#include "Simple/Time.hpp"
#include "Simple/Money.hpp"

class Transaction {
public:
	unique_ptr<Date> date;
	unique_ptr<Time> time;
	unique_ptr<Money> money;
	ulong accFrom;
	ulong accTo;
	ulong id = -1;
	

	Transaction(Date* date, Time* time, Money* money, ulong from, ulong to);
};