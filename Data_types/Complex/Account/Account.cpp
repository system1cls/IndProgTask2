#include "Complex/Account.hpp"

Account::Account(ulong ID, BString* account_type, Money* money_on_account, BString* ñurrency) {
	this->ID = ID;
	this->account_type = account_type;
	this->money_on_account = money_on_account;
	this->virtual_money = new Money(money_on_account->get_money());
	this->min_money_on_account_dayly = new Money(money_on_account->get_money());
	this->min_money_on_account_Monthly = new Money(money_on_account->get_money());
	this->min_money_on_account_Quater = new Money(money_on_account->get_money());
	this->min_money_on_account_Semi = new Money(money_on_account->get_money());
	this->min_money_on_account_year = new Money(money_on_account->get_money());
	this->money_tranfered_in_month = new Money(0);
	this->ñurrency = ñurrency;
	this->is_closed = false;
}

ulong Account::get_ID() const {
	return this->ID;
}

void Account::set_close() {
	this->is_closed = true;
}

void Account::set_ID(ulong ID) {
	this->ID = ID;
}

BString* Account::get_type() const {
	return this->account_type;
}

double Account::get_money() const {
	return this->money_on_account->get_money();
}

pair<ulong, ulong> Account::get_ent_dec() const {
	return this->money_on_account->get_ent_dec();
}

double Account::get_min_money_dayly() const {
	return this->min_money_on_account_dayly->get_money();
}

void Account::update_min_money_dayly() {
	this->min_money_on_account_dayly->set_money(this->get_money());
}

double Account::get_min_money_monthly() const {
	return this->min_money_on_account_Monthly->get_money();
}

void Account::update_min_money_monthly() {
	this->min_money_on_account_Monthly->set_money(this->get_money());
}

double Account::get_min_money_Quater() const {
	return this->min_money_on_account_Quater->get_money();
}

void Account::update_min_money_Quater() {
	this->min_money_on_account_Quater->set_money(this->get_money());
}

double Account::get_min_money_Semi() const {
	return this->min_money_on_account_Semi->get_money();
}

void Account::update_min_money_Semi() {
	this->min_money_on_account_Semi->set_money(this->get_money());
}

double Account::get_min_money_year() const {
	return this->min_money_on_account_year->get_money();
}

void Account::update_min_money_year() {
	this->min_money_on_account_year->set_money(this->get_money());
}

BString* Account::get_currency() const {
	return this->ñurrency;
}

void Account::add_money(double money_to_add) {
	this->money_on_account->add_money(money_to_add);
	this->virtual_money->add_money(money_to_add);
}

bool Account::try_reduce_money(double money) {
	bool succs = this->money_on_account->try_reduce(money);
	if (!succs) {
		return false;
	}

	this->virtual_money->try_reduce(money);

	if (this->get_min_money_dayly() > this->get_money()) {
		update_min_money_dayly();
	}
	if (this->get_min_money_monthly() > this->get_money()) {
		update_min_money_monthly();
	}
	if (this->get_min_money_Quater() > this->get_money()) {
		update_min_money_Quater();
	}
	if (this->get_min_money_Semi() > this->get_money()) {
		update_min_money_Semi();
	}
	if (this->get_min_money_year() > this->get_money()) {
		update_min_money_year();
	}


	return true;
}

double Account::get_virtual_money() const {
	return this->virtual_money->get_money();
}

void Account::set_virtual_money(double money) {
	this->virtual_money->set_money(money);
}

double Account::check_reserve_banking() {
	return this->money_on_account->get_money() - this->virtual_money->get_money() * 0.2;
}

double Account::do_reserve_Banking(double money_need) {
	if (get_account_currency_type_enum(this->account_type) != debit) {
		fprintf(stderr, "Banking from not debit\n");
		exit(EXIT_FAILURE);
	}

	
	double money_send = min(this->money_on_account->get_money() * 0.8, money_need);
	this->money_on_account->set_money(this->money_on_account->get_money() - money_send);
	return money_send;
}

double Account::money_to_be_returned() {
	return this->virtual_money->get_money() - this->money_on_account->get_money();
}

void Account::return_reserve_money() {
	this->money_on_account->set_money(virtual_money->get_money());
}

double Account::get_money_transfered_in_month() {
	return this->money_tranfered_in_month->get_money();
}

void Account::null_money_transfered_in_month() {
	this->money_tranfered_in_month->set_money(0);
}

void Account::add_money_transfered_in_month(double money_to_add) {
	this->money_tranfered_in_month->add_money(money_to_add);
}

Account::~Account() {
	if (this->account_type != nullptr) delete account_type;
	if (this->money_on_account != nullptr) delete this->money_on_account;
	if (this->min_money_on_account_dayly != nullptr) delete min_money_on_account_dayly;
	if (this->min_money_on_account_Monthly != nullptr) delete min_money_on_account_Monthly;
	if (this->min_money_on_account_Quater != nullptr) delete min_money_on_account_Quater;
	if (this->min_money_on_account_Semi != nullptr) delete min_money_on_account_Semi;
	if (this->min_money_on_account_year != nullptr) delete min_money_on_account_year;
	if (this->money_tranfered_in_month != nullptr) delete money_tranfered_in_month;
 	if (this->ñurrency != nullptr) delete this->ñurrency;
}