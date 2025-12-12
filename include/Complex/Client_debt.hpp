#pragma once

#include "Simple/Simple_data_types.hpp"
#include "Enums/Enums.hpp"

class Client_debt {
private:
	ulong client_ID;
	ulong account_ID;
	ulong credit_ID;

public:

	Client_debt(ulong client_ID, ulong Account_ID, ulong Credit_ID);

	ulong get_client_ID();
	ulong get_account_ID();
	ulong get_credit_ID();
};