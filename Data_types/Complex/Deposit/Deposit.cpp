#include "Complex/Deposit.hpp"

Deposit::Deposit(ulong ID, double interest_rate, BString* type, Date* date_of_creation) {
	this->ID = ID;
	this->interest_rate = interest_rate;
	this->type = type;
	this->date_of_creation = date_of_creation;
}

Deposit::Deposit(ulong ID, double interest_rate, BString* type, Date* date_of_creation, ulong days_of_duration) {
	this->ID = ID;
	this->interest_rate = interest_rate;
	this->type = type;
	this->date_of_creation = date_of_creation;
	this->days_of_duration = days_of_duration;
}

ulong Deposit::get_ID() {
	return this->ID;
}

void Deposit::set_ID(ulong ID) {
	this->ID = ID;
}

double Deposit::get_interest_rate() {
	return this->interest_rate;
}

BString* Deposit::get_type() {
	return this->type;
}

Date* Deposit::get_date_of_creation() {
	return this->date_of_creation;
}

ulong Deposit::get_days_of_duration() {
	return this->days_of_duration;
}

void Deposit::add_days(ulong days) {
	this->days_of_duration += days;
}

void Deposit::dec_days() {
	this->days_of_duration--;
}

Deposit::~Deposit() {
	if (this->date_of_creation != nullptr) delete this->date_of_creation;
	if (this->type != nullptr) delete this->type;
}