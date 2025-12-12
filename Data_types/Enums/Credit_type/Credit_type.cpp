#include "Enums/Credit_type.hpp"

Credit_type get_credit_type_enum(BString* str) {
	if (strcmp(str->str, "Charged_Daily") == 0) {
		return Credit_type::Charged_Daily;
	}

	if (strcmp(str->str, "Charged_Monthly") == 0) {
		return Credit_type::Charged_Monthly;
	}

	if (strcmp(str->str, "Charged_Quarterly") == 0) {
		return Credit_type::Charged_Quarterly;
	}

	if (strcmp(str->str, "Charged_Semi_annually") == 0) {
		return Credit_type::Charged_Semi_annually;
	}
	
	if (strcmp(str->str, "Charged_Annually") == 0) {
		return Credit_type::Charged_Annually;
	}

	//TODO:error;
	exit(EXIT_FAILURE);
}

BString* get_credit_type_string(Credit_type type) {
	switch (type) {
	case Charged_Daily:
		return new BString("Charged_Daily");
	
	case Charged_Monthly:
		return new BString("Charged_Monthly");
	
	case Charged_Quarterly:
		return new BString("Charged_Quarterly");
	
	case Charged_Semi_annually:
		return new BString("Charged_Semi_annually");
	
	case Charged_Annually:
		return new BString("Charged_Annually");

	default:
		//TODO:error
		exit(EXIT_FAILURE);
	}
}