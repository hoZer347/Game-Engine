#include "GridActions.h"

#include "Grid.h"
#include "Inputs.h"
#include "UnitMenu.h"

#include <functional>
#include <vector>
#include <map>

enum {
	G_SELECT_UNSELECT = 0
};

void setup_grid(Grid* g) {
	inputs->mem["Grid"] = g;
	g_select(g);
	g_cursor_updates_grid(g);
}

void g_select(Grid* g) {
	inputs->mem["Grid"] = g;

	inputs->m[GLFW_MOUSE_BUTTON_LEFT] = [](int a, int m) {
		Grid* g = (Grid*)inputs->mem["Grid"];

		if (a)
			if (g->hovered &&
				g->hovered->u &&
				!g->hovered->u->has_moved) {

				// Getting the clicked cell
				g->selected = g->hovered;
				g->selected->u = g->hovered->u;

				// Flood filling the cell based on the unit
				std::set<Cell*> S;
				flood_fill(g->selected, S, u_ff, g->selected->u->get(U::RNG), g->selected);
				for (auto& c : S)
					if (!c->u || c->u == g->selected->u)
						c->change_color(g->selected->u->team);

				std::cout << S.size() << std::endl;

				g_unselect(g);
			}
		
		// TODO: clicking an empty cell (terrain info / map otions)
	};

	inputs->m[GLFW_MOUSE_BUTTON_RIGHT] = [](int a, int m) {
		Grid* g = (Grid*)inputs->mem["Grid"];

		// Deselecting cells
		g->hovered = NULL;
		g->selected = NULL;

		// Resetting selected cells
		for (auto& _C : g->C)
			for (auto& c : _C)
				c->change_color(TEAM_NULL);

		g_select(g);
	};
}

void g_unselect(Grid* g) {
	inputs->mem["Grid"] = g;

	inputs->m[GLFW_MOUSE_BUTTON_LEFT] = [](int a, int m) {
		Grid* g = (Grid*)inputs->mem["Grid"];

		if (!a)
			if (g->hovered &&
				(!g->hovered->u || g->hovered->u == g->selected->u) &&
				g->selected &&
				g->selected->u &&
				g->hovered->clr == g->selected->u->team) {

				// Moving Unit
				if (!(g->hovered->u == g->selected->u)) {
					g->hovered->u = g->selected->u;
					g->selected->u = NULL;
				}

				// Resetting selected cells
				for (auto& _C : g->C)
					for (auto& c : _C)
						c->change_color(TEAM_NULL);

				// Going back to select
				g_select(g);

				// Creating a menu of options for the selected unit
				create_unit_menu(g->hovered->u->get_options());
				((UnitMenu*)MENU)->unit = g->hovered->u;

				// Making the movement reversable
				if (!(g->hovered->u == g->selected->u)) {
					inputs->mem["Selected"] = g->selected;
					inputs->mem["Hovered"] = g->hovered;
					inputs->mem["Unit"] = g->hovered->u;

					inputs->on_del.push_back([]() {
						Cell
							* c1 = (Cell*)inputs->mem["Selected"],
							* c2 = (Cell*)inputs->mem["Hovered"];

						if (c1 && c2) {
							c1->u = c2->u;
							c2->u = NULL;
						}
					});
				}
			}
	};
}

void g_cursor_updates_grid(Grid* g) {
	inputs->mem["Grid"] = g;

	inputs->c = [](double x, double y) {
		Grid* g = (Grid*)inputs->mem["Grid"];

		g->animate = true;
	};
}
