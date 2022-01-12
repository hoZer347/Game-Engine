#include "Unit.h"

std::vector<Unit*> UNIT;

Unit* create_unit() {
	Unit* u = new Unit();

	UNIT.push_back(u);

	return u;
}

std::vector<unsigned short>& Unit::get_options() {
	return options;
}

std::vector<unsigned short>& Unit::get_skills() {
	return skills;
}
