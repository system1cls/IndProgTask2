#pragma once
#include "Transaction_pool.hpp"
#include "Client_enter_analyzer.hpp"
#include "Client_activity_analyzer.hpp"

class Analyzer {
private:
	Trasaction_pool pool;
	Client_info_analyzer cl_info_analyzer;
	Client_activity_analyzer cl_activity_analyzer;

public:

	void add_transaction(Date* date, Time* time, Money* money, ulong id, ulong to);

	void add_transaction(Date* date, Time* time, Money* money, ulong id, ulong from, ulong to);

	vector<shared_ptr<Transaction>> getLast();

	vector<shared_ptr<Transaction>> getTransactionWithMoneyType(ulong date, MoneyRequestType type, shared_ptr<Money> target);

	vector<shared_ptr<Transaction>> getTransactionWithperiod(shared_ptr<Date> start, shared_ptr<Date> end);

	
	void add_new_client_enter(Date* date, string& name);

	map<string, ulong> getTop(shared_ptr<Date> start, shared_ptr<Date> end);

	set<string> getRepeat(shared_ptr<Date> first, shared_ptr<Date> second);


	void addNewActivity(ulong id, Date* date, Time* time, string& opearation);

	map<ulong, vector<shared_ptr<Activity>>> getOperation(ulong id, Date* start, Date* end);
};