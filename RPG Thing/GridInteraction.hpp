#pragma once

#include "Inputs.h"
#include "Renderer.h"
#include "Grid.h"
#include "Unit.h"
#include "GridFunctions.hpp"
#include "Animations.hpp"

#include <functional>
#include <vector>
#include <map>

enum {
	G_SELECT_UNSELECT = 0
};

static void g_select(Grid*);
static void g_unselect(Grid*);
static void attach_neighbours(Grid*);
static void g_cursor_updates_grid(Grid*);

static void setup_grid(Grid* g) {
	inputs->mem["Grid"] = g;
	g_select(g);
	g_cursor_updates_grid(g);
}

static void g_select(Grid* g) {
	inputs->mem["Grid"] = g;

	inputs->m[GLFW_MOUSE_BUTTON_LEFT] = [](int a, int m) {
		Grid* g = (Grid*)inputs->mem["Grid"];

		if (a)
			if (g->hovered && g->hovered->u) {
				g->selected = g->hovered;
				g->selected->u = g->hovered->u;

				std::set<Cell*> S;
				flood_fill(g->selected, S, u_ff, g->selected->u->get(U::RNG), g->selected);
				for (auto& c : S)
					if (!c->u || c->u == g->selected->u)
						c->change_team(g->selected->u->team);

				g_unselect(g);
			}
	};

	inputs->m[GLFW_MOUSE_BUTTON_RIGHT] = [](int a, int m) {
		Grid* g = (Grid*)inputs->mem["Grid"];

		// Deselecting cells
		g->hovered = NULL;
		g->selected = NULL;

		// Resetting selected cells
		for (auto& _C : g->C)
			for (auto& c : _C)
				c->change_team(TEAM_NULL);

		g_select(g);
	};
}

static void g_unselect(Grid* g) {
	inputs->mem["Grid"] = g;

	inputs->m[GLFW_MOUSE_BUTTON_LEFT] = [](int a, int m) {
		Grid* g = (Grid*)inputs->mem["Grid"];

		if (!a)
			if (g->hovered &&
				!g->hovered->u &&
				g->selected &&
				g->selected->u &&
				g->hovered->team == g->selected->u->team) {

				std::set<Cell*> S;
				flood_fill(g->selected, S, u_ff, g->selected->u->get(U::RNG), g->selected);
				for (auto& c : S)
					if (!c->u || c->u == g->selected->u)
						c->change_team(TEAM_NULL);

				g->selected->u->s->trns = NULL;
				g->hovered->u = g->selected->u;
				g->selected->u = NULL;

				g_select(g);
			}
	};
}

static void g_cursor_updates_grid(Grid* g) {
	inputs->mem["Grid"] = g;

	inputs->c = [](int x, int y) {
		Grid* g = (Grid*)inputs->mem["Grid"];

		g->animate = true;
	};
}
