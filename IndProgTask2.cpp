// IndProgTask2.cpp: определяет точку входа для приложения.
//

#include <iostream>
#include <string>
#include <utility>
#include <algorithm>
using namespace std;

#include "bank.hpp"

int main(int argc, char* argv[])
{
	ulong seed = 5000;
	if (argc >= 2) {
		seed = atoi(argv[1]);
		if (seed == 0) seed = 5000;
	}

	bank(seed);
	exit(EXIT_SUCCESS);
}
