#include "Clients_operations/Client_operation_tools.hpp"



Account* get_acc(bank_info& info, ulong acc_ID) {
	if (!info.accounts.contains(acc_ID)) {
		fprintf(stderr, "Client error. Unknown account");
		return nullptr;
	}

	return info.accounts[acc_ID];
}

bool check_if_client_owns_acc(bank_info& info, Client* client, Account* acc) {
	Client_account* cl_acc = info.client_accounts_by_account[acc->get_ID()];
	Client* real_client = info.clients[cl_acc->get_client_ID()];
	bool is_real = *real_client->get_name() == *client->get_name() && *real_client->get_type() == *client->get_type();
	return is_real;
}

void tranfer_money_to_bank_acc(Date* date, Time* time, bank_info& info, Account* from, Money* money) {
	Account_currency_type cur_type = get_account_currency_type_enum(from->get_currency());
	ulong b_id = add_money_to_bank_acc(info, cur_type, money->get_money());
	from->try_reduce_money(money->get_money());

	info.analyzer.add_transaction(date, time, money, info.gen.gen(), from->get_ID(), b_id);
	Order_book::log_withdrawal(date, time, from->get_ID(), money);
}

