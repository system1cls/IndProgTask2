#pragma once

#include "Simple/Simple_data_types.hpp"

enum Account_type {
	debit,
	deposit,
	credit
};

Account_type get_account_type_enum(BString* str);

BString* get_account_type_string(Account_type type);