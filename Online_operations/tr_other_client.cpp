#include "Online_operations/Online_operations.hpp"


bool transfer_in_one_cur(bank_info& info, Account* acc1, Account* acc2, Money* money) {
	if (get_account_type_enum(acc2->get_type()) == credit && check_if_more_then_credit(info, acc2, money)) {
		fprintf(stderr, "Incorrect online operation. Invalid loan payment amount\n");
		return false;
	}

	if (!acc1->try_reduce_money(money->get_money())) {
		fprintf(stderr, "Incorrect online operation. Insufficient funds\n");
		return false;
	}

	acc2->add_money(money->get_money());
	return true;
}

bool transfer_in_other_cur(bank_info& info, Account* acc1, Account* acc2, Money* money, Account_currency_type cur1, Account_currency_type cur2) {
	Exchange_info* ex_info = info.exchanges[{cur1, cur2}];

	Money money_transformed(money->get_money() * ex_info->get_coef());

	if (get_account_type_enum(acc2->get_type()) == credit && check_if_more_then_credit(info, acc2, &money_transformed)) {
		fprintf(stderr, "Incorrect online operation. Invalid loan payment amount\n");
		return false;
	}

	if (acc1->get_money() < money->get_money()) {
		fprintf(stderr, "Incorrect online operation. Insufficient funds\n");
		return false;
	}

	Client* client = get_client_by_acc(info, acc1);
	Client_type cl_t = get_client_type_enum(client->get_type());
	bool is_VIP = (cl_t == VIP_Individual_Client || cl_t == VIP_Legal_Entity);

	Money tarif(0);
	
	if (!is_VIP) {
		double max_free_trans;

		switch (cur1) {
		case RUB:
			max_free_trans = 100000;
			break;
		case YUAN:
			max_free_trans = 10000;
			break;
		case USD:
		case EUR:
			max_free_trans = 1000;
			break;
		}

		double tarif_d = max(money->get_money() * 0.01 - max((max_free_trans - acc1->get_money_transfered_in_month()), 0.), 0.);
		acc1->add_money_transfered_in_month(money->get_money());
		tarif.set_money(tarif_d);
	}

	if (!try_reduce_money_from_bank_acc(info, cur2, money_transformed.get_money())) {
		fprintf(stderr, "Incorrect online operation. Can’t perform exchange\n");
		return false;
	}

	if (!acc1->try_reduce_money(money->get_money() + tarif.get_money())) {
		fprintf(stderr, "Incorrect online operation. Insufficient funds\n");
		return false;
	}


	ulong b_id = add_money_to_bank_acc(info, cur1, money->get_money() + tarif.get_money());

	acc2->add_money(money_transformed.get_money());
	return true;
}

void transfer_between_accs_of_other_client(bank_info& info, Date* date, Time* time, ulong acc1_id, ulong acc2_id, Money* money) {
	Account* acc1 = get_acc(info, acc1_id);
	Account* acc2 = get_acc(info, acc2_id);
	if (acc1 == nullptr || acc2 == nullptr) {
		fprintf(stderr, "Incorrect online operation. Unknown account");
		return;
	}

	Account_type acc1_t = get_account_type_enum(acc1->get_type());
	Account_type acc2_t = get_account_type_enum(acc2->get_type());

	if (acc1_t == deposit && check_if_operation_on_deposit_in_period(info, acc1)) {
		fprintf(stderr, "Incorrect online operation. Unnable to transfer money from deposit without ending of period");
		return;
	}

	if (acc2_t == deposit && check_if_operation_on_deposit_in_period(info, acc2)) {
		fprintf(stderr, "Incorrect online operation. Unnable to transfer money from deposit without ending of period");
		return;
	}


	Account_currency_type cur1 = get_account_currency_type_enum(acc1->get_currency());
	Account_currency_type cur2 = get_account_currency_type_enum(acc2->get_currency());

	if (cur1 == cur2) {
		if (!transfer_in_one_cur(info, acc1, acc2, money)) {
			return;
		}
	}
	else {
		if (!transfer_in_other_cur(info, acc1, acc2, money, cur1, cur2)) {
			return;
		}
	}

	info.analyzer.add_transaction(date, time, money, info.gen.gen(), acc1->get_ID(), acc2->get_ID());
	Order_book::log_transist(date, time, acc1_id, acc2_id, money);
	printf("%llu # %llu:%llu # Online Transfer Approved %llu -> %llu", date->get_date(), time->get_hours(), time->get_minutes(), acc1_id, acc2_id);
}
