#pragma once
#include "Data_types.hpp"

class Order_book {
public:

	static void log_transist(Date* date, Time* time, ulong from_ID, ulong to_ID, Money* money);

	static void log_replenishment(Date* date, Time* time, ulong ID, Money* money);

	static void log_withdrawal(Date* date, Time* time, ulong ID, Money* money);
};