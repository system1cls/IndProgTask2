#pragma once

#include <utility>
#include <iostream>
using namespace std;
typedef unsigned long long int ulong;


class Money {
private:
	double money;

public:

	double round();

	Money(double money);

	void set_money(ulong entire, ulong dec);

	void set_money(double money);

	double get_money() const;

	pair<ulong, ulong> get_ent_dec() const;

	void add_money(double money_to_add);

	bool try_reduce(double money_to_reduce);
};

ostream& operator << (ostream& os, const Money& money);

istream& operator >> (istream& is, Money& money);