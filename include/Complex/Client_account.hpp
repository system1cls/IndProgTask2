#pragma once

#include "Simple/Simple_data_types.hpp"
#include "Enums/Enums.hpp"

class Client_account {
private:
	ulong client_ID;
	ulong account_ID;
	ulong debit_ID;

public:

	Client_account(ulong client_ID, ulong account_ID, ulong contribution_ID);

	ulong get_client_ID();
	ulong get_account_ID();
	ulong get_debit_ID();


};