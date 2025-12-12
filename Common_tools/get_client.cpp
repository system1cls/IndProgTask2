#include "Common_tools.hpp"

Client* get_client_by_acc(bank_info& info, Account* acc) {
	Account_type acc_t = get_account_type_enum(acc->get_type());
	if (acc_t == credit) {
		Client_debt* debt = info.client_debts_by_account[acc->get_ID()];
		return info.clients[debt->get_client_ID()];
	}

	Client_account* cl_acc = info.client_accounts_by_account[acc->get_ID()];
	return info.clients[cl_acc->get_client_ID()];
}

Client* get_client(bank_info& info, string name, Client_type type) {
	if (!info.clients_by_name_type.contains(name)) {
		//TODO:error;
		exit(EXIT_FAILURE);
	}

	auto it1 = info.clients_by_name_type.lower_bound(name);
	auto it2 = info.clients_by_name_type.upper_bound(name);


	for (auto it = it1; it != it2; it++) {
		Client_type real_type = get_client_type_enum(it->second->get_type());
		if (type == Legal_Entity || type == VIP_Legal_Entity) {
			if (real_type == Legal_Entity || real_type == VIP_Legal_Entity) {
				return it->second;
			}
		}
		else {
			if (real_type == Individual_Client || real_type == VIP_Individual_Client) {
				return it->second;
			}
		}
	}

	//TODO:error;
	exit(EXIT_FAILURE);
}