#include "Common_tools.hpp"

bool check_if_more_then_credit(bank_info& info, Account* acc, Money* money) {
	Credit* credit = info.credits[info.client_debts_by_account[acc->get_ID()]->get_credit_ID()];
	return credit->get_money_was_lended() < money->get_money() + acc->get_money();
}