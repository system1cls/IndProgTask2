#include "Complex/Credit.hpp"

Credit::Credit(ulong ID, double intersert_rate, Money* money_was_lended, BString* type) {
	this->ID = ID;
	this->interest_rate = intersert_rate;
	this->money_was_lended = money_was_lended;
	this->money_payed = new Money(0);
	this->type = type;
}

ulong Credit::get_ID() const {
	return this->ID;
}

double Credit::get_interest_rate() const {
	return this->interest_rate;
}

double Credit::get_money_was_lended() const {
	return this->money_was_lended->get_money();
}

double Credit::get_money_payed() const {
	return this->money_payed->get_money();
}

void Credit::add_money(double money) {
	this->money_payed->add_money(money);
}

void Credit::reduce_credit(double money_to_reduce) {
	this->money_was_lended->try_reduce(money_to_reduce);
}

BString* Credit::get_type() const {
	return this->type;
}

Credit::~Credit() {
	if (this->money_was_lended != nullptr) delete this->money_was_lended;
	if (this->type != nullptr) delete this->type;
}
