#include "Online_operations/Online_operations.hpp"

void add_money_from_another_bank(bank_info& info, Date* date, Time* time, ulong acc_id, Money* money) {
	Account* acc = get_acc(info, acc_id);
	if (acc == nullptr) {
		fprintf(stderr, "Incorrect online operation. Unknown account\n");
		return;
	}

	if (get_account_type_enum(acc->get_type()) == credit && check_if_more_then_credit(info, acc, money)) {
		fprintf(stderr, "Incorrect online operation. Invalid loan payment amount\n");
		return;
	}

	acc->add_money(money->get_money());

	info.analyzer.add_transaction(date, time, money, info.gen.gen(), acc->get_ID());
	printf("%llu # %llu:%llu # Online Inbound Transfer Approved %llu\n", date->get_date(), time->get_hours(), time->get_minutes(), acc_id);
}