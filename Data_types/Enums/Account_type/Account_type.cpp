#include "Enums/Account_type.hpp"

Account_type get_account_type_enum(BString* str) {
	if (strcmp(str->str, "debit") == 0) {
		return debit;
	}

	if (strcmp(str->str, "deposit") == 0) {
		return deposit;
	}

	if (strcmp(str->str, "credit") == 0) {
		return credit;
	}

	//TODO:error
	exit(EXIT_FAILURE);
}

BString* get_account_type_string(Account_type type) {


	switch (type) {
	case debit:
		return new BString("debit");
	case deposit:
		return new BString("deposit");
	case credit:
		return new BString("credit");
	default:

		//TODO:error;
		exit(EXIT_FAILURE);
	}
}
