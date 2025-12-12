#include "Clients_operations/Client_operations.hpp"

void withdraw(bank_info& info, Date* date, Time* time, string name, Client_type cl_type, ulong acc_ID, Money* money_to_withdraw) {
	Client* client = get_client(info, name, cl_type);
	Account* acc = get_acc(info, acc_ID);
	if (acc == nullptr) {
		fprintf(stderr, "Client error. Unknown account\n");
		return;
	}


	if (!check_if_client_owns_acc(info, client, acc)) {
		fprintf(stderr, "Client error. Access denied\n");
		return;
	}

	if (acc->is_close()) {
		fprintf(stderr, "Client error. Account closed\n");
		return;
	}

	if (get_account_type_enum(acc->get_type()) == credit) {
		fprintf(stderr, "Client error. Unable to withdraw\n");
		return;
	}

	Money tarif(max(2.5, acc->get_money() * 0.0025));
	if (acc->get_money() < tarif.get_money()) {
		fprintf(stderr, "Client error. Negative balance on closure\n");
		return;
	}

	if (acc->get_money() < tarif.get_money() + money_to_withdraw->get_money()) {
		fprintf(stderr, "Client error. Insufficient funds");
		return;
	}

	
	if (get_account_type_enum(acc->get_type()) == deposit) {
		Client_account* cl_acc = info.client_accounts_by_account[acc->get_ID()];
		Deposit* deposit = info.deposits[cl_acc->get_debit_ID()];
		if (deposit->get_days_of_duration() == 0) {
			tranfer_money_to_bank_acc(date, time, info, acc, &tarif);
			acc->try_reduce_money(money_to_withdraw->get_money());

		}

		if (acc->get_money() < 0.001) {
			acc->set_close();
		}
	}
	else {
		tranfer_money_to_bank_acc(date, time, info, acc, &tarif);
		acc->try_reduce_money(money_to_withdraw->get_money());
	}


	printf("%llu # %llu:%llu # Funds Withdrawn %llu # %llu.%llu", date->get_date(), time->get_hours(), time->get_minutes(), acc->get_ID(), acc->get_ent_dec().first, acc->get_ent_dec().second);

}