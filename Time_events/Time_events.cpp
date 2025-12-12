#include "Time_events/Time_tools.hpp"
#include "Time_events/Time_events.hpp"


void Time_events::start_of_the_day(Date* date, Time* time, bank_info& info) {
	info.date.set_date(date->get_date());
	info.time.set_time(time->get_hours(), time->get_minutes());
}

double get_money_to_transfer_credit(Date* date, Credit* credit, Credit_type type) {
	switch (type) {
	case Charged_Daily:
		return max(0., credit->get_money_was_lended() - credit->get_money_payed()) * credit->get_interest_rate() / 365;
	
	case Charged_Monthly:
		return max(0., credit->get_money_was_lended() - credit->get_money_payed()) * credit->get_interest_rate() / 365 * get_days_in_month(date);
		
	case Charged_Quarterly:
		return max(0., credit->get_money_was_lended() - credit->get_money_payed()) * credit->get_interest_rate() / 365 * get_days_in_quoter(date);
		
	case Charged_Semi_annually:
		return max(0., credit->get_money_was_lended() - credit->get_money_payed()) * credit->get_interest_rate() / 365 * get_days_in_semi(date);
		
	case Charged_Annually:
		return max(0., credit->get_money_was_lended() - credit->get_money_payed()) * credit->get_interest_rate();
		
	default:
		//TODO:error;
		exit(EXIT_FAILURE);
	}
}

void do_credit(Date* date, Time* time, bank_info& info, Credit_type type) {
	for (auto ID_credit = info.credits.begin(); ID_credit != info.credits.end(); ID_credit++) {
		Credit* credit = ID_credit->second;

		if (get_credit_type_enum(credit->get_type()) == type) {
			ulong credit_ID = credit->get_ID();

			ulong acc_id = info.client_debts_by_credit[credit_ID]->get_account_ID();

			Account* client_acc = info.accounts.at(acc_id);

			if (client_acc->is_close())
				continue;

			Account_currency_type currency_type = get_account_currency_type_enum(client_acc->get_currency());

			double money_to_reduce = get_money_to_transfer_credit(date, credit, type);

			bool is_succesful = client_acc->try_reduce_money(money_to_reduce);

			if (!is_succesful) {
				//TODO:error;
				exit(EXIT_FAILURE);
			}

			ulong b_id = add_money_to_bank_acc(info, currency_type, money_to_reduce);

			if (abs(credit->get_money_payed() - credit->get_money_was_lended()) < 0.001) {
				client_acc->set_close();
			}

			Money _money(money_to_reduce);

			info.analyzer.add_transaction(&info.date, &info.time, &_money, info.gen.gen(), client_acc->get_ID(), b_id);
			Order_book::log_withdrawal(date, time, credit_ID, &_money);
		}
	}
}

double get_money_to_transfer_debit(Date* date, Account* client, Deposit* debit, Deposit_type type) {
	switch (type) {
	case Compounded_Daily_Remaining:
		return client->get_virtual_money() * debit->get_interest_rate() / 365;
	case Compounded_Daily_Min:
		return client->get_min_money_dayly() * debit->get_interest_rate() / 365;
	case Compounded_Monthly_Remaining:
		return client->get_virtual_money() * debit->get_interest_rate() / 365 * get_days_in_month(date);
	case Compounded_Monthly_Min:
		return client->get_min_money_monthly() * debit->get_interest_rate() / 365 * get_days_in_month(date);
	case Compounded_Quarterly_Remaining:
		return client->get_virtual_money() * debit->get_interest_rate() / 365 * get_days_in_quoter(date);
	case Compounded_Quarterly_Min:
		return client->get_min_money_Quater() * debit->get_interest_rate() / 365 * get_days_in_quoter(date);
	case Compounded_Semi_Annually_Remaining:
		return client->get_virtual_money() * debit->get_interest_rate() / 365 * get_days_in_semi(date);
	case Compounded_Semi_Annually_Min:
		return client->get_min_money_Semi() * debit->get_interest_rate() / 365 * get_days_in_semi(date);
	case Compounded_Annually_Remaining:
		return client->get_virtual_money() * debit->get_interest_rate();
	case Compounded_Annually_Min:
		return client->get_min_money_year() * debit->get_interest_rate();

	default:
		//TODO:error;
		exit(EXIT_FAILURE);
	}
}

void do_debit(Date* date, Time* time, bank_info& info, Deposit_type type) {
	for (auto ID_debit = info.deposits.begin(); ID_debit != info.deposits.end(); ID_debit++) {
		Deposit* deposit = ID_debit->second;

		if (get_debit_type_enum(deposit->get_type()) == type && deposit->get_interest_rate() > 0.) {
			ulong deposit_ID = deposit->get_ID();
			Client_account* cl_acc = info.client_accounts_by_deposit[deposit_ID];
			Account* client_acc = info.accounts.at(cl_acc->get_account_ID());
			if (client_acc->is_close() || get_account_type_enum(client_acc->get_type()) == debit) {
				continue;
			}

			Account_currency_type currency_type = get_account_currency_type_enum(client_acc->get_currency());

			

			double money_to_transfer = get_money_to_transfer_debit(date, client_acc, deposit, type);

			if (!try_reduce_money_from_bank_acc(info, currency_type, money_to_transfer)) {
				if (!try_reserve(info, currency_type, money_to_transfer, client_acc->get_ID())) {
					fprintf(stderr, "Bank defaulted");
					exit(EXIT_FAILURE);
				}
			}

			client_acc->add_money(money_to_transfer);

			Money _money(money_to_transfer);
			Order_book::log_replenishment(date, time, client_acc->get_ID(), &_money);
			

			if ((type == Compounded_Daily_Min || type == Compounded_Daily_Remaining) && get_account_type_enum(client_acc->get_type()) == Account_type::deposit && deposit->get_days_of_duration() > 0) {

				if (deposit->get_days_of_duration() == 0) {
					if (client_acc->money_to_be_returned() > 0) {
						Money money_to_be_returned(client_acc->money_to_be_returned());
						if (!try_reduce_money_from_bank_acc(info, currency_type, money_to_be_returned.get_money())) {
							if (!try_reserve(info, get_account_currency_type_enum(client_acc->get_currency()), money_to_be_returned.get_money(), client_acc->get_ID())) {
								fprintf(stderr, "Bank defaulted");
								exit(EXIT_FAILURE);
							}
						}
						client_acc->return_reserve_money();
					}
				}
			}

			info.analyzer.add_transaction(&info.date, &info.time, &_money, info.gen.gen(), client_acc->get_ID());
		}
	}
}

void do_credit_dayly(Date* date, Time* time, bank_info& info) {
	do_credit(date, time, info, Charged_Daily);
}

void do_debit_dayly(Date* date, Time* time, bank_info& info) {
	do_debit(date, time, info, Compounded_Daily_Remaining);
	do_debit(date, time, info, Compounded_Daily_Min);
}

void print_work_stat_day(Date* date, bank_info& info) {
	for (auto type_place : info.work_places) {
		Work_place* place = type_place.second;
		place->end_day(date);
	}
}

void Time_events::end_of_the_day(Date* date, Time* time, bank_info& info) {

	do_credit_dayly(date, time, info);
	do_debit_dayly(date, time, info);
	print_work_stat_day(date, info);
}

void do_credit_monthly(Date* date, Time* time, bank_info& info) {
	do_credit(date, time, info, Charged_Monthly);
}

void do_debit_monthly(Date* date, Time* time, bank_info& info) {
	do_debit(date, time, info, Compounded_Monthly_Remaining);
	do_debit(date, time, info, Compounded_Monthly_Min);
}

void null_money_transf(bank_info& info) {
	for (auto acc : info.accounts) {
		acc.second->null_money_transfered_in_month();
	}
}

void Time_events::end_of_the_month(Date* date, Time* time, bank_info& info) {
	Time_events::end_of_the_day(date, time, info);

	do_credit_monthly(date, time, info);
	do_debit_monthly(date, time, info);
	null_money_transf(info);
}

void do_credit_quater(Date* date, Time* time, bank_info& info) {
	do_credit(date, time, info, Charged_Quarterly);
}

void do_debit_quater(Date* date, Time* time, bank_info& info) {
	do_debit(date, time, info, Compounded_Quarterly_Remaining);
	do_debit(date, time, info, Compounded_Quarterly_Min);
}

void Time_events::end_of_the_Quater(Date* date, Time* time, bank_info& info) {
	Time_events::end_of_the_month(date, time, info);

	do_credit_quater(date, time, info);
	do_debit_quater(date, time, info);
}

void do_credit_semi(Date* date, Time* time, bank_info& info) {
	do_credit(date, time, info, Charged_Semi_annually);
}

void do_debit_semi(Date* date, Time* time, bank_info& info) {
	do_debit(date, time, info, Compounded_Semi_Annually_Remaining);
	do_debit(date, time, info, Compounded_Semi_Annually_Min);
}

void Time_events::end_of_the_Semi(Date* date, Time* time, bank_info& info) {
	Time_events::end_of_the_Quater(date, time, info);

	do_credit_semi(date, time, info);
	do_debit_semi(date, time, info);
}

void do_credit_year(Date* date, Time* time, bank_info& info) {
	do_credit(date, time, info, Charged_Annually);
}

void do_debit_year(Date* date, Time* time, bank_info& info) {
	do_debit(date, time, info, Compounded_Annually_Remaining);
	do_debit(date, time, info, Compounded_Annually_Min);
}

void print_work_stat_year(Date* date, bank_info& info) {
	for (auto type_place : info.work_places) {
		Work_place* place = type_place.second;
		place->end_year(date);
	}
}

void Time_events::end_of_the_year(Date* date, Time* time, bank_info& info) {
	Time_events::end_of_the_Semi(date, time, info);

	do_credit_year(date, time, info);
	do_debit_year(date, time, info);
	print_work_stat_year(date, info);
}