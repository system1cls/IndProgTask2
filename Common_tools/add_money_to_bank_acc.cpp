#include "Common_tools.hpp"

ulong add_money_to_bank_acc(bank_info& info, Account_currency_type type, double money) {
	auto b_acc_it = info.bank_accounts.lower_bound(type);
	if (b_acc_it == info.bank_accounts.upper_bound(type)) {
		fprintf(stderr, "No bank_acc for currency");
		exit(EXIT_FAILURE);
	}
	Account* b_acc_to = info.accounts[b_acc_it->second->get_account_ID()];

	b_acc_to->add_money(money);
	return b_acc_to->get_ID();
}