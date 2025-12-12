#pragma once
#include "Transaction.hpp"
#include <vector>
#include <map>
#include <algorithm>

enum MoneyRequestType {
	Less,
	Equal,
	More
};


class Trasaction_pool {
private:
	vector<shared_ptr<Transaction>> transactions_by_date;
	map<ulong, vector<shared_ptr<Transaction>>> transactions_by_money;

public:
	
	void add_transaction(shared_ptr<Transaction> transaction);
	
	vector<shared_ptr<Transaction>> getLast();

	vector<shared_ptr<Transaction>> getTransactionWithMoneyType(ulong date, MoneyRequestType type, shared_ptr<Money> target);

	vector<shared_ptr<Transaction>> getTransactionWithperiod(shared_ptr<Date> start, shared_ptr<Date> end);

};