#include "Analyzer/Client_enter_analyzer.hpp"

Client_enter_info::Client_enter_info(Date* date, const string& clientName) {
	this->date = make_unique<Date>(date->get_date());
	this->clientName = clientName;
}

Client_enter_info::Client_enter_info(shared_ptr<Date> date, const string& clientName) {
	this->date = make_unique<Date>(date->get_date());
	this->clientName = clientName;
}

int comp_by_date(shared_ptr<Client_enter_info> inf1, shared_ptr<Client_enter_info> inf2) {
	return (inf2->date->get_date() > inf1->date->get_date());
}



void Client_info_analyzer::add_new_client_enter(Date* date, string& name) {
	shared_ptr<Client_enter_info> info = make_shared<Client_enter_info>(date, name);


	if (this->client_info_by_name.contains(name)) {
		vector<shared_ptr<Client_enter_info>> vec = client_info_by_name[name];
		auto it_date_vec = lower_bound(vec.begin(), vec.end(), info, comp_by_date);
		if (it_date_vec->get()->date->get_date() == date->get_date()) {
			return;
		}
		vec.insert(it_date_vec, info);
	}
	else {
		client_info_by_name[name] = vector<shared_ptr<Client_enter_info>>();
		client_info_by_name[name].push_back(info);
	}

	auto it_date = lower_bound(this->cl_info_by_date.begin(), this->cl_info_by_date.end(), info, comp_by_date);
	cl_info_by_date.insert(it_date, info);
}


int comp_by_cnt(pair<string, ulong> p1, pair<string, ulong> p2) {
	return p2.second < p1.second;
}

map<string, ulong> Client_info_analyzer::getTop(shared_ptr<Date> start, shared_ptr<Date> end) {
	shared_ptr<Client_enter_info> startInfo = make_shared<Client_enter_info>(start, "name");
	shared_ptr<Client_enter_info> endInfo = make_shared<Client_enter_info>(end, "name");

	map<string, ulong> cntEnterByName;
	vector<pair<string, ulong>> vec;

	map<string, ulong> ans;

	auto start_it = lower_bound(this->cl_info_by_date.begin(), this->cl_info_by_date.end(), startInfo, comp_by_date);
	auto end_it = upper_bound(this->cl_info_by_date.begin(), this->cl_info_by_date.end(), endInfo, comp_by_date);
	for (auto it = start_it; it != end_it; it++) {
		string& name = it->get()->clientName;
		if (cntEnterByName.contains(name)) {
			cntEnterByName[name]++;
		}
		else {
			cntEnterByName[name] = 1;
		}
	}

	for (auto it = cntEnterByName.begin(); it != cntEnterByName.end(); it++) {
		string name = it->first;
		ulong cnt = it->second;
		vec.push_back({name, cnt});
	}

	sort(vec.begin(), vec.end(), comp_by_cnt);

	int cntToGet = vec.size() > 0 && vec.size() / 10  > 0 ? vec.size() / 10 : 1;
	for (auto it = vec.begin(); it != vec.end() && cntToGet > 0; it++) {
		ans[it->first] = it->second;
	}

	return ans;
}

set<string> Client_info_analyzer::getRepeat(shared_ptr<Date> first, shared_ptr<Date> second) {
	shared_ptr<Client_enter_info> firstInfo = make_shared<Client_enter_info>(first, "name");
	shared_ptr<Client_enter_info> secondInfo = make_shared<Client_enter_info>(second, "name");

	map<string, bool> firstNames;
	set<string> ans;
	auto it_first_start = lower_bound(this->cl_info_by_date.begin(), this->cl_info_by_date.end(), firstInfo, comp_by_date);
	auto it_first_end = upper_bound(this->cl_info_by_date.begin(), this->cl_info_by_date.end(), firstInfo, comp_by_date);;
	for (auto it = it_first_start; it != it_first_end; it++) {
		firstNames.insert({ it->get()->clientName, false });
	}

	auto it_second_start = lower_bound(this->cl_info_by_date.begin(), this->cl_info_by_date.end(), secondInfo, comp_by_date);
	auto it_second_end = upper_bound(this->cl_info_by_date.begin(), this->cl_info_by_date.end(), secondInfo, comp_by_date);
	for (auto it = it_second_end; it != it_second_end; it++) {
		if (firstNames.contains(it->get()->clientName)) {
			firstNames[it->get()->clientName] = true;
		}
		else {
			ans.insert(it->get()->clientName);
		}
	}

	for (auto it = firstNames.begin(); it != firstNames.end(); it++) {
		if (it->second == false) {
			ans.insert(it->first);
		}
	}

	return ans;
}