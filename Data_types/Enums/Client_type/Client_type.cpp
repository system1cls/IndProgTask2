#include "Enums/Client_type.hpp"

Client_type get_client_type_enum(BString* str) {
	if (strcmp(str->str, "Individual_Client") == 0 || strcmp(str->str, "Individual") == 0) {
		return Client_type::Individual_Client;
	}

	if (strcmp(str->str, "Legal_Entity") == 0) {
		return Client_type::Legal_Entity;
	}

	if (strcmp(str->str, "VIP_Individual_Client") == 0 || strcmp(str->str, "VIP_Individual") == 0) {
		return Client_type::VIP_Individual_Client;
	}

	if (strcmp(str->str, "VIP_Legal_Entity") == 0) {
		return Client_type::VIP_Legal_Entity;
	}

	if (strcmp(str->str, "Not_a_Client") == 0) {
		return Client_type::Not_a_Client;
	}

	//TODO:error
	exit(EXIT_FAILURE);
}

BString* get_client_type_string(Client_type type) {
	switch (type) {
	case Individual_Client:
		return new BString("Individual_Client");
	
	case Legal_Entity:
		return new BString("Legal_Entity");
	
	case VIP_Individual_Client:
		return new BString("VIP_Individual_Client");
	
	case VIP_Legal_Entity:
		return new BString("VIP_Legal_Entity");
	
	case Not_a_Client:
		return new BString("Not_a_Client");
	
	default:
		//TODO:error;
		exit(EXIT_FAILURE);
	}
}