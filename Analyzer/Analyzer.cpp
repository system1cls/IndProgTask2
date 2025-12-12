#include "Analyzer/Analyzer.hpp"

void Analyzer::add_transaction(Date* date, Time* time, Money* money, ulong id, ulong to) {
	shared_ptr<Transaction> transaction = make_shared<Transaction>(date, time, money, -1, to);
	transaction->id = id;

	this->pool.add_transaction(transaction);
}

void Analyzer::add_transaction(Date* date, Time* time, Money* money, ulong id, ulong from, ulong to) {
	shared_ptr<Transaction> transaction = make_shared<Transaction>(date, time, money, from, to);
	transaction->id = id;

	this->pool.add_transaction(transaction);
}

vector<shared_ptr<Transaction>> Analyzer::getLast() {
	return this->pool.getLast();
}

vector<shared_ptr<Transaction>> Analyzer::getTransactionWithMoneyType(ulong date, MoneyRequestType type, shared_ptr<Money> target) {
	return this->pool.getTransactionWithMoneyType(date, type, target);
}

vector<shared_ptr<Transaction>> Analyzer::getTransactionWithperiod(shared_ptr<Date> start, shared_ptr<Date> end) {
	return this->pool.getTransactionWithperiod(start, end);
}


void Analyzer::add_new_client_enter(Date* date, string& name) {
	this->cl_info_analyzer.add_new_client_enter(date, name);
}

map<string, ulong> Analyzer::getTop(shared_ptr<Date> start, shared_ptr<Date> end) {
	return this->cl_info_analyzer.getTop(start, end);
}

set<string> Analyzer::getRepeat(shared_ptr<Date> first, shared_ptr<Date> second) {
	return this->cl_info_analyzer.getRepeat(first, second);
}

void Analyzer::addNewActivity(ulong id, Date* date, Time* time, string& opearation) {
	this->cl_activity_analyzer.addNewActivity(id, date, time, opearation);
}

map<ulong, vector<shared_ptr<Activity>>> Analyzer::getOperation(ulong id, Date* start, Date* end) {
	return this->cl_activity_analyzer.getOperation(id, start, end);
}

