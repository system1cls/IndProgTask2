#include "Common_tools.hpp"

bool check_if_operation_on_deposit_in_period(bank_info& info, Account* acc) {
	Client_account* cl_acc = info.client_accounts_by_account[acc->get_ID()];
	Deposit* deposit = info.deposits[cl_acc->get_debit_ID()];
	return check_if_operation_on_deposit_in_period(info, deposit);
}

bool check_if_operation_on_deposit_in_period(bank_info& info, Client* cl) {
	Client_account* cl_acc = info.client_accounts_by_account[cl->get_id()];
	Deposit* deposit = info.deposits[cl_acc->get_debit_ID()];
	return check_if_operation_on_deposit_in_period(info, deposit);
}

bool check_if_operation_on_deposit_in_period(bank_info& info, Deposit* deposit) {
	return deposit->get_days_of_duration() > 0;
}
