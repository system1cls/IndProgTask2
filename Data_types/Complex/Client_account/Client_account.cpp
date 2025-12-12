#include "Complex/Client_account.hpp"

Client_account::Client_account(ulong client_ID, ulong account_ID, ulong debit_ID) {
	this->client_ID = client_ID;
	this->account_ID = account_ID;
	this->debit_ID = debit_ID;
}

ulong Client_account::get_client_ID() {
	return this->client_ID;
}

ulong Client_account::get_account_ID() {
	return this->account_ID;
}

ulong Client_account::get_debit_ID() {
	return this->debit_ID;
}
