#include "Clients_operations/Client_operations.hpp"


void print_acc_info(bank_info& info, Date* date, Time* time, string name, Client_type cl_type, ulong acc_ID) {
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

	pair<ulong, ulong> money_pair = acc->get_ent_dec();

	printf("%llu # %llu:%llu # Balance of %llu # %llu.%llu", date->get_date(), time->get_hours(), time->get_minutes(), acc->get_ID(), money_pair.first, money_pair.second);
}