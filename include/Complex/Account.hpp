#pragma once
#include <utility>
#include "Simple/Simple_data_types.hpp"
#include "Enums/Enums.hpp"

class Account {
private:
	ulong ID;
	BString* account_type;
	Money* money_on_account;
	Money* min_money_on_account_dayly;
	Money* min_money_on_account_Monthly;
	Money* min_money_on_account_Quater;
	Money* min_money_on_account_Semi;
	Money* min_money_on_account_year;
	Money* virtual_money;
	Money* money_tranfered_in_month;
	BString* ñurrency;
	bool is_closed;

public:

	Account(ulong ID, BString* account_type, Money* money_on_account, BString* ñurrency);

	bool is_close() {
		return is_closed;
	}

	void set_close();

	ulong get_ID() const;

	void set_ID(ulong ID);

	BString* get_type() const;

	double get_money() const;

	pair<ulong, ulong> get_ent_dec() const;

	double get_min_money_dayly() const;

	void update_min_money_dayly();

	double get_min_money_monthly() const;

	void update_min_money_monthly();

	double get_min_money_Quater() const;

	void update_min_money_Quater();

	double get_min_money_Semi() const;

	void update_min_money_Semi();

	double get_min_money_year() const;

	void update_min_money_year();

	double get_virtual_money() const;

	void set_virtual_money(double money);

	double check_reserve_banking();

	double do_reserve_Banking(double money_need);

	double money_to_be_returned();

	void return_reserve_money();

	BString* get_currency() const;

	void add_money(double money_to_add);

	bool try_reduce_money(double money);

	double get_money_transfered_in_month();

	void null_money_transfered_in_month();

	void add_money_transfered_in_month(double money_to_add);

	~Account();
};