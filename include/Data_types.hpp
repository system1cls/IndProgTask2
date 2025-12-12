#pragma once

typedef unsigned long long int ulong;

#include <iostream>
#include <ostream>
#include <map>
#include <utility>
#include <vector>

#include "IDgen.hpp"
#include "Simple/Simple_data_types.hpp"
#include "Enums/Enums.hpp"
#include "Complex/Complex_data_types.hpp"
#include "Analyzer/Analyzer.hpp"

typedef struct {
	IDgen gen;
	Analyzer analyzer;
	Date date;
	Time time;
	bool is_open;
	map<ulong, Account*> accounts;
	map<ulong, Deposit*> deposits;
	map<ulong, Credit*> credits;
	map<string, Client*> clients_by_name_type;
	map<ulong, Client*> clients;
	multimap<ulong, Client_account*> client_accounts_by_client;
	map<ulong, Client_account*> client_accounts_by_deposit;
	map<ulong, Client_account*> client_accounts_by_account;
	multimap<Account_currency_type, Bank_account*> bank_accounts;
	multimap<ulong, Client_debt*> client_debts_by_client;
	map<ulong, Client_debt*> client_debts_by_credit;
	map<ulong, Client_debt*> client_debts_by_account;
	multimap<Work_place_type, Work_place*> work_places;
	map<pair<Account_currency_type, Account_currency_type>, Exchange_info*> exchanges;
} bank_info;

