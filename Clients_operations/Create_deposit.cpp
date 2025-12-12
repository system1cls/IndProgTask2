#include "Clients_operations/Client_operations.hpp"

double rates[][4][4]{
		{
			{0.09, 0.099, -1, 0.103},
			{0.097, 0.101, -1, 0.12},
			{0.115, 0.119, -1, 0.12},
			{0.121, 0.123, -1, 0.124}
		},
		{
			{0.026, 0.032, -1, 0.029},
			{0.028, 0.035, -1, 0.034},
			{0.039, 0.038, -1, 0.037},
			{0.041, 0.04, -1, 0.042}
		},
		{
			{0.013, 0.017, -1, 0.014},
			{0.015, 0.02, -1, 0.019},
			{0.018, 0.023, -1, 0.023},
			{0.02, 0.025, -1, 0.023}
		},
		{
			{0.007, 0.011, -1, 0.011},
			{0.011, 0.017, -1, 0.015},
			{0.015, 0.018, -1, 0.021},
			{0.019, 0.019, -1, 0.022}
		}
};

enum Period
{
	three_month,
	six_month,
	year,
	two_year,
	unknown,
};

double get_rate(Account_currency_type cur_type, Client_type cl_type, Period per) {
	int cur_it = 0, per_it = 0, cl_it = 0;

	switch (cur_type) {
	case RUB:
		cur_it = 0;
		break;
	case YUAN:
		cur_it = 1;
		break;
	case USD:
		cur_it = 2;
		break;
	case EUR:
		cur_it = 3;
		break;
	}

	switch (per) {
	case three_month:
		per_it = 0;
		break;
	case six_month:
		per_it = 1;
		break;
	case year:
		per_it = 2;
		break;
	case two_year:
		per_it = 3;
		break;
	}

	switch (cl_type) {
	case Individual_Client:
		cl_it = 0;
		break;
	case VIP_Individual_Client:
		cl_it = 1;
		break;
	case Legal_Entity:
		cl_it = 2;
		break;
	case VIP_Legal_Entity:
		cl_it = 3;
		break;
	}

	return rates[cur_it][per_it][cl_it];
}

Period get_per(BString* period_str) {
	if (strcmp(period_str->str, "3 month") == 0) {
		return three_month;
	}

	if (strcmp(period_str->str, "6 month") == 0) {
		return six_month;
	}

	if (strcmp(period_str->str, "12 month") == 0) {
		return year;
	}

	if (strcmp(period_str->str, "24 month") == 0) {
		return two_year;
	}

	return unknown;
}

void create_deposit(bank_info& info, Date* date, Time* time, string name, Client_type cl_type, Account_currency_type cur_type, Deposit_type debit_type, BString* period, Money* money) {
	Period per = get_per(period);
	if (per == unknown) {
		fprintf(stderr, "Illegal period\n");
		return;
	}
	
	ulong cnt_days;
	switch (per) {
	case three_month:
		cnt_days = 90;
		break;
	case six_month:
		cnt_days = 182;
		break;
	case year:
		cnt_days = 365;
		break;
	case two_year:
		cnt_days = 730;
		break;
	}

	double rate = get_rate(cur_type, cl_type, per);
	
	Client* client = get_client(info, name, cl_type);

	Money* money_on_acc = new Money(money->get_money());
	Account* acc = new Account(0, get_account_type_string(debit), money_on_acc, get_account_currency_type_str(cur_type));
	ulong acc_id = info.gen.gen();
	acc->set_ID(acc_id);

	Deposit* deposit = new Deposit((ulong)0, rate, get_debit_type_string(Compounded_Annually_Remaining), new Date(date->get_date()), cnt_days);
	ulong deposit_id = info.gen.gen();
	deposit->set_ID(deposit_id);

	Client_account* cl_acc = new Client_account(client->get_id(), acc_id, deposit_id);

	info.accounts.insert({ acc_id, acc });
	info.deposits.insert({ deposit_id, deposit });
	info.client_accounts_by_client.insert({ client->get_id(), cl_acc});
	info.client_accounts_by_account.insert({acc_id, cl_acc});
	info.client_accounts_by_deposit.insert({ deposit_id, cl_acc });

	printf("%llu # %llu:%llu # Deposit  Approved # %llu", date->get_date(), time->get_hours(), time->get_hours(), acc_id);
}