#include "Complex/Client_debt.hpp"

Client_debt::Client_debt(ulong client_ID, ulong Account_ID, ulong Credit_ID) {
	this->client_ID = client_ID;
	this->account_ID = Account_ID;
	this->credit_ID = Credit_ID;
}

ulong Client_debt::get_client_ID() {
	return this->client_ID;
}

ulong Client_debt::get_account_ID() {
	return this->account_ID;
}

ulong Client_debt::get_credit_ID() {
	return this->credit_ID;
}