#pragma once

#include "Inputs.h"
#include "Renderer.h"
#include "Grid.h"

enum {
	G_SELECT_UNSELECT = 0
};

static void g_select(Grid*);
static void g_unselect(Grid*);

static void g_select(Grid* g) {
	inputs.m[GLFW_MOUSE_BUTTON_LEFT] = [](int a, int m) {
		Grid* g = (Grid*)inputs.mem["Grid"];

		if (a)
			if (g->hovered && g->hovered->u) {
				g->selected = g->hovered;
				g->hovered->animate = false;

				g_unselect(g);
			}
			
	};
}

static void g_unselect(Grid* g) {
	inputs.m[GLFW_MOUSE_BUTTON_LEFT] = [](int a, int m) {
		Grid* g = (Grid*)inputs.mem["Grid"];

		if (!a)
			if (g->hovered &&
				!g->hovered->u &&
				g->selected &&
				g->selected->u) {

				g->hovered->u = g->selected->u;
				g->selected->u = NULL;
				g->selected->animate = true;

				g_select(g);
			}
	};
}

static void setup_grid(Grid* g) {
	inputs.mem["Grid"] = g;
	g_select(g);
}
