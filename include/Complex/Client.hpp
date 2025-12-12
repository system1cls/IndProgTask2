#pragma once

#include "Simple/Simple_data_types.hpp"
#include "Enums/Enums.hpp"

class Client {
private:
	ulong ID;
	BString* name;
	BString* type;
	char cnt_accs[4];


public:

	Client(ulong ID, BString* name, BString* type);

	ulong get_id() const;
	BString* get_name() const;
	BString* get_type() const;
	
	bool try_add_acc(Account_currency_type type);

	~Client();
};