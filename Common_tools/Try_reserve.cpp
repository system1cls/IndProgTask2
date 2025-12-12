#include "Common_tools.hpp"

bool try_reserve(bank_info& info, Account_currency_type cur_type, double money_need, ulong acc_id) {
	vector<Account* > acc_reserve;
	double money_to_be_lended = 0;

	for (auto id_deposit : info.deposits) {
		if (money_to_be_lended >= money_need) {
			break;
		}

		Deposit* deposit = id_deposit.second;
		Client_account* cl_acc = info.client_accounts_by_deposit[id_deposit.first];
		Account* account = info.accounts[cl_acc->get_account_ID()];

		if (get_account_type_enum(account->get_type()) != Account_type::deposit) {
			continue;
		}

		if (deposit->get_days_of_duration() == 0) {
			continue;
		}

		if (account->check_reserve_banking() > 0) {
			acc_reserve.push_back(account);
			money_to_be_lended += account->check_reserve_banking();
		}
	}

	if (money_to_be_lended < money_need) {
		return false;
	}

	for (auto acc : acc_reserve) {
		double money_lended = acc->do_reserve_Banking(money_need);
		money_need -= money_lended;
		info.analyzer.add_transaction(&info.date, &info.time, new Money(money_lended), info.gen.gen(), acc->get_ID(), acc_id);
		if (money_need <= 0) return true;
	}


	fprintf(stderr, "try_reserve error");
	exit(EXIT_FAILURE);
}