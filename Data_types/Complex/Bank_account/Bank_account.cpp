#include "Complex/Bank_account.hpp"

Bank_account::Bank_account(ulong account_ID) {
	this->account_ID = account_ID;
}

ulong Bank_account::get_account_ID() const {
	return this->account_ID;
}