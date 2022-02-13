#include "Unit.h"

Unit* create_unit() {
	Unit* u = new Unit();

	make_meshobj((_MeshObj*)u);

	return u;
}

void Unit::update() {

}

std::vector<unsigned short>& Unit::get_options() {
	return options;
}

std::vector<unsigned short>& Unit::get_skills() {
	return skills;
}
