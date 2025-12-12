#pragma once

#include "Simple/Simple_data_types.hpp"

enum Client_type {
	Individual_Client,
	Legal_Entity,
	VIP_Individual_Client,
	VIP_Legal_Entity,
	Not_a_Client
};

Client_type get_client_type_enum(BString* str);

BString* get_client_type_string(Client_type type);