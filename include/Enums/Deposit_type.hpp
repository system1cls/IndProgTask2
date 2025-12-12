#pragma once

#include "Simple/Simple_data_types.hpp"

enum Deposit_type
{
	Compounded_Daily_Remaining,
	Compounded_Daily_Min,
	Compounded_Monthly_Remaining,
	Compounded_Monthly_Min,
	Compounded_Quarterly_Remaining,
	Compounded_Quarterly_Min,
	Compounded_Semi_Annually_Remaining,
	Compounded_Semi_Annually_Min,
	Compounded_Annually_Remaining,
	Compounded_Annually_Min
};

Deposit_type get_debit_type_enum(BString* str);

BString* get_debit_type_string(Deposit_type type);