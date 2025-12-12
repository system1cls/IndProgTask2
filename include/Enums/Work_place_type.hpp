#pragma once

#include "Simple/Simple_data_types.hpp"

enum Work_place_type {
	Client_Manager,
	Cash_Desk,
	Currency_Exchange,
	VIP_Client_Manager,
};

Work_place_type get_work_place_type_enum(BString* str);

BString* get_work_place_type_string(Work_place_type type);