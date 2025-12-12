#include "Enums/Deposit_type.hpp"



Deposit_type get_debit_type_enum(BString* str) {

	if (strcmp(str->str, "Compounded_Daily_Remaining") == 0) {
		return Compounded_Daily_Remaining;
	}

	if (strcmp(str->str, "Compounded_Daily_Min") == 0) {
		return Compounded_Daily_Min;
	}

	if (strcmp(str->str, "Compounded_Monthly_Remaining") == 0) {
		return Compounded_Monthly_Remaining;
	}

	if (strcmp(str->str, "Compounded_Monthly_Min") == 0) {
		return Compounded_Monthly_Min;
	}

	if (strcmp(str->str, "Compounded_Quarterly_Remaining") == 0) {
		return Compounded_Quarterly_Remaining;
	}

	if (strcmp(str->str, "Compounded_Quarterly_Min") == 0) {
		return Compounded_Quarterly_Min;
	}

	if (strcmp(str->str, "Compounded_Semi_Annually_Remaining") == 0) {
		return Compounded_Semi_Annually_Remaining;
	}

	if (strcmp(str->str, "Compounded_Semi_Annually_Min") == 0) {
		return Compounded_Semi_Annually_Min;
	}

	if (strcmp(str->str, "Compounded_Annually_Remaining") == 0) {
		return Compounded_Annually_Remaining;
	}

	if (strcmp(str->str, "Compounded_Annually_Min") == 0) {
		return Compounded_Annually_Min;
	}

	//TODO:error;
	exit(EXIT_FAILURE);
}

BString* get_debit_type_string(Deposit_type type) {
	switch (type) {
	case Compounded_Daily_Remaining:
		return new BString("Compounded_Daily_Remaining");
	
	case Compounded_Daily_Min:
		return new BString("Compounded_Daily_Min");
	
	case Compounded_Monthly_Remaining:
		return new BString("Compounded_Monthly_Remaining");
	
	case Compounded_Monthly_Min:
		return new BString("Compounded_Monthly_Min");
	
	case Compounded_Quarterly_Remaining:
		return new BString("Compounded_Quarterly_Remaining");
	
	case Compounded_Quarterly_Min:
		return new BString("Compounded_Quarterly_Min");
	
	case Compounded_Semi_Annually_Remaining:
		return new BString("Compounded_Semi_Annually_Remaining");
	
	case Compounded_Semi_Annually_Min:
		return new BString("Compounded_Semi_Annually_Min");

	case Compounded_Annually_Remaining:
		return new BString("Compounded_Annually_Remaining");

	case Compounded_Annually_Min:
		return new BString("Compounded_Annually_Min");

	default:
		//TODO:error
		exit(EXIT_FAILURE);
	}
}