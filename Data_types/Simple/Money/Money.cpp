#include "Simple/Money.hpp"

double Money::round() {
	if (money == 0) {
		return 0;
	}
	int sign = 1;
	if (money < 0) {
		sign = -1;
		money *= -1;
	}

	double entire = floor(money);
	double dec = money - entire;

	if (dec < 0.5) {
		return entire * sign;
	}

	if (dec > 0.5) {
		return (entire + 1) * sign;
	}

	if ((ulong)entire % 2) {
		return entire * sign;
	}

	return (entire + 1) * sign;
}

Money::Money(double money) {
	this->money = money;
}

void Money::set_money(ulong entire, ulong dec) {
	if (dec > 999) {
		//TODO: error;
		exit(EXIT_FAILURE);
	}

	money = entire + ((double)dec / 1000);
}

void Money::set_money(double money) {
	this->money = money;
}

double Money::get_money() const {
	return money;
}

ostream& operator << (ostream& os, const Money& money) {
	os << money.get_money();
	return os;
}

istream& operator >> (istream& is, Money& money) {
	ulong en, dec;
	if (fscanf_s(stdin, "%llu.%llu", &en, &dec) < 0) {
		//TODO:error;
		exit(EXIT_FAILURE);
	}
	money.set_money(en, dec);
	return is;
}

pair<ulong, ulong> Money::get_ent_dec() const {
	pair<ulong, ulong> p;
	p.first = (ulong)money;
	p.second = ((ulong)(money * 1000)) % 1000;
	return p;
}

void Money::add_money(double money_to_add) {
	this->money += money_to_add;
}

bool Money::try_reduce(double money_to_reduce) {
	this->money -= money_to_reduce;
	return this->money >= 0;
}
