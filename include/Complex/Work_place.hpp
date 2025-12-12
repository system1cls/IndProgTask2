#pragma once

#include "Simple/Simple_data_types.hpp"
#include "Enums/Enums.hpp"
#include <vector>

class Work_place {
private:
	BString* type;
	ulong cnt_places;
	vector<ulong> time_to_be_freed;
	vector<ulong> cnt_clients_in_day;
	vector<ulong> cnt_clients_in_year;

public:

	Work_place(BString* type, ulong cnt_places);

	BString* get_type() const;
	ulong get_cnt_places() const;

	ulong min_time_when_be_ready();

	ulong add_new_client(Time* start_time, ulong time);

	void end_day(Date* date);

	void end_year(Date* date);

	~Work_place();
};