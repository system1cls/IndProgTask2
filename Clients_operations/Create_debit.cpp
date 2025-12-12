#include "Clients_operations/Client_operations.hpp"

double get_start_money(Client_type client_type, Account_currency_type cur_type) {
	switch (client_type) {
	case Individual_Client:
		switch (cur_type) {
		case RUB: return 10000;
		case YUAN: return 2000;
		case USD:
		case EUR: return 100;
		}
	case VIP_Individual_Client:
		switch (cur_type) {
		case RUB: return 4000;
		case YUAN: return 1000;
		case USD:
		case EUR: return 50;
		}
	case Legal_Entity:
		switch (cur_type) {
		case RUB: return 25000;
		case YUAN: return 5000;
		case USD:
		case EUR: return 200;
		}
	case VIP_Legal_Entity:
		switch (cur_type) {
		case RUB: return 15000;
		case YUAN: return 2000;
		case USD:
		case EUR: return 100;
		}
	}
}

void create_debit(bank_info& info, Date* date, Time* time, string name, Client_type cl_type, Account_currency_type cur_type) {
	Client* client = get_client(info, name, cl_type);
	if (!client->try_add_acc(cur_type)) {
		fprintf(stderr, "Client error. Active account limit reached\n");
		return;
	}

	double start_money = get_start_money(cl_type, cur_type);
	auto b_acc_it = info.bank_accounts.lower_bound(cur_type);
	if (b_acc_it == info.bank_accounts.upper_bound(cur_type)) {
		fprintf(stderr, "No bank_acc for currency");
		exit(EXIT_FAILURE);
	}
	Account* b_acc = info.accounts[b_acc_it->second->get_account_ID()];
	b_acc->add_money(start_money);

	Account* acc = new Account((ulong)0, get_account_type_string(debit), new Money(start_money * (-1)), get_account_currency_type_str(cur_type));
	ulong id = info.gen.gen();
	acc->set_ID(id);
	Money money(start_money);
	Order_book::log_transist(date, time, id, b_acc->get_ID(), &money);

	Deposit* deposit = new Deposit((ulong)0, 0., get_debit_type_string(Compounded_Annually_Remaining), new Date(date->get_date()));
	ulong deposit_id = info.gen.gen();
	deposit->set_ID(deposit_id);


	Client_account* cl_acc = new Client_account(client->get_id(), id, deposit_id);

	info.accounts.insert({ id, acc });
	info.deposits.insert({ deposit_id, deposit });
	info.client_accounts_by_account.insert({ id, cl_acc });
	info.client_accounts_by_deposit.insert({ deposit_id, cl_acc });
	info.client_accounts_by_client.insert({ client->get_id(), cl_acc });


	info.analyzer.add_transaction(date, time, &money, info.gen.gen(), acc->get_ID(), b_acc->get_ID());
	printf("%llu # %llu:%llu # Account Created %llu # %le\n", date->get_date(), time->get_hours(), time->get_minutes(), id, acc->get_money());
}
