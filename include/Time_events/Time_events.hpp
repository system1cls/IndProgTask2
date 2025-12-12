#pragma once
#include "Data_types.hpp"
#include "Order_book.hpp"
#include "Init_bank.hpp"
#include "Common_tools.hpp"
#include <map>

class Time_events {
public:

	static void start_of_the_day(Date* date, Time* time, bank_info& info);

	static void end_of_the_day(Date* date, Time* time, bank_info& info);

	static void end_of_the_month(Date* date, Time* time, bank_info& info);

	static void end_of_the_Quater(Date* date, Time* time, bank_info& info);

	static void end_of_the_Semi(Date* date, Time* time, bank_info& info);

	static void end_of_the_year(Date* date, Time* time, bank_info& info);
};