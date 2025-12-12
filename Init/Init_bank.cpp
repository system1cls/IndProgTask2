#include "Data_types.hpp"
#include "Init_bank.hpp"
#include "Common_tools.hpp"
#include <algorithm>
using namespace std;

void get_accounts(map<ulong, Account*>& accounts) {
	ulong account_cnt = 0;
	if (scanf("Accounts %llu", &account_cnt) != 1) {
		fprintf(stderr, "Accounts cnt init error");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < account_cnt; i++) {
		ulong ID;

		char type_str[100];
		ulong ent, dec;
		char currency_str[100];

		if (scanf("\n%llu # %99[a-zA-Z0-9/_] # %llu.%llu # %99[a-zA-Z0-9/_]", &ID, type_str, &ent, &dec, currency_str) != 5) {
			fprintf(stderr, "Accounts init error");
			exit(EXIT_FAILURE);
		}
		
		BString* acc_type = new BString(type_str);
		acc_type = get_account_type_string(get_account_type_enum(acc_type));

		Money* money = new Money(0);
		money->set_money(ent, dec);

		BString* currency = new BString(currency_str);

		Account* acc = new Account(ID, acc_type, money, currency);
		accounts.insert({ ID, acc });
	}
}

void get_Deposits(map<ulong, Deposit*>& debits) {
	ulong debits_cnt;
	if (scanf("\nDeposits %llu", &debits_cnt) != 1) {
		fprintf(stderr, "Deposits cnt init error");
		exit(EXIT_FAILURE);
	}


	for (int i = 0; i < debits_cnt; i++) {
		ulong ID;
		double rate;
		char type_str[100];
		ulong date_l;
		ulong days;

		if (scanf("\n%llu # %le # %99[a-zA-Z0-9/_ ] # %llu # %llu", &ID, &rate, type_str, &date_l, &days) != 5) {
			fprintf(stderr, "Deposits init error");
			exit(EXIT_FAILURE);
		}
		
		string temp = string(type_str);
		temp = delete_spaces_from_start_and_end(temp);
		replace(temp.begin(), temp.end(), ' ', '_');
		BString* type = new BString("");
		strcpy(type->str, temp.c_str());
		type = get_debit_type_string(get_debit_type_enum(type));

		Date* date = new Date(days);

		Deposit* debit = new Deposit(ID, rate, type, date, days);
		debits.insert({ ID, debit });
	}
}

void get_credits(map<ulong, Credit*>& credits) {
	ulong credits_cnt;
	if (scanf("\nCredits %llu", &credits_cnt) != 1) {
		fprintf(stderr, "Credits cnt init error");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < credits_cnt; i++) {
		ulong ID;
		double rate;
		ulong ent, dec;
		char type_ch[100];

		if (scanf("\n%llu # %le # %llu.%llu # %99[a-zA-Z0-9/_ ]", &ID, &rate, &ent, &dec, type_ch) != 5) {
			fprintf(stderr, "credits init error");
			exit(EXIT_FAILURE);
		}
		
		string temp = string(type_ch);
		temp = delete_spaces_from_start_and_end(temp);
		replace(temp.begin(), temp.end(), ' ', '_');
		BString* type = new BString("");
		strcpy(type->str, temp.c_str());
		type = get_credit_type_string(get_credit_type_enum(type));

		Money* money = new Money(0);
		money->set_money(ent, dec);

		Credit* credit = new Credit(ID, rate, money, type);
		credits.insert({ ID, credit });
	}
}

void get_clients(map<ulong, Client*>& clients, map<string, Client*>& clients_by_name_type) {
	ulong clients_cnt;
	if (scanf("\nClients %llu", &clients_cnt) != 1) {
		fprintf(stderr, "Clients cnt init error");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < clients_cnt; i++) {
		ulong ID;
		char name_ch[100];
		char type_ch[100];

		if (scanf("\n%llu # %99[a-zA-Z0-9/_ ] # %99[a-zA-Z0-9/_ ]", &ID, name_ch, type_ch) != 3) {
			fprintf(stderr, "clients init error");
			exit(EXIT_FAILURE);
		}

		string temp_name = string(name_ch);
		temp_name = delete_spaces_from_start_and_end(temp_name);
		strcpy(name_ch, temp_name.c_str());
		BString* name = new BString(name_ch);

		string temp = string(type_ch);
		temp = delete_spaces_from_start_and_end(temp);
		replace(temp.begin(), temp.end(), ' ', '_');
		BString* type = new BString("");
		strcpy(type->str, temp.c_str());
		type = get_client_type_string(get_client_type_enum(type));

		Client* client = new Client(ID, name, type);
		clients.insert({ ID, client });
		clients_by_name_type.insert({ temp_name, client });
	}
}

void get_client_accs(multimap<ulong, Client_account*>& client_accs_client, map<ulong, Client_account*>& client_accs_deposit, map<ulong, Client_account*>& client_accs_acc) {
	ulong client_acc_cnt;
	if (scanf("\nClient Deposit %llu", &client_acc_cnt) != 1) {
		fprintf(stderr, "Client deposits cnt init error");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < client_acc_cnt; i++) {
		ulong client_ID;
		ulong acc_ID;
		ulong deposit_ID;

		if (scanf("\n%llu # %llu # %llu", &client_ID, &acc_ID, &deposit_ID) != 3) {
			fprintf(stderr, "client acc init error");
			exit(EXIT_FAILURE);
		}

		Client_account* acc = new Client_account(client_ID, acc_ID, deposit_ID);
		client_accs_client.insert({ client_ID, acc });
		client_accs_deposit.insert({ deposit_ID, acc });
		client_accs_acc.insert({acc_ID, acc});
	}
}

void get_bank_accs(bank_info& info) {
	ulong bank_acc_cnt;
	if (scanf("\nBank Accounts %llu", &bank_acc_cnt) != 1) {
		fprintf(stderr, "Bank accounts cnt init error");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < bank_acc_cnt; i++) {
		ulong ID;

		if (scanf("\n%llu", &ID) != 1) {
			fprintf(stderr, "bank accs init error");
			exit(EXIT_FAILURE);
		}

		Account* acc = info.accounts.at(ID);

		Bank_account* b_acc = new Bank_account(ID);
		info.bank_accounts.insert({get_account_currency_type_enum(acc->get_currency()), b_acc});
	}
}

void get_client_debts(multimap<ulong, Client_debt*>& client_debts, map<ulong, Client_debt*>& client_debt_acc,  map<ulong, Client_debt*>& client_debt_by_credit) {
	ulong client_debt_cnt;
	if (scanf("\nClient Credit %llu", &client_debt_cnt) != 1) {
		fprintf(stderr, "Client credit cnt error");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < client_debt_cnt; i++) {
		ulong client_ID;
		ulong acc_ID;
		ulong credit_ID;

		if (scanf("\n%llu # %llu # %llu", &client_ID, &acc_ID, &credit_ID) != 3) {
			fprintf(stderr, "clients debts init error");
			exit(EXIT_FAILURE);
		}

		Client_debt* debt = new Client_debt(client_ID, acc_ID, credit_ID);
		client_debts.insert({ client_ID, debt });
		client_debt_acc.insert({acc_ID, debt});
		client_debt_by_credit.insert({ credit_ID, debt });
	}
}

void get_work_places(multimap<Work_place_type, Work_place*>& work_places) {
	ulong work_place_cnt;
	if (scanf("\nWork Places %llu", &work_place_cnt) != 1) {
		fprintf(stderr, "Work places cnt init error");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < work_place_cnt; i++) {
		char type_ch[100];
		ulong cnt_places;

		if (scanf("\n%99[a-zA-Z0-9/_ ] # %llu", type_ch, &cnt_places) != 2) {
			fprintf(stderr, "work places init error");
			exit(EXIT_FAILURE);
		}

		string temp = string(type_ch);
		temp = delete_spaces_from_start_and_end(temp);
		temp = delete_spaces_from_start_and_end(temp);
		replace(temp.begin(), temp.end(), ' ', '_');
		BString* type = new BString("");
		strcpy(type->str, temp.c_str());

		Work_place* place = new Work_place(type, cnt_places);
		work_places.insert({ get_work_place_type_enum(type), place });
	}
}

void get_exchange_infos(map<pair<Account_currency_type, Account_currency_type>, Exchange_info*>& infos) {
	ulong info_cnt;
	if (scanf("\nExchange Rates %llu", &info_cnt) != 1) {
		fprintf(stderr, "Exchange rates cnt init error");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < info_cnt; i++) {
		char from_ch[100];
		char to_ch[100];
		double coef;

		if (scanf("\n%99[a-zA-Z0-9/_] # %99[a-zA-Z0-9/_] # %le", from_ch, to_ch, &coef) != 3) {
			fprintf(stderr, "exchange info init error");
			exit(EXIT_FAILURE);
		}

		BString* from = new BString(from_ch);
		BString* to = new BString(to_ch);

		Exchange_info* info = new Exchange_info(from, to, coef);
		pair<Account_currency_type, Account_currency_type> curs;
		curs.first = get_account_currency_type_enum(from);
		curs.second = get_account_currency_type_enum(to);
		infos.insert({ curs, info });
	}
}

void add_cnt_accs_to_clients(bank_info& info) {
	for (auto id_cl_acc : info.client_accounts_by_client) {
		ulong client_id = id_cl_acc.first;
		Client_account* cl_acc = id_cl_acc.second;
		Client* client = info.clients.at(client_id);
		Account* acc = info.accounts.at(cl_acc->get_account_ID());
		if (!client->try_add_acc(get_account_currency_type_enum(acc->get_type()))) {
			fprintf(stderr, "Client error. Active account limit reached");
			exit(EXIT_FAILURE);
		}
	}

	for (auto id_cl_debt : info.client_debts_by_client) {
		ulong client_id = id_cl_debt.first;
		Client_debt* cl_debt = id_cl_debt.second;
		Client* client = info.clients.at(client_id);
		Account* acc = info.accounts.at(cl_debt->get_account_ID());
		if (!client->try_add_acc(get_account_currency_type_enum(acc->get_type()))) {
			fprintf(stderr, "Client error. Active account limit reached");
			exit(EXIT_FAILURE);
		}
	}
}


bank_info get_init_info(ulong seed) {
	bank_info info;
	
	info.gen.set_seed(seed);
	info.date.set_date(0);
	info.time.set_time(8, 0);
	info.is_open = false;

	get_accounts(info.accounts);
	get_Deposits(info.deposits);
	
	get_credits(info.credits);
	get_clients(info.clients, info.clients_by_name_type);
	get_client_accs(info.client_accounts_by_client, info.client_accounts_by_deposit, info.client_accounts_by_account);
	get_bank_accs(info);
	get_client_debts(info.client_debts_by_client, info.client_debts_by_account, info.client_debts_by_credit);
	get_work_places(info.work_places);
	get_exchange_infos(info.exchanges);
	add_cnt_accs_to_clients(info);
	
	return info;
}
