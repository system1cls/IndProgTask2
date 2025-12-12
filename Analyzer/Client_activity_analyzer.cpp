#include "Analyzer/Client_activity_analyzer.hpp"

Activity::Activity(Date* date, Time* time, const string& operation) {
	this->date = make_unique<Date>(date->get_date());
	this->time = make_unique<Time>(time->get_hours(), time->get_minutes());
	this->operation = operation;
}


int comp(shared_ptr<Activity> ac1, shared_ptr<Activity> ac2) {
	ulong day1 = ac1.get()->date.get()->get_date();
	ulong day2 = ac2.get()->date.get()->get_date();
	if (day2 != day1) return day2 > day1;

	ulong hour1 = ac1.get()->time.get()->get_hours();
	ulong hour2 = ac2.get()->time.get()->get_hours();
	if (hour2 != hour1) return hour2 > hour1;

	ulong m1 = ac1.get()->time.get()->get_minutes();
	ulong m2 = ac2.get()->time.get()->get_minutes();
	return m2 > m1;
}

void Client_activity_analyzer::addNewActivity(ulong id, Date* date, Time* time, string& opearation) {
	shared_ptr<Activity> acc = make_shared<Activity>(date, time, opearation);

	if (this->activities.contains(id)) {

		auto it = lower_bound(activities[id].begin(), activities[id].end(), acc, comp);
		activities[id].insert(it, acc);
	}
	else {
		activities[id] = vector<shared_ptr<Activity>>();
		activities[id].push_back(acc);
	}
}


map<ulong, vector<shared_ptr<Activity>>> Client_activity_analyzer::getOperation(ulong id, Date* start, Date* end) {
	map<ulong, vector<shared_ptr<Activity>>> ans;
	if (!this->activities.contains(id)) {
		return ans;
	}
	ulong curDate = 0;
	bool isStarted = false;
	Time* stime = new Time(0, 0);
	Time* etime = new Time(23, 59);
	shared_ptr<Activity> start_ac = make_shared<Activity>(start, stime, "");
	shared_ptr<Activity> end_ac = make_shared<Activity>(end, etime, "");

	auto it_start = lower_bound(activities[id].begin(), activities[id].end(), start_ac, comp);
	auto it_end = upper_bound(activities[id].begin(), activities[id].end(), end_ac, comp);

	for (auto it = it_start; it != it_end; it++) {
		if (curDate != it->get()->date->get_date() || !isStarted) {
			curDate = it->get()->date->get_date();
			ans[curDate] = vector<shared_ptr<Activity>>();
		}
		
		ans[curDate].push_back(*it);
	}


	delete stime;
	delete etime;

	return ans;
}