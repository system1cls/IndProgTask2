#include "Common_tools.hpp"

bool try_reduce_money_from_bank_acc(bank_info& info, Account_currency_type type, double money_to_reduce) {
	auto start_bank_it = info.bank_accounts.lower_bound(type);
	auto end_bank_it = info.bank_accounts.upper_bound(type);
	double money_can_be_reduced = 0;

	for (auto it = start_bank_it; it != end_bank_it; it++) {
		ulong b_id = it->second->get_account_ID();
		Account* acc = info.accounts[b_id];
		money_can_be_reduced += acc->get_money();
	}

	if (!(money_can_be_reduced > money_to_reduce)) {
		return false;
	}

	double money_to_be_reduced = money_to_reduce;
	for (auto it = start_bank_it; it != end_bank_it; it++) {
		ulong b_id = it->second->get_account_ID();
		Account* acc = info.accounts[b_id];
		double temp = acc->get_money();
		acc->try_reduce_money(min(acc->get_money(), money_to_be_reduced));
		money_to_be_reduced -= temp;
	}

	return true;
}