#pragma once

#include "Grid.h"
#include "Unit.h"

#include <set>

static void flood_fill(Cell* o, std::set<Cell*>& C, std::function<double(Cell*, Cell*)> f, double i, Cell* c) {
	if (!c || i <= 0) return;

	i -= f(o, c);

	C.insert(c);

	flood_fill(o, C, f, i, (*c)[U]);
	flood_fill(o, C, f, i, (*c)[D]);
	flood_fill(o, C, f, i, (*c)[L]);
	flood_fill(o, C, f, i, (*c)[R]);
}

static void a_star(Cell* goal, Cell* c, std::vector<Cell*>& path, std::map<Cell*, unsigned short> visited) {

}

static void attach_neighbours(Grid* g) {
	for (unsigned int i = 0; i < g->C.size(); i++)
		for (unsigned int j = 0; j < g->C[0].size(); j++) {
			if (j < g->C.size() - 1)
				(*g->C[i][j])[U] = g->C[i][j + 1];
			if (j > 0)
				(*g->C[i][j])[D] = g->C[i][j - 1];
			if (i > 0)
				(*g->C[i][j])[L] = g->C[i - 1][j];
			if (i < g->C.size() - 1)
				(*g->C[i][j])[R] = g->C[i + 1][j];
		}
}

static std::function<double(Cell*, Cell*)> u_ff = [](Cell* o, Cell* c) {\
	if (!c || !o || !o->u)
		return 10000000.;

	if (!c->u || c->clr == TEAM_NULL || c->u->team == o->clr)
		return c->terrain;

	return 10000000.;
};
