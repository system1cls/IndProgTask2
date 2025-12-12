#pragma once

#include "Simple/Simple_data_types.hpp"

enum Credit_type
{
	Charged_Daily,
	Charged_Monthly,
	Charged_Quarterly,
	Charged_Semi_annually,
	Charged_Annually,
};

Credit_type get_credit_type_enum(BString* str);

BString* get_credit_type_string(Credit_type type);