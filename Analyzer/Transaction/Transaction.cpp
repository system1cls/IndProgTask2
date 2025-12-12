#include "Analyzer/Transaction.hpp"

Transaction::Transaction(Date* date, Time* time, Money* money, ulong from, ulong to) {
	this->date = make_unique<Date>(date->get_date());
	this->time = make_unique<Time>(time->get_hours(), time->get_minutes());
	this->money = make_unique<Money>(money->get_money());
	this->accFrom = from;
	this->accTo = to;
}
