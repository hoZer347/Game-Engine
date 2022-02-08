#include "UnitMenuActions.h"
#include "UnitMenu.h"

#include "GridActions.h"

#include <vector>

void attack() {
	// TODO:
	std::vector<unsigned short> v;
	create_unit_menu(v);
}

void skill() {
	// TODO:
}

void equip() {
	// TODO:
}

void item() {
	// TODO:
}

void end() {
	// TODO:
}

void wait() {
	inputs->on_del.clear();
	prev_menu();
}

void cancel() {
	prev_menu();
}

