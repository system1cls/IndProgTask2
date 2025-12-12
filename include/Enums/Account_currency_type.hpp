#pragma once

#include "Simple/Simple_data_types.hpp"

enum Account_currency_type {
	RUB,
	YUAN,
	USD,
	EUR
};

Account_currency_type get_account_currency_type_enum(BString* str);

BString* get_account_currency_type_str(Account_currency_type type);