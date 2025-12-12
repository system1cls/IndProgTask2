#include "Enums/Work_place_type.hpp"

Work_place_type get_work_place_type_enum(BString* str) {
	if (strcmp(str->str, "Client_Manager") == 0) {
		return Work_place_type::Client_Manager;
	}

	if (strcmp(str->str, "Cash_Desk") == 0) {
		return Work_place_type::Cash_Desk;
	}

	if (strcmp(str->str, "Currency_Exchange") == 0) {
		return Work_place_type::Currency_Exchange;
	}

	if (strcmp(str->str, "VIP_Client_Manager") == 0) {
		return Work_place_type::VIP_Client_Manager;
	}

	//TODO:error;
	exit(EXIT_FAILURE);
}

BString* get_work_place_type_string(Work_place_type type) {
	switch (type) {
	case Client_Manager:
		return new BString("Client_Manager");

	case Cash_Desk:
		return new BString("Cash_Desk");

	case Currency_Exchange:
		return new BString("Currency_Exchange");

	case VIP_Client_Manager:
		return new BString("VIP_Client_Manager");

	default:
		//TODO:error
		exit(EXIT_FAILURE);
	}
}