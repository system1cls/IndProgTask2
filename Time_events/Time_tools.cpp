#include "Time_events/Time_tools.hpp"

array<int, 12> days_in_month{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
array<int, 4> days_in_qouter{ 90, 91, 92, 92 };

int get_days_in_month(Date* date) {
	ulong day_in_year = date->get_date() % 365;

	for (auto cnt_d : days_in_month) {
		if (day_in_year < cnt_d) {
			return cnt_d;
		}
		day_in_year -= cnt_d;
	}

	//TODO:error;
	exit(EXIT_FAILURE);
}

int get_days_in_quoter(Date* date) {
	ulong day_in_year = date->get_date() % 365;

	for (auto cnt_q : days_in_qouter) {
		if (day_in_year < cnt_q) {
			return cnt_q;
		}
		day_in_year -= cnt_q;
	}

	//TODO:error;
	exit(EXIT_FAILURE);
}

int get_days_in_semi(Date* date) {
	ulong day_in_year = date->get_date() % 365;

	if (day_in_year < 182) return 182;
	return 183;
}