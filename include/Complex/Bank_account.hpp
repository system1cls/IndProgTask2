#pragma once

#include "Simple/Simple_data_types.hpp"
#include "Enums/Enums.hpp"


class Bank_account {
private:
	ulong account_ID;

public:
	Bank_account(ulong account_ID);

	ulong get_account_ID() const;
};