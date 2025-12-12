#pragma once
#include "Data_types.hpp"
#include <vector>
#include <random>

bool try_reserve(bank_info& info, Account_currency_type cur_type, double money_need, ulong acc_id);

bool check_if_operation_on_deposit_in_period(bank_info& info, Account* acc);

bool check_if_operation_on_deposit_in_period(bank_info& info, Client* cl);

bool check_if_operation_on_deposit_in_period(bank_info& info, Deposit* deposit);

Client* get_client_by_acc(bank_info& info, Account* acc);

Client* get_client(bank_info& info, string name, Client_type type);

bool check_if_more_then_credit(bank_info& info, Account* acc, Money* money);

bool check_string_by_scheme(string input, string scheme);

string delete_spaces_from_start_and_end(string str);

bool try_reduce_money_from_bank_acc(bank_info& info, Account_currency_type type, double money_to_reduce);

ulong add_money_to_bank_acc(bank_info& info, Account_currency_type type, double money);
