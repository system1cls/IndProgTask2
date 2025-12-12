#include "Clients_operations/Client_operations.hpp"

void exchange_currency(bank_info& info, Date* date, Time* time, string name, Client_type cl_type, Account_currency_type from, Account_currency_type to, Money* money_to_transfer) {
	Exchange_info* ex_info = info.exchanges[{from, to}];
	Money money_to_send(money_to_transfer->get_money() * ex_info->get_coef());
	
	if (!try_reduce_money_from_bank_acc(info, to, money_to_send.get_money())) {
		fprintf(stderr, "Can’t perform exchange");
		return;
	}

	add_money_to_bank_acc(info, from, money_to_transfer->get_money());


	printf("%llu # %llu:%llu # Currency Exchange Performed # %llu.%llu\n", date->get_date(), time->get_hours(), time->get_minutes(), money_to_send.get_ent_dec().first, money_to_send.get_ent_dec().second);
}
