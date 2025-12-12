#pragma once

#include "Simple/Simple_data_types.hpp"
#include "Enums/Enums.hpp"

class Exchange_info {
private:
	BString* from;
	BString* to;
	double coef;

public:

	Exchange_info(BString* from, BString* to, double coef);

	BString* get_from();
	BString* get_to();
	double get_coef();

	~Exchange_info();
};

typedef Exchange_info EInfo;