#pragma once

#include "Data_types.hpp"
#include "Order_book.hpp"
#include "Common_tools.hpp"

Account* get_acc(bank_info& info, ulong acc_ID);

bool check_if_client_owns_acc(bank_info& info, Client* client, Account* acc);

void tranfer_money_to_bank_acc(Date* date, Time* time, bank_info& info, Account* from, Money* money);