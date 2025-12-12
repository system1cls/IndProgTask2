#pragma once
#include "Simple/Date.hpp"
#include <vector>
#include <map>
#include <set>
#include <algorithm>

class Client_enter_info {
public:
	unique_ptr<Date> date;
	string clientName;

	Client_enter_info(Date* date, const string& clientName);
	Client_enter_info(shared_ptr<Date> date, const string& clientName);
};




class Client_info_analyzer {
private:
	vector<shared_ptr<Client_enter_info>> cl_info_by_date;
	map<string, vector<shared_ptr<Client_enter_info>>> client_info_by_name;

public:

	void add_new_client_enter(Date* date, string& name);

	map<string, ulong> getTop(shared_ptr<Date> start, shared_ptr<Date> end);

	set<string> getRepeat(shared_ptr<Date> first, shared_ptr<Date> second);
};