#include "UnitMenuActions.h"
#include "UnitMenu.h"

#include "Grid.h"

#include <vector>

void attack() {
	// Showing Attack Range
	Cell* c = (Cell*)inputs->mem["Hovered"];
	MENU->change_focus(false);
	for (auto& _c : GRID->C)
		for (auto& __c : _c)
			__c->change_color(TEAM_NULL);
	std::set<Cell*>* C = new std::set<Cell*>();
	flood_fill(c, *C, u_ff, ((UnitMenu*)MENU)->unit->get(U::ARG), c);
	for (auto& _c : *C)
		_c->change_color(TEAM_R_ATK);
	//

	// Assigning Functionality
	new_inputs();
	inputs->mem["Range"] = C;

	// Selected Cell to Attack
	inputs->m[GLFW_MOUSE_BUTTON_LEFT] = [](int a, int m) {
		std::set<Cell*> C = *(std::set<Cell*>*)inputs->mem["Range"];
		Grid* g = GRID;

		if (a) {
			if (g->hovered && g->hovered->clr == TEAM_R_ATK) {

			}

			for (auto& c : C)
				c->change_color(TEAM_NULL);

			prev_inputs();
			wait();
		}
	};
	//

	// Going Back to Menu
	inputs->m[GLFW_MOUSE_BUTTON_RIGHT] = [](int a, int m) {
		std::set<Cell*> C = *(std::set<Cell*>*)inputs->mem["Range"];
		prev_inputs();

		for (auto& c : C)
			c->change_color(TEAM_NULL);

		MENU->change_focus(true);
	};
	//
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

