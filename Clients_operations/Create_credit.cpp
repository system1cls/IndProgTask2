#include "Clients_operations/Client_operations.hpp"

double get_max_credit(Account_currency_type cur_type, Client_type cl_type) {
	vector<vector<double>> maxs{
		{3000000, 600000, 15000, 2000},
		{15000000, 120000, 95000, 100000},
		{50000000, 10000000, 600000, 750000},
		{100000000, 25000000, 1000000, 1300000}
	};

	int it1 = -1, it2 = -1;

	switch (cl_type) {
	case Individual_Client:
		it1 = 0;
		break;
	case VIP_Individual_Client:
		it1 = 1;
		break;
	case Legal_Entity:
		it1 = 2;
		break;
	case VIP_Legal_Entity:
		it1 = 3;
		break;
	}

	switch (cur_type) {
	case RUB:
		it2 = 0;
		break;
	case YUAN:
		it2 = 1;
		break;
	case USD:
		it2 = 2;
		break;
	case EUR:
		it2 = 3;
		break;
	}

	return maxs[it1][it2];
}

double get_rate(Account_currency_type cur_type, Client_type cl_type) {
	double rates[][4]{
		{0.122, 0.043, 0.021, 0.019},
		{0.099, 0.04, 0.015, 0.011},
		{0.167, 0.063, 0.041, 0.032},
		{0.15, 0.058, 0.036, 0.031}
	};

	int it1 = 0, it2 = 0;

	switch (cl_type) {
	case Individual_Client:
		it1 = 0;
		break;
	case VIP_Individual_Client:
		it1 = 1;
		break;
	case Legal_Entity:
		it1 = 2;
		break;
	case VIP_Legal_Entity:
		it1 = 3;
		break;
	}

	switch (cur_type) {
	case RUB:
		it2 = 0;
		break;
	case YUAN:
		it2 = 1;
		break;
	case USD:
		it2 = 2;
		break;
	case EUR:
		it2 = 3;
		break;
	}

	return rates[it1][it2];
}

void create_credit(bank_info& info, Date* date, Time* time, string name, Client_type cl_type, Account_currency_type cur_type, Credit_type credit_type, Money* money) {
	Client* client = get_client(info, name, cl_type);
	if (!client->try_add_acc(cur_type)) {
		fprintf(stderr, "Client error. Active account limit reached\n");
		return;
	}

	if (money->get_money() > get_max_credit(cur_type, cl_type)) {
		fprintf(stderr, "Client error. Too many money to credit\n");
		return;
	}


	Money *money_to_credit = new Money(money->get_money() * 0.999);
	if (!try_reduce_money_from_bank_acc(info, cur_type, money_to_credit->get_money())) {
		fprintf(stderr, "Can`t perform credit");
		return;
	}


	Account* acc = new Account(0, get_account_type_string(credit), money_to_credit, get_account_currency_type_str(cur_type));
	ulong acc_id = info.gen.gen();
	acc->set_ID(acc_id);

	Credit* credit = new Credit(0, get_rate(cur_type, cl_type), new Money(money->get_money()), get_credit_type_string(credit_type));
	ulong credit_id = info.gen.gen();
	credit->set_ID(credit_id);

	Client_debt* debt = new Client_debt(client->get_id(), acc_id, credit_id);
	
	info.accounts.insert({ acc_id, acc });
	info.credits.insert({ credit_id, credit });
	info.client_debts_by_client.insert({ client->get_id(), debt });
	info.client_debts_by_credit.insert({ credit_id, debt });
	info.client_debts_by_account.insert({ acc_id, debt });
	

	info.analyzer.add_transaction(date, time, money_to_credit, info.gen.gen(), acc->get_ID());
	printf("%llu # %llu:%llu # Loan Approved %llu", date->get_date(), time->get_hours(), time->get_minutes(), acc_id);
}