#include "tests/loadConfigs.hpp"


void set_basic(bank_info& info) {
	info.accounts.insert({ 1, new Account(1, new BString("debit"), new Money(1000000), new BString("RUB")) });
	info.accounts.insert({ 2, new Account(2, new BString("debit"), new Money(500000), new BString("YUAN")) });
	info.accounts.insert({ 3, new Account(3, new BString("debit"), new Money(100000), new BString("USD")) });
	info.accounts.insert({ 4, new Account(4, new BString("debit"), new Money(100000), new BString("EUR")) });

	info.bank_accounts.insert({ RUB, new Bank_account(1) });
	info.bank_accounts.insert({ YUAN, new Bank_account(2) });
	info.bank_accounts.insert({ USD, new Bank_account(3) });
	info.bank_accounts.insert({ EUR, new Bank_account(4) });

	Client* donatello = new Client(1, new BString("Donatello"), new BString(get_client_type_string(Individual_Client)->str));
	info.clients.insert({ 1,  donatello });
	info.clients_by_name_type.insert({ "Donatello", donatello });

	Client* mike = new Client(2, new BString("Mike"), new BString(get_client_type_string(Legal_Entity)->str));
	info.clients.insert({ 2, mike });
	info.clients_by_name_type.insert({ "Mike", mike });

	info.is_open = true;

	double coefs[][3] = { {0.088, 0.012, 0.01}, 
		{11.34, 0.14, 0.12}, 
		{80.98, 7.12, 0.85}, 
		{94.58, 8.31, 1.17} };
	for (int i = 0; i < 4; i++) {
		Account_currency_type from;
		switch (i) {
		case 0:
			from = RUB;
			break;
		case 1:
			from = YUAN;
			break;
		case 2:
			from = USD;
			break;
		case 3:
			from = EUR;
			break;
		}

		for (int j = 0; j < 3; j++) {
			Account_currency_type to;
			switch (i * 4 + j) {
			case 4:
			case 8:
			case 12:
				to = RUB;
				break;

			case 0:
			case 9:
			case 13:
				to = YUAN;
				break;

			case 1:
			case 5:
			case 14:
				to = USD;
				break;

			case 2:
			case 6:
			case 10:
				to = EUR;
				break;
			}

			info.exchanges.insert({ {from, to}, new Exchange_info(get_account_currency_type_str(from), get_account_currency_type_str(to), coefs[i][j]) });
		}
	}


	info.work_places.insert({ Client_Manager, new Work_place(get_work_place_type_string(Client_Manager), 5)});
	info.work_places.insert({ Cash_Desk, new Work_place(get_work_place_type_string(Cash_Desk), 5) });
	info.work_places.insert({ VIP_Client_Manager, new Work_place(get_work_place_type_string(VIP_Client_Manager), 5) });
	info.work_places.insert({ Currency_Exchange, new Work_place(get_work_place_type_string(Currency_Exchange), 5) });
}

bank_info createSimpleConf() {
	bank_info info;

	set_basic(info);

	info.accounts.insert({ 10, new Account(10, new BString("debit"), new Money(100000), new BString("RUB")) });
	info.deposits.insert({ 1, new Deposit(1, 0, get_debit_type_string(Compounded_Daily_Min), new Date(0)) });
	Client_account* cl_acc = new Client_account(info.clients_by_name_type["Donatello"]->get_id(), 10, 1);
	info.client_accounts_by_account.insert({ 10, cl_acc });
	info.client_accounts_by_client.insert({info.clients_by_name_type["Donatello"]->get_id(), cl_acc});
	info.client_accounts_by_deposit.insert({ 1, cl_acc });

	info.accounts.insert({ 20, new Account(20, new BString("debit"), new Money(50000), new BString("YUAN")) });
	info.deposits.insert({ 2, new Deposit(2, 0, get_debit_type_string(Compounded_Daily_Min), new Date(0)) });
	cl_acc = new Client_account(info.clients_by_name_type["Mike"]->get_id(), 20, 2);
	info.client_accounts_by_account.insert({ 20, cl_acc });
	info.client_accounts_by_client.insert({ info.clients_by_name_type["Mike"]->get_id(), cl_acc });
	info.client_accounts_by_deposit.insert({ 2, cl_acc });
	
	return info;
}

bank_info createCredit(Credit_type cr_type) {
	bank_info info = createSimpleConf();

	info.accounts.insert({11, new Account(11, new BString("credit"), new Money(500000), new BString("RUB"))});
	info.credits.insert({ 3, new Credit(3, 0.05, new Money(1000000), get_credit_type_string(cr_type))});
	Client_debt* debt = new Client_debt(1, 11, 3);
	info.client_debts_by_account.insert({ 11, debt });
	info.client_debts_by_client.insert({ 1, debt });
	info.client_debts_by_credit.insert({ 3, debt });
	return info;
}

bank_info createDeposit(Deposit_type dep_type) {
	bank_info info = createSimpleConf();

	info.accounts.insert({ 11, new Account(11, new BString("deposit"), new Money(100000), new BString("RUB")) });
	info.deposits.insert({ 3,  new Deposit(3, 0.05, get_debit_type_string(dep_type), new Date(0), 730)});
	Client_account* cl_acc = new Client_account(1, 11, 3);
	info.client_accounts_by_account.insert({ 11, cl_acc });
	info.client_accounts_by_client.insert({ 1, cl_acc });
	info.client_accounts_by_deposit.insert({ 3, cl_acc });

	info.accounts[11]->try_reduce_money(10000);
	info.accounts[11]->add_money(10000);

	return info;
}
