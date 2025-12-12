#include "Clients_operations/Client_operations.hpp"

void close_deposit(bank_info& info, Date* date, Time* time, string name, Client_type cl_type, ulong acc_ID) {
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
		fprintf(stderr, "Account closed\n");
		return;
	}

	if (get_account_type_enum(acc->get_type()) != debit) {
		fprintf(stderr, "unable to close\n");
		return;
	}

	Money tarif(max(10., acc->get_money() * 0.015));
	if (acc->get_money() < tarif.get_money()) {
		fprintf(stderr, "Client error. Negative balance on closure\n");
		return;
	}

	tranfer_money_to_bank_acc(date, time, info, acc, &tarif);

	acc->set_close();

	printf("%llu # %llu:%llu # Account closed %llu # %llu.%llu", date->get_date(), time->get_hours(), time->get_minutes(), acc->get_ID(), acc->get_ent_dec().first, acc->get_ent_dec().second);
}