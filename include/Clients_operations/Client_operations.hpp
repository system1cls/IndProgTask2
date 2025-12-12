#pragma once
#include "Client_operation_tools.hpp"
#include "Data_types.hpp"
#include "Order_book.hpp"
#include "Common_tools.hpp"

void print_acc_info(bank_info& info, Date* date, Time* time, string name, Client_type cl_type, ulong acc_ID);

void create_deposit(bank_info& info, Date* date, Time* time, string name, Client_type cl_type, Account_currency_type cur_type, Deposit_type debit_type, BString* period, Money* money);

void close_deposit(bank_info& info, Date* date, Time* time, string name, Client_type cl_type, ulong acc_ID);

void withdraw(bank_info& info, Date* date, Time* time, string name, Client_type cl_type, ulong acc_ID, Money* money);

void top_up(bank_info& info, Date* date, Time* time, string name, Client_type cl_type, ulong acc_ID, Money* money);

void create_credit(bank_info& info, Date* date, Time* time, string name, Client_type cl_type, Account_currency_type cur_type, Credit_type credit_type, Money* money);

void create_debit(bank_info& info, Date* date, Time* time, string name, Client_type cl_type, Account_currency_type cur_type);

void exchange_currency(bank_info& info, Date* date, Time* time, string name, Client_type cl_type, Account_currency_type from, Account_currency_type to, Money* money_to_transfer);