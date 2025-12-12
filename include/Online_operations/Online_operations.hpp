#pragma once
#include "Data_types.hpp"
#include "Order_book.hpp"
#include "Common_tools.hpp"
#include "Clients_operations/Client_operation_tools.hpp"

void transfer_between_accs_of_one_client(bank_info& info, Date* date, Time* time, ulong acc1_id, ulong acc2_id, Money* money);

void transfer_between_accs_of_other_client(bank_info& info, Date* date, Time* time, ulong acc1_id, ulong acc2_id, Money* money);

void add_money_from_another_bank(bank_info& info, Date* date, Time* time, ulong acc_id, Money* money);