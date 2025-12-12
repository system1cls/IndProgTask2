#include "Enums/Account_currency_type.hpp"

Account_currency_type get_account_currency_type_enum(BString* str) {
	if (strcmp(str->str, "RUB") == 0) {
		return RUB;
	}

	if (strcmp(str->str, "YUAN") == 0) {
		return YUAN;
	}

	if (strcmp(str->str, "USD") == 0) {
		return USD;
	}

	if (strcmp(str->str, "EUR") == 0) {
		return EUR;
	}

	//TODO:error;
	exit(EXIT_FAILURE);
}

BString* get_account_currency_type_str(Account_currency_type type) {
	switch (type) {
	case RUB:
		return new BString("RUB");
	case YUAN:
		return new BString("YUAN");
	case USD:
		return new BString("USD");
	case EUR:
		return new BString("EUR");
	default:
		//TODO: error;
		exit(EXIT_FAILURE);
	}
}