#include "Analyzer/Transaction_pool.hpp"

int comp_trans_with_money(shared_ptr<Transaction> trans1, shared_ptr<Transaction> trans2) {
	return (trans2.get()->money.get()->get_money() > trans1.get()->money.get()->get_money());
}


int comp_trans_with_datetime(shared_ptr<Transaction> trans1, shared_ptr<Transaction> trans2) {
	ulong day1 = trans1.get()->date.get()->get_date();
	ulong day2 = trans2.get()->date.get()->get_date();
	if (day2 != day1) return day2 > day1;

	ulong hour1 = trans1.get()->time.get()->get_hours();
	ulong hour2 = trans2.get()->time.get()->get_hours();
	if (hour2 != hour1) return hour2 > hour1;

	ulong m1 = trans1.get()->time.get()->get_minutes();
	ulong m2 = trans2.get()->time.get()->get_minutes();
	return m2 > m1;
}


void Trasaction_pool::add_transaction(shared_ptr<Transaction> trans) {
	auto it_day = lower_bound(this->transactions_by_date.begin(), this->transactions_by_date.end(), trans, comp_trans_with_datetime);
	this->transactions_by_date.insert(it_day, trans);
	ulong udate = trans->date->get_date();
	if (this->transactions_by_money.contains(udate)) {
		auto it_money = lower_bound(this->transactions_by_money[udate].begin(), this->transactions_by_money[udate].end(), trans, comp_trans_with_money);
		this->transactions_by_money[udate].insert(it_money, trans);
	}
	else {
		this->transactions_by_money[udate] = vector<shared_ptr<Transaction>>();
		this->transactions_by_money[udate].push_back(trans);
	}

}

vector<shared_ptr<Transaction>> Trasaction_pool::getTransactionWithMoneyType(ulong date, MoneyRequestType type, shared_ptr<Money> target) {
	vector<shared_ptr<Transaction>> ans;
	if (!this->transactions_by_money.contains(date)) {
		return ans;
	}

	switch (type) {
	case Less: {
		auto it = this->transactions_by_money[date].begin();
		while (it != transactions_by_money[date].end() && it->get()->money->get_money() < target->get_money()) {
			ans.push_back(*it);
			it++;
		}
		return ans;
	}
	case Equal: {
		Date* cdate = new Date(date);
		Time* time = new Time(0, 0);
		Money* money = new Money(target->get_money());
		shared_ptr<Transaction> moneyTr = make_shared<Transaction>(cdate, time, money, -1, -1);
		auto it_money = lower_bound(this->transactions_by_money[date].begin(), this->transactions_by_money[date].end(), moneyTr, comp_trans_with_money);
		while (it_money != transactions_by_money[date].end() && it_money->get()->money->get_money() == target->get_money()) {
			ans.push_back(*it_money);
			it_money++;
		}
		return ans;
	}
	case More:
		Date* cdate = new Date(date);
		Time* time = new Time(0, 0);
		Money* money = new Money(target->get_money());
		shared_ptr<Transaction> moneyTr = make_shared<Transaction>(cdate, time, money, -1, -1);
		auto it_money = upper_bound(this->transactions_by_money[date].begin(), this->transactions_by_money[date].end(), moneyTr, comp_trans_with_money);
		while (it_money != transactions_by_money[date].end()) {
			ans.push_back(*it_money);
			it_money++;
		}
		return ans;
	}

	return ans;
}


vector<shared_ptr<Transaction>> Trasaction_pool::getTransactionWithperiod(shared_ptr<Date> start, shared_ptr<Date> end) {
	Date* sDate = new Date(start->get_date());
	Date* eDate = new Date(end->get_date());
	Time* sTime = new Time(0, 0);
	Time* eTime = new Time(23, 59);
	Money* money = new Money(0);
	shared_ptr<Transaction> sTrans = make_shared<Transaction>(sDate, sTime, money, -1, -1);
	shared_ptr<Transaction> eTrans = make_shared<Transaction>(eDate, eTime, money, -1, -1);
	auto it_start = lower_bound(this->transactions_by_date.begin(), this->transactions_by_date.end(), sTrans, comp_trans_with_datetime);
	auto it_end = upper_bound(transactions_by_date.begin(), transactions_by_date.end(), eTrans, comp_trans_with_datetime);
	vector<shared_ptr<Transaction>> ans;
	while (it_start != it_end) {
		ans.push_back(*it_start);
		it_start++;
	}
	return ans;
}

vector<shared_ptr<Transaction>> Trasaction_pool::getLast() {
	int number_of_first = this->transactions_by_date.size() >= 10 ? this->transactions_by_date.size() - 10 : 0;
	auto it_start = this->transactions_by_date.begin() + number_of_first;

	vector<shared_ptr<Transaction>> ans;

	for (auto it = it_start; it != transactions_by_date.end(); it++) {
		ans.push_back(*it);
	}
	
	return ans;
}