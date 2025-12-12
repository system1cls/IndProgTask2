#pragma once
#include "Simple/Date.hpp"
#include "Simple/Time.hpp"
#include <vector>
#include <map>

class Activity {
public:
	unique_ptr<Date> date;
	unique_ptr<Time> time;
	string operation;

	Activity(Date* date, Time* time, const string& opearation);
};


class Client_activity_analyzer {
private:
	map<ulong, vector<shared_ptr<Activity>>> activities;

public:

	void addNewActivity(ulong id, Date* date, Time* time, string& opearation);

	map<ulong, vector<shared_ptr<Activity>>> getOperation(ulong id, Date* start, Date* end);
};