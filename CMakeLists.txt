# CMakeList.txt: проект CMake для IndProgTask2; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 20)

# Включение горячей перезагрузки для компиляторов MSVC, если поддерживается.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("IndProgTask2")


add_custom_target(conan_install
    COMMAND conan install ${CMAKE_SOURCE_DIR} --build=missing
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running Conan package manager"
)

set(HEADER ${CMAKE_CURRENT_SOURCE_DIR})

set(bank "Data_types/Simple/Bank_string/Bank_string.cpp" 
    "Data_types/Simple/Date/Date.cpp" "Data_types/Simple/Money/Money.cpp" "Data_types/Simple/Time/Time.cpp" 
    "Data_types/Enums/Account_currency_type/Account_currency_type.cpp" "Data_types/Enums/Account_type/Account_type.cpp" 
    "Data_types/Enums/Client_type/Client_type.cpp" "Data_types/Enums/Credit_type/Credit_type.cpp" "Data_types/Enums/Debit_type/Debit_type.cpp" 
    "Data_types/Enums/Work_place_type/Work_place_type.cpp" "Data_types/Complex/Account/Account.cpp" "Data_types/Complex/Bank_account/Bank_account.cpp" 
    "Data_types/Complex/Client/Client.cpp" "Data_types/Complex/Client_account/Client_account.cpp" "Data_types/Complex/Client_debt/Client_debt.cpp" 
    "Data_types/Complex/Credit/Credit.cpp" "Data_types/Complex/Deposit/Deposit.cpp" "Data_types/Complex/Exchange_info/Exchange_info.cpp" 
    "Data_types/Complex/Work_place/Work_place.cpp" "Common_tools/add_money_to_bank_acc.cpp"
    "Common_tools/check_if_more_then_credit.cpp" "Common_tools/check_string_by_scheme.cpp" "Common_tools/delete_spaces_from_start_and_end.cpp"
    "Common_tools/deposit_in_period.cpp" "Common_tools/get_client.cpp" "Common_tools/try_reduce_money_from_bank_acc.cpp" "Common_tools/try_reserve.cpp"
    "Order_book/Order_book.cpp" 
    "Clients_operations/Client_operation_tools.cpp" "Clients_operations/Close_deposit.cpp"
    "Clients_operations/Create_credit.cpp" "Clients_operations/Create_debit.cpp" "Clients_operations/Create_deposit.cpp" "Clients_operations/Exchange_currency.cpp"
    "Clients_operations/Print_acc_info.cpp" "Clients_operations/Top_up.cpp" "Clients_operations/Withdraw.cpp" 
    "Online_operations/add_money_from_another_bank.cpp" "Online_operations/tr_one_client.cpp" "Online_operations/tr_other_client.cpp"
    "Time_events/Time_tools.cpp" "Time_events/Time_events.cpp"
    "Init/Init_bank.cpp"
    "Command/Command.cpp"
    "Command/Client_approaches/Close_deposit_command.cpp" "Command/Client_approaches/Create_credit_command.cpp" "Command/Client_approaches/Create_debit_command.cpp" "Command/Client_approaches/Create_deposit_command.cpp"
    "Command/Client_approaches/Exchange_currency_command.cpp" "Command/Client_approaches/Print_acc_info_command.cpp" "Command/Client_approaches/Top_up_command.cpp"
    "Command/Client_approaches/Withdraw_command.cpp" 
    "Command/Online/Add_money_from_another_bank_command.cpp" "Command/Online/Transfere_between_accs_of_one_client_command.cpp"
    "Command/Online/Transfer_between_accs_of_other_client_command.cpp" "Command/Time_events/End_of_the_day_command.cpp" "Command/Time_events/End_of_the_month_command.cpp"
    "Command/Time_events/End_of_the_Quater_command.cpp" "Command/Time_events/End_of_the_Semi_command.cpp" "Command/Time_events/End_of_the_year_command.cpp"
    "Command/Time_events/Start_of_the_day_command" "Bank/bank.cpp"
      "IDgen/IDgen.cpp" "Analyzer/Transaction/Transaction.cpp" "Analyzer/Transaction_pool.cpp" "Analyzer/Client_info_analyzer.cpp" "Analyzer/Analyzer.cpp" "Analyzer/Client_activity_analyzer.cpp" "Command/Analyzer/Client_activity_report_command.cpp" "Command/Analyzer/Find_transaction_command.cpp" "Command/Analyzer/Last_transaction_command.cpp" "Command/Analyzer/Find_regulars_command.cpp" "Command/Analyzer/Find_repeated_command.cpp")

# Добавьте источник в исполняемый файл этого проекта.
add_executable (IndProgTask2 "IndProgTask2.cpp" "IndProgTask2.h" ${bank})

add_dependencies(IndProgTask2 conan_install)


include(${CMAKE_BINARY_DIR}/generators/conan_toolchain.cmake)
find_package(GTest REQUIRED)

target_include_directories(IndProgTask2 PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)


install(TARGETS IndProgTask2 RUNTIME DESTINATION ${CMAKE_INSTAL_BINDIR})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET IndProgTask2 PROPERTY CXX_STANDARD 20)
endif()

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set (CMAKE_EXPORT_COMPILE_COMMANDS YES)

enable_testing()

add_subdirectory(tests)
# TODO: Добавьте тесты и целевые объекты, если это необходимо.
