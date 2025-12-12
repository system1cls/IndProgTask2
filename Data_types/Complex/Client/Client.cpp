#include "Complex/Client.hpp"

Client::Client(ulong ID, BString* name, BString* type) {
	this->ID = ID;
	this->name = name;
	this->type = type;
	for (int i = 0; i < 4; i++) {
		this->cnt_accs[0] = 0;
	}
}

ulong Client::get_id() const {
	return this->ID;
}

BString* Client::get_name() const {
	return this->name;
}

BString* Client::get_type() const {
	return this->type;
}

unsigned char get_max_in_RUB(Client_type cl_type) {
	switch (cl_type) {
	case Individual_Client:
		return 3;
	case VIP_Individual_Client:
		return 5;
	case Legal_Entity:
		return 10;
	case VIP_Legal_Entity:
		return 25;
	default:
		return 0;
	}
}

unsigned char get_max_in_YUAN(Client_type cl_type) {
	switch (cl_type) {
	case Individual_Client:
		return 1;
	case VIP_Individual_Client:
		return 5;
	case Legal_Entity:
		return 5;
	case VIP_Legal_Entity:
		return 15;
	default:
		return 0;
	}
}

unsigned char get_max_in_USD(Client_type cl_type) {
	switch (cl_type) {
	case Individual_Client:
		return 1;
	case VIP_Individual_Client:
		return 3;
	case Legal_Entity:
		return 5;
	case VIP_Legal_Entity:
		return 10;
	default:
		return 0;
	}
}

unsigned char get_max_in_EUR(Client_type cl_type) {
	switch (cl_type) {
	case Individual_Client:
		return 1;
	case VIP_Individual_Client:
		return 3;
	case Legal_Entity:
		return 5;
	case VIP_Legal_Entity:
		return 10;
	default:
		return 0;
	}
}

bool Client::try_add_acc(Account_currency_type type) {
	unsigned char acc_max;
	Client_type cl_type = get_client_type_enum(this->get_type());
	switch (type) {
	case RUB:
		acc_max = get_max_in_RUB(cl_type);
		if (cnt_accs[0] < acc_max) {
			cnt_accs[0]++;
			return true;
		}
		return false;

	case YUAN:
		acc_max = get_max_in_YUAN(cl_type);
		if (cnt_accs[1] < acc_max) {
			cnt_accs[1]++;
			return true;
		}
		return false;
	case USD:
		acc_max = get_max_in_USD(cl_type);
		if (cnt_accs[2] < acc_max) {
			cnt_accs[2]++;
			return true;
		}
		return false;
	case EUR:
		acc_max = get_max_in_EUR(cl_type);
		if (cnt_accs[3] < acc_max) {
			cnt_accs[3]++;
			return true;
		}
		return false;
	default:
		return false;
	}

}

Client::~Client() {
	if (this->name != nullptr) delete this->name;
	if (this->type != nullptr) delete this->type;
}