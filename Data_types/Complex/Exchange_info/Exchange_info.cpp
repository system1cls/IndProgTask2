#include "Complex/Exchange_info.hpp"

EInfo::Exchange_info(BString* from, BString* to, double coef) {
	this->coef = coef;
	this->from = from;
	this->to = to;
}

double EInfo::get_coef() {
	return this->coef;
}

BString* EInfo::get_from() {
	return this->from;
}

BString* EInfo::get_to() {
	return this->to;
}

EInfo::~Exchange_info() {
	if (this->from != nullptr) delete this->from;
	if (this->to != nullptr) delete this->to;
}