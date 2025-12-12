#include "Clients_operations/Client_operations.hpp"

void top_up(bank_info& info, Date* date, Time* time, string name, Client_type cl_type, ulong acc_ID, Money* money) {
	Client* client = get_client(info, name, cl_type);
	Account* acc = get_acc(info, acc_ID);
	if (acc == nullptr) {
		fprintf(stderr, "Client error. Unknown account\n");
		return;
	}

	if (!check_if_client_owns_acc(info, client, acc)) {
		fprintf(stderr, "Client error. Access denied\n");
		return;
	}

	if (acc->is_close()) {
		fprintf(stderr, "Client error. Account closed\n");
		return;
	}

	if (get_account_type_enum(acc->get_type()) != debit) {
		fprintf(stderr, "Client error. Unable to top up\n");
		return;
	}

	Money tarif(max(1., money->get_money() * 0.0001));
	acc->add_money(money->get_money());

	tranfer_money_to_bank_acc(date, time, info, acc, &tarif);

	info.analyzer.add_transaction(date, time, money, info.gen.gen(), acc->get_ID());
	printf("%llu # %llu:%llu # Fonds Credited %llu # %llu.%llu", date->get_date(), time->get_hours(), time->get_minutes(), acc->get_ID(), acc->get_ent_dec().first, acc->get_ent_dec().second);
}