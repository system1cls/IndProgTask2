#include "Order_book.hpp"

void Order_book::log_transist(Date* date, Time* time, ulong from_ID, ulong to_ID, Money* money) {
	pair<ulong, ulong> ent_dec = money->get_ent_dec();

	fprintf(stderr, "%llu # %llu:%llu # %llu -> %llu # %llu.%llu\n", 
		date->get_date(), time->get_hours(), time->get_minutes(), from_ID, to_ID, ent_dec.first, ent_dec.second);
}

void Order_book::log_replenishment(Date* date, Time* time, ulong ID, Money* money) {
	pair<ulong, ulong> ent_dec = money->get_ent_dec();

	fprintf(stderr, "%llu # %llu:%llu # -> %llu # %llu.%llu\n", 
		date->get_date(), time->get_hours(), time->get_minutes(), ID, ent_dec.first, ent_dec.second);
}

void Order_book::log_withdrawal(Date* date, Time* time, ulong ID, Money* money) {
	pair<ulong, ulong> ent_dec = money->get_ent_dec();

	fprintf(stderr, "%llu # %llu:%llu # %llu -> # %llu.%llu\n",
		date->get_date(), time->get_hours(), time->get_minutes(), ID, ent_dec.first, ent_dec.second);
}

