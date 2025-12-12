#include <gtest/gtest.h>
#include "tests/loadConfigs.hpp"


TEST(TestOffline, testCloseDeposit) {
	bank_info info = createSimpleConf();

	close_deposit(info, new Date(0), new Time(0, 0), "Donatello", Client_type::Individual_Client, 10);
	bool ans = info.accounts.find(10)->second->is_close();

	ASSERT_TRUE(ans);
}

TEST(TestOffline, testCreateCredit) {
	bank_info info = createSimpleConf();

	create_credit(info, new Date(0), new Time(0, 0), "Donatello", Client_type::Individual_Client, EUR, Credit_type::Charged_Daily, new Money(1000));
	Credit* credit = info.credits.begin()->second;
	
	ASSERT_EQ(credit->get_money_was_lended(), 1000);
}

TEST(TestOffline, CreateDebit) {
	bank_info info = createSimpleConf();

	create_debit(info, new Date(0), new Time(0, 0), "Donatello", Individual_Client, USD);
	Account* acc;
	for (auto it = info.accounts.begin(); it != info.accounts.end(); it++) {
		ulong id = it->second->get_ID();
		if (id != 10 && id != 20 && id > 4) {
			acc = it->second;
			break;
		}
	}

	ASSERT_EQ(acc->get_money(), -100);
}

TEST(TestOffline, testCreateDeposit) {
	bank_info info = createSimpleConf();

	create_deposit(info, new Date(0), new Time(0, 0), "Donatello", Individual_Client, YUAN, Deposit_type::Compounded_Daily_Min, new BString("3 month"), new Money(50000));
	Account* acc;
	for (auto it = info.accounts.begin(); it != info.accounts.end(); it++) {
		ulong id = it->second->get_ID();
		if (id != 10 && id != 20 && id > 4) {
			acc = it->second;
			break;
		}
	}

	Deposit * dep = info.deposits[info.client_accounts_by_account[acc->get_ID()]->get_debit_ID()];
	ASSERT_EQ(dep->get_interest_rate(), 0.026);
}

TEST(TestOffline, testExchangeCurrency) {
	bank_info info = createSimpleConf();

	exchange_currency(info, new Date(0), new Time(0, 0), "Donatello", Individual_Client, RUB, YUAN, new Money(100000));
	Account* acc = info.accounts[1];

	ASSERT_EQ(acc->get_money(), 1100000);
}

TEST(TestOffline, testWithdraw) {
	bank_info info = createSimpleConf();

	withdraw(info, new Date(0), new Time(0, 0), "Donatello", Individual_Client, 10, new Money(50000));
	Account* acc = info.accounts[10];

	ASSERT_EQ(acc->get_money(), 49750);
}

TEST(TestOffline, testTopUP) {
	bank_info info = createSimpleConf();

	top_up(info, new Date(0), new Time(0, 0), "Donatello", Individual_Client, 10, new Money(50000));
	Account* acc = info.accounts[10];

	ASSERT_EQ(acc->get_money(), 149995);
}



TEST(Testonline, testAddmoneyFromAnotherBank) {
	bank_info info = createSimpleConf();

	add_money_from_another_bank(info, new Date(0), new Time(0, 0), 10, new Money(50000));
	Account* acc = info.accounts[10];

	ASSERT_EQ(acc->get_money(), 150000);
}

void add_acc(bank_info& info, Account_currency_type cur_type) {
	info.accounts.insert({11, new Account(10, get_account_type_string(debit), new Money(0), get_account_currency_type_str(cur_type))});
	Client_account* cl_acc = new Client_account(1, 11, 3);
	info.client_accounts_by_account.insert({11, cl_acc});
	info.client_accounts_by_client.insert({ 1, cl_acc });
	info.client_accounts_by_deposit.insert({ 3, cl_acc });
	info.deposits.insert({ 3, new Deposit(3, 0, get_debit_type_string(Deposit_type::Compounded_Annually_Min), new Date(0))});
}

TEST(Testonline, testTROneClientOneCur) {
	bank_info info = createSimpleConf();
	add_acc(info, RUB);

	transfer_between_accs_of_one_client(info, new Date(0), new Time(0, 0), 10, 11, new Money(50000));
	Account* acc = info.accounts[10];

	ASSERT_EQ(acc->get_money(), 50000);
}

TEST(Testonline, testTROneClientOtherCur) {
	bank_info info = createSimpleConf();
	add_acc(info, EUR);

	transfer_between_accs_of_one_client(info, new Date(0), new Time(0, 0), 10, 11, new Money(50000));
	Account* acc = info.accounts[10];

	ASSERT_EQ(acc->get_money(), 50000);
}


TEST(Testonline, testTROtherClientOneCur) {
	bank_info info = createSimpleConf();
	add_acc(info, YUAN);

	transfer_between_accs_of_other_client(info, new Date(0), new Time(0, 0), 20, 11, new Money(25000));
	Account* acc = info.accounts[20];

	ASSERT_EQ(acc->get_money(), 25000);
}

TEST(Testonline, testTROtherClientOtherCur) {
	bank_info info = createSimpleConf();

	transfer_between_accs_of_other_client(info, new Date(0), new Time(0, 0), 20, 10, new Money(25000));
	Account* acc = info.accounts[20];

	ASSERT_EQ(acc->get_money(), 25000);
}


TEST(TestTime, CreditCharged_Daily) {
	bank_info info = createCredit(Charged_Daily);

	Time_events::end_of_the_day(new Date(0), new Time(19, 50), info);
	Account* acc = info.accounts[11];

	ASSERT_EQ(acc->get_money(), 499863.01369863015);
}

TEST(TestTime, CreditCharder_monthly) {
	bank_info info = createCredit(Charged_Monthly);

	Time_events::end_of_the_month(new Date(30), new Time(19, 50), info);
	Account* acc = info.accounts[11];

	ASSERT_EQ(acc->get_money(), 495753.42465753423);
}

TEST(TestTime, CreditCharder_quater) {
	bank_info info = createCredit(Charged_Quarterly);

	Time_events::end_of_the_Quater(new Date(90), new Time(19, 50), info);
	Account* acc = info.accounts[11];

	ASSERT_EQ(acc->get_money(), 487534.24657534249);
}

TEST(TestTime, CreditCharder_Semi) {
	bank_info info = createCredit(Charged_Semi_annually);

	Time_events::end_of_the_Semi(new Date(182), new Time(19, 50), info);
	Account* acc = info.accounts[11];

	ASSERT_EQ(acc->get_money(), 474931.50684931508);
}

TEST(TestTime, CreditCharged_Year) {
	bank_info info = createCredit(Charged_Annually);

	Time_events::end_of_the_year(new Date(365), new Time(19, 50), info);
	Account* acc = info.accounts[11];

	ASSERT_EQ(acc->get_money(), 450000.00000000000);
}

TEST(TestTime, DepositCompounded_Daily_Remaining) {
	bank_info info = createDeposit(Compounded_Daily_Remaining);

	Time_events::end_of_the_day(new Date(0), new Time(19, 50), info);
	Account* acc = info.accounts[11];

	ASSERT_EQ(acc->get_money(), 100013.69863013699);
}

TEST(TestTime, DepositCompounded_Daily_Min) {
	bank_info info = createDeposit(Compounded_Daily_Min);

	Time_events::end_of_the_day(new Date(0), new Time(19, 50), info);
	Account* acc = info.accounts[11];

	ASSERT_EQ(acc->get_money(), 100012.32876712328);
}

TEST(TestTime, DepositCompounded_Month_Remaining) {
	bank_info info = createDeposit(Compounded_Monthly_Remaining);

	Time_events::end_of_the_month(new Date(0), new Time(19, 50), info);
	Account* acc = info.accounts[11];

	ASSERT_EQ(acc->get_money(), 100424.65753424658);
}

TEST(TestTime, DepositCompounded_Month_Min) {
	bank_info info = createDeposit(Compounded_Monthly_Min);

	Time_events::end_of_the_month(new Date(0), new Time(19, 50), info);
	Account* acc = info.accounts[11];

	ASSERT_EQ(acc->get_money(), 100382.19178082192);
}

TEST(TestTime, DepositCompounded_Quater_Remaining) {
	bank_info info = createDeposit(Compounded_Quarterly_Remaining);

	Time_events::end_of_the_Quater(new Date(0), new Time(19, 50), info);
	Account* acc = info.accounts[11];

	ASSERT_EQ(acc->get_money(), 101232.87671232877);
}

TEST(TestTime, DepositCompounded_Quater_Min) {
	bank_info info = createDeposit(Compounded_Quarterly_Min);

	Time_events::end_of_the_Quater(new Date(0), new Time(19, 50), info);
	Account* acc = info.accounts[11];

	ASSERT_EQ(acc->get_money(), 101109.58904109590);
}

TEST(TestTime, DepositCompounded_Semi_Remaining) {
	bank_info info = createDeposit(Compounded_Semi_Annually_Remaining);

	Time_events::end_of_the_Semi(new Date(0), new Time(19, 50), info);
	Account* acc = info.accounts[11];

	ASSERT_EQ(acc->get_money(), 102493.15068493150);
}

TEST(TestTime, DepositCompounded_Semi_Min) {
	bank_info info = createDeposit(Compounded_Semi_Annually_Min);

	Time_events::end_of_the_Semi(new Date(0), new Time(19, 50), info);
	Account* acc = info.accounts[11];

	ASSERT_EQ(acc->get_money(), 102243.83561643836);
}


TEST(TestTime, DepositCompounded_Year_Remaining) {
	bank_info info = createDeposit(Compounded_Annually_Remaining);

	Time_events::end_of_the_year(new Date(0), new Time(19, 50), info);
	Account* acc = info.accounts[11];

	ASSERT_EQ(acc->get_money(), 105000.);
}

TEST(TestTime, DepositCompounded_Year_Min) {
	bank_info info = createDeposit(Compounded_Annually_Min);

	Time_events::end_of_the_year(new Date(0), new Time(19, 50), info);
	Account* acc = info.accounts[11];

	ASSERT_EQ(acc->get_money(), 104500.);
}

TEST(TestAnalyze, testClientReport) {
	bank_info info = createSimpleConf();

	Command* start = new Start_of_the_day_command(new Date(0), new Time(8, 0));
	Command* cmd = new Print_acc_info_command(new Date(0), new Time(9, 0), "Donatello", Client_type::Individual_Client, 10);
	start->run(info);
	cmd->run(info);

	map<ulong, vector<shared_ptr<Activity>>> mymap = info.analyzer.getOperation(1, new Date(0), new Date(0));
	ASSERT_EQ(mymap[0].size(), 1);
}

void makeTransfer(bank_info& info) {
	transfer_between_accs_of_other_client(info, new Date(0), new Time(0, 0), 10, 20, new Money(20));
	transfer_between_accs_of_other_client(info, new Date(0), new Time(0, 0), 10, 20, new Money(30));
	transfer_between_accs_of_other_client(info, new Date(0), new Time(0, 0), 10, 20, new Money(40));
}

TEST(TestAnalyze, testFindTransactionLess) {
	bank_info info = createSimpleConf();
	makeTransfer(info);

	vector<shared_ptr<Transaction>> vec = info.analyzer.getTransactionWithMoneyType(0, Less, make_shared<Money>(30));
	ASSERT_EQ(vec.size(), 1);

	shared_ptr<Transaction> tr = *vec.begin();
	ASSERT_EQ(tr->money->get_money(), 20);
}

TEST(TestAnalyze, testFindTransactionEqual) {
	bank_info info = createSimpleConf();
	makeTransfer(info);

	vector<shared_ptr<Transaction>> vec = info.analyzer.getTransactionWithMoneyType(0, Equal, make_shared<Money>(30));
	ASSERT_EQ(vec.size(), 1);

	shared_ptr<Transaction> tr = *vec.begin();
	ASSERT_EQ(tr->money->get_money(), 30);
}


TEST(TestAnalyze, testFindTransactionMore) {
	bank_info info = createSimpleConf();
	makeTransfer(info);

	vector<shared_ptr<Transaction>> vec = info.analyzer.getTransactionWithMoneyType(0, More, make_shared<Money>(30));
	ASSERT_EQ(vec.size(), 1);

	shared_ptr<Transaction> tr = *vec.begin();
	ASSERT_EQ(tr->money->get_money(), 40);
}

TEST(TestAnalyze, testLast) {
	bank_info info = createSimpleConf();
	makeTransfer(info);

	vector<shared_ptr<Transaction>> vec = info.analyzer.getLast();
	ASSERT_EQ(vec.size(), 3);
}

void makeApproaches(bank_info& info) {
	info.is_open = true;
	Command* cmdF = new Print_acc_info_command(new Date(0), new Time(9, 0), "Donatello", Client_type::Individual_Client, 10);
	Command* cmdS0 = new Print_acc_info_command(new Date(0), new Time(9, 0), "Mike", Client_type::Legal_Entity, 20);
	Command* cmdS1 = new Print_acc_info_command(new Date(1), new Time(9, 0), "Mike", Client_type::Legal_Entity, 20);

	cmdF->run(info);
	cmdS0->run(info);
	cmdF->run(info);
	cmdS1->run(info);
}

TEST(TestAnalyze, testRegulars) {
	bank_info info = createSimpleConf();
	makeApproaches(info);

	map<string, ulong> mmap = info.analyzer.getTop(make_shared<Date>(0), make_shared<Date>(1));
	ASSERT_EQ(mmap.size(), 1);

	ASSERT_EQ(mmap.begin()->first, "Mike");
	ASSERT_EQ(mmap.begin()->second, 2);
}

TEST(TestAnalyze, testRepeatedTrue) {
	bank_info info = createSimpleConf();
	makeApproaches(info);

	set<string> names = info.analyzer.getRepeat(make_shared<Date>(0), make_shared<Date>(1));
	ASSERT_EQ(names.size(), 1);
	ASSERT_EQ(*names.begin(), "Mike");
}


int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}